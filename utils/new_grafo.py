# This program is under GPL Licence
#Project: "Gerencia de Consumo de Energia em Ambientes de Codigo Aberto" - UFAM - INdT
#Coordinator: Dr. Prof. Raimundo Barreto - UFAM

#Code: Generator of Control Flow Graph from a C code (Jonatas) with WCEC (Carlos Bruno) 

#Author: Jonatas Costa de Oliveira - UFAM -----   jonatasoli@gmail.com / jco@dcc.ufam.edu.br
#History: 
# 2007-14-05: version 0.2 implemented

r"""This code aims to generate the flow graph from a C Code in the graphml format, more informations in README

	ps: Some coments, especialy "prints", are useful to tests"""


"""This function returns a string from the C code 
@caminho is the C code"""
def abre_arquivo(caminho):
	fin = open(caminho, "ra") # ra = read-only + ascii
	return fin.readlines ()


"""This function verifies if the line passed is a declaration of a function"""
def isnt_function(linha):
	try:
		linha = linha.split()
		for atomo in lista_tipos:
			if (atomo == linha[0]):
				linha = " ".join(linha)
				if ((linha.find("(") >= 0) and (linha.find(")") >= 0)):
					return 0
				break;
		return 1
	except:
		return 1			
			
	
"""This function adds new types of declarion in the list of the declaration types, in this case, they are pointers """
def complementa_tipos(lista):
	lista_aux= []
	for elemento in lista:
		aux = elemento + "*"
		lista_aux.append(aux)
		aux = elemento + "**"
		lista_aux.append(aux)
		aux = elemento + "***"
		lista_aux.append(aux)
	return lista + lista_aux



"""This function returns 1 (true) if the word passed doesn't results in a block end"""
def isnt_endblock(word):
	for desvio in lista_stops:
		if (desvio == word):
			return 0
	return 1


"""Get the name of the function from the line given"""
def get_name_function(string):
	string = string.split()
	i = len(string[0]) + 1
	string = " ".join(string)
	function = ""
	while(not (string[i] == "(")):
		function = function + string[i]
		i = i  + 1	
	lista_funcoes.append(function)
	return function


"""Get the next block of the code, starts the research in the line given, and returns the block, the type of the block and updates the current line """
def get_block(linha,string,funcao):
	words = string[linha].split()
	block = ""
	tipo = "default"
		

	try:
		tipo = switch_bloco[words[0]]
		
		block = block + string[linha]
		linha = linha + 1
	
		if (tipo == "else"):
			block = block + string[linha]
			linha = linha + 1
			words = string[linha].split()
		elif (tipo == "fim") or (tipo == "break"):
			return [linha,block,tipo]
			
		elif (tipo == "switch"):
			block = block + string[linha]
			linha = linha + 1
			return [linha,block,tipo]	
		


		if (linha == len(string)):
			return [linha,block,tipo]
		while (string[linha] == "\n"):
				linha = linha +1
		words = string[linha].split()
		while (isnt_endblock(words[0])):
			
			block = block + string[linha]
			linha = linha + 1 
			if (linha == len(string)):
				return [linha,block,tipo]
			while (string[linha] == "\n"):
				linha = linha +1
			words = string[linha].split()
		
		if (words[0] == "if"):

			tipo = tipo + " if"		
			block = block + string[linha]
			linha = linha + 1
		
	
		return [linha,block,tipo]
	except:
		tipo =  "Normal Block"
		block = block + string[linha]
		linha = linha + 1
		if (linha == len(string)):
			return [linha,block,tipo]
		while (string[linha] == "\n"):
				linha = linha +1
		words = string[linha].split()
		while (isnt_endblock(words[0])):
			block = block + string[linha]
			linha = linha +1
			if (linha == len(string)):
				return [linha,block,tipo]
			while (string[linha] == "\n"):
				linha = linha +1	
			words = string[linha].split()
		if (words[0] == "if"):
			tipo = tipo + " if"		
			block = block + string[linha]
			linha = linha + 1
		elif	(words[0]=="}"):
			tipo = tipo + " fim"		
			block = block + string[linha]
			linha = linha + 1
		return [linha,block,tipo]
		
	
	
		

"""Function that uses the get_block function to get all the blocks of the C code """
def get_all_blocks(string):
	linha = 0
	funcao_atual = ""
	while (linha < len(string)):
		while((string[linha])[0] == "#"):
			linha = linha +1
		while(not(isnt_function(string[linha]))):
			funcao_atual = get_name_function(string[linha])
			linha = linha +1
		if (not(string[linha] == "\n")):
			
			lista =  get_block(linha,string,funcao_atual)
			if (not (lista[1] == "")):
				bloco_atual = bloco()
				bloco_atual.c = lista[1]
				bloco_atual.linhas  = range(linha+1,lista[0]+1)
		
				 #Gets the asm code
				asm_code = get_asm_to_wcec(afc_dict,afc_keys,bloco_atual.linhas)	
				bloco_atual.assembly = asm_code 		
			
				#calculates the WCEC							
				bloco_atual.wcec = cal_wcec(asm_code,wcec_table)				
				bloco_atual.funcao = funcao_atual
				bloco_atual.tipo = lista[2]
				if (lista[2] == "for" or lista[2] == "while"):
					bloco_atual.loops = (lista[1].split())[-1]
				lista_blocos.append(bloco_atual)
			linha = lista[0]
		else:
			linha = linha +1
		


	
"""These next functions build the edges of each function of the graph. To do this, a execution stack of the C code is necessary.
@funcoes list storages all the functions names declared in the C code, and the list of the blocks is a list of list. If the block is part of the second list so the function that it belongs is the funcoes[1].
@lista_exec storages the sequency of blocks types"""

def build_graph(blocks):
	indice = 0  
	indice_bloco = 0

	
	funcoes = [] 
	lista_exec = []
	blocos = []
	arestas = []
	pos = 0


	for funcao in lista_funcoes:
		funcoes.append([])
		for block in blocks:
			if block.funcao == funcao:
				funcoes[-1].append(block) 

	
	for funcao in funcoes:
		for block in funcoes[indice]:
			lista_exec.append(block)
			block.ident = block.funcao + "_" + str(indice_bloco)
			indice_bloco = indice_bloco + 1
			print block.tipo
		indice = indice + 1
		arestas.append(define_arestas(lista_exec))
		blocos.append(lista_exec) 
		lista_exec = []
	return [blocos,arestas]

"""This function inserts the correct edges in the nodes that are break's"""

def put_breaks(lista_arestas, list_breaks):
	for break_ in list_breaks:
	 	entrada = break_

	 	indice = 0
	 	
	 	while indice < len(lista_arestas):
	 		if lista_arestas[indice][0] == entrada:
	 			pai_loop_case = lista_arestas[indice][1]
	 			location = indice
	 			break
	 		indice += 1
	 		
	 	indice = 0	
	 	maior = -1
		while indice < len(lista_arestas):
	 		if (lista_arestas[indice][0] == pai_loop_case) and (lista_arestas[indice][1] > maior) :
	 			maior = lista_arestas[indice][1]
	 		indice += 1
	 	saida = maior
	 	
	 	lista_arestas[location] = [entrada,saida]
	 	
	lista_arestas = func_take_default(lista_arestas)
	 	
	return lista_arestas	
	
	
def func_take_default(lista_arestas):
	indice = 0
	
	while indice <	len (lista_arestas):
		if (lista_blocos[(lista_arestas[indice][0])].tipo == "switch_with_default") and (lista_blocos[(lista_arestas[indice][1])].tipo == "fim"):
			lista_arestas.pop(indice)
			print indice
		indice += 1
		
	return lista_arestas			
	

def define_arestas(lista):
	pilha = []
	indice = 0
	arestas = []
	lista_break = []
	#print "Tamanho Funcao: %d" % (len(lista))
	while (indice < len(lista)):
		bloco = lista[indice]
		if bloco.tipo.find("break") >= 0 :
			lista_break.append(indice)
			
		tupla = switch_exec[bloco.tipo](pilha,indice,lista)
		pilha = tupla[0]
		print pilha
		aresta = tupla[1]
		if aresta:
			if (len(aresta)%2 == 0):
				cont = 0
				while cont < len(aresta):
					if (aresta[cont] >=  len(lista)) or (aresta[cont+1] >=  len(lista)):
						break
					arestas.append([(aresta[cont]),(aresta[cont+1])])
					cont = cont + 2
				
			
		indice = indice + 1
		
	print pilha	
	print "\n\nArestas:"
	print arestas
	arestas = put_breaks(arestas,lista_break)
	
	print "\n\nArestas:"
	print arestas
	print "lista_breaks:"
	print lista_break
	return [arestas]



#Manipulation of the execution stack, it's based in the list of the types of the blocks


def func_inicio(pilha,indice,lista):
	pilha.append(["inicio",indice])
	aresta = [indice,indice+1]
	return [pilha,aresta]
	
def func_inicio_break(pilha,indice,lista):
	cont = -1
	
	while (pilha[cont][0] != "for") and (pilha[cont][0] != "while") and (pilha[cont][0] != "switch"):
		cont -= 1
	
	aresta = [indice,pilha[cont][1]]
	pilha.append(["inicio",indice])
	return [pilha,aresta]


def func_inicio_if(pilha,indice,lista):
	pilha.append(["inicio",indice])
	pilha.append(["if",indice])
	aresta = [indice,indice+1]
	return [pilha,aresta]


def func_if(pilha,indice,lista):
	pilha.append(["if",indice])
	aresta = [indice,indice+1]
	return [pilha,aresta]
	
def func_else(pilha,indice,lista):
	pilha.append(["else",indice])
	aresta = [indice,indice+1]
	return [pilha,aresta]


def func_inicio_fim(pilha,indice,lista):

	try:
		if ((pilha[-1])[0] == "if"):
			if lista[indice+1].tipo.find("else") == -1:
				aresta = [(pilha[-1])[1],indice+1,indice,indice+1]
				pilha.pop()
			elif (lista[indice+1].tipo == "else"):
				aresta = [(pilha[-1])[1],indice+1]
				pilha.pop()
				pilha.append(["else",indice+1])
			else:
				aresta = [(pilha[-1])[1],indice+1]
				pilha.pop()
		if ((pilha[-1])[0] == "while") or ((pilha[-1])[0] == "for"):
			aresta = [(pilha[-1])[1],indice+1,indice,(pilha[-1])[1],indice+1,indice+2]
			pilha.pop() 
		return [pilha,aresta]
	except:
		return [pilha,0]


def func_fim(pilha,indice,lista):
	arestas = []
	if ((pilha[-1])[0] == "inicio"):
		pilha.pop() 
	try:
		if ((pilha[-1])[0] == "if"): 
			arestas = [(pilha[-1])[1],indice+1] 
			pilha.pop() 
		elif ((pilha[-1])[0] == "else"):
			arestas = [indice,indice+1,(pilha[-1])[1] -1, indice+1] 
			pilha.pop() 
		elif ((pilha[-1])[0] == "while") or ((pilha[-1])[0] == "for"):
			arestas = [(pilha[-1])[1],indice+1,indice,(pilha[-1])[1]]
			pilha.pop() 
		elif ((pilha[-1])[0] == "switch") or ((pilha[-1])[0] == "switch_with_default"):
			arestas = [(pilha[-1])[1],indice,indice,indice+1] 
			pilha.pop() 
		return [pilha,arestas]
	except:
		return [pilha,0]
		

def func_else_fim(pilha,indice,lista):
	aresta = [indice,indice+1,indice-1,indice+1]
	return [pilha,aresta]			
	

def func_else_if(pilha,indice,lista):
	pilha.append(["else",indice])
	pilha.append(["if",indice])
	aresta = [indice,indice+1]
	return [pilha,aresta]	


def func_while(pilha,indice,lista):
	pilha.append(["while",indice])
	aresta = [indice,indice+1]
	return [pilha,aresta]		


def func_for(pilha,indice,lista):
	pilha.append(["for",indice])
	aresta = [indice,indice+1]
	return [pilha,aresta]			
	

def func_normal_fim(pilha,indice,lista):
	arestas = []
	if ((pilha[-1])[0] == "inicio"):
		pilha.pop() 
	try:
		if ((pilha[-1])[0] == "if"): 
			arestas = [(pilha[-1])[1],indice+1] 
			pilha.pop() 
		elif ((pilha[-1])[0] == "else"):
			arestas = [indice,indice+1,(pilha[-1])[1] -1, indice+1] 
			pilha.pop() 
		elif ((pilha[-1])[0] == "while") or ((pilha[-1])[0] == "for"):
			arestas = [(pilha[-1])[1],indice+1,indice,(pilha[-1])[1]]
			pilha.pop() 
		return [pilha,arestas]
	except:
		return [pilha,0]


	
	

def func_normal_if(pilha,indice,lista):
	pilha.append(["if",indice])
	aresta = [indice,indice+1]
	return [pilha,aresta]		


def func_normal(pilha,indice,lista):
	aresta = [indice,indice+1]
	return [pilha,aresta]
	
def func_break(pilha,indice,lista):
	cont = -1
	while (pilha[cont][0] != "for") and (pilha[cont][0] != "while") and (pilha[cont][0] != "switch"):
		cont -= 1
	aresta = [indice,pilha[cont][1]]
	return [pilha,aresta]		


def func_switch(pilha,indice,lista):
	aresta = []
	pilha.append(["switch",indice])
	return [pilha,aresta]
	
def func_case(pilha,indice,lista):
	arestas = []
	if pilha[-1][0] == "switch" :
		arestas = ([pilha[-1][1],indice,indice,indice+1])
	return [pilha,arestas]		
	

def func_default(pilha,indice,lista):
	arestas = []
	if pilha[-1][0] == "switch":
		arestas = [pilha[-1][1],indice,indice,indice+1]
		pilha[-1][0] = "switch_with_default"
		lista_blocos[(pilha[-1][1])].tipo = "switch_with_default"
	return [pilha,arestas]		


def concatene_arestas(lista1,lista2):
	lista = lista1
	for elem in lista2:
		lista.append(elem)
	#print lista
	return lista
	

	




"""These funcions builds the graph that will be executed, it's starts from the main function """

def build_func(blocos,arestas):

	blocos_with_func = []
	indice = 0
	
	
	while (indice < len(blocos)):
		count = 0
		while (count < len(blocos[indice])):
			count2 = 0
			while (count2 < len(lista_funcoes)):
				if (count2 != indice):
					soma =  (blocos[indice][count].c).count(lista_funcoes[count2] + " ") + (blocos[indice][count].c).count(lista_funcoes[count2] + "(")
					if soma  > 0:
						contador = 0
						while contador < soma:
							blocos_with_func.append([indice,count2,count])  #[Current Function,Function called,Block Position]
							contador +=1
				count2 = count2 + 1
			count = count + 1
		indice = indice + 1
	print blocos_with_func

	indice = pos_main(lista_funcoes)
	if (indice == -1):
		print "Nao Existe Funcao Main"
		sys.exit(1)
	new_blocos = blocos[indice]
	new_arestas = arestas[indice][0]

	lista = build_func_aux(blocos,arestas,blocos_with_func,indice,new_blocos,new_arestas,0)
	#print lista[0]
	return [lista[0],lista[1]]
	#print arestas[indice][0]


def pos_main(funcoes):
	indice = 0
	while indice < len(funcoes):
		if funcoes[indice] == "main":
			return indice
		indice = indice + 1
	return -1




def build_func_aux(blocos,arestas,blocos_with_func,indice,new_blocos,new_arestas,retorno):
	tuplas_funcao_atual = []
	
	for tupla in blocos_with_func:
		if (tupla[0] == indice):
			tuplas_funcao_atual.append(tupla)
	
	cont = 0
	for tupla in tuplas_funcao_atual:

		indice = tupla[1]
		for aresta in new_arestas:
			if aresta[1] == tupla[2]+retorno:
				aresta[1] = len(new_blocos)
		
		for aresta in arestas[tupla[1]][0]:
			valor1 = aresta[0] + len(new_blocos)
			valor2 = aresta[1] + len(new_blocos)
			new_arestas.append([valor1,valor2])
					
		retorno2 = len(new_blocos)

		for bloco in blocos[tupla[1]]:
			new_blocos.append(bloco)

		new_arestas.append([len(new_blocos)-1,tupla[2]+retorno])

	
		lista = build_func_aux(blocos,arestas,blocos_with_func,indice,new_blocos,new_arestas,retorno2)
		new_arestas = lista[0]
		new_blocos = lista[1]
		cont += 1
		
	

	
	return [new_arestas,new_blocos]



#Get the first block of the final graph

def get_node_init():
	nodes = range(len(lista_blocos))
	for aresta in arestas:
			try:
				nodes.remove(aresta[1])
			except:
				aux = 1	

	return nodes[0]


#Get the last block of the final graph

def get_node_final():
	nodes = range(len(lista_blocos))
	for aresta in arestas:
			try:
				nodes.remove(aresta[0])
			except:
				aux = 1	
				
	new_block = bloco()
	new_block.wcec = 0
	new_block.tipo = "normal"
	new_block.linhas = [0]
	lista_blocos.append(new_block)
	
	for node in nodes:
		arestas.append([node,(len(lista_blocos))-1])
	return len(lista_blocos)-1

#Output - Prints	

def imprime_bloco(bloco):
	print "\nNome Bloco: %s" %bloco.ident
	print "\nBloco em C: \n%s" %bloco.c
	print "Bloco em Asm: \n %s"%bloco.assembly
	print "\nLinhas para Script do Assembly: "
	print bloco.linhas
	print "\nFuncao ao qual pertence: %s" %bloco.funcao
	print "\nTipo do Bloco: %s" %bloco.tipo	
	if (bloco.tipo == "for" or bloco.tipo == "while"):
		print "\nCiclos do loop: %s" %bloco.loops
	print "\nWCEC: %d" %bloco.wcec
	print "\n\n********************************************************************"
		

def imprime_todos_blocos():
	for blocos in lista_blocos:
		indice = 0
		while (indice < len(blocos)):
			imprime_bloco(blocos[indice])
			indice = indice + 1


def imprime_blocos_final(lista):
	for bloco in lista:
		imprime_bloco(bloco)


"""This function converts the graph in the graphml format """


def passa_graphml(edges,nodes):
	
	# Init the xml file
	doc = Document()

	# Creates the base element
	elem_graphml = doc.createElement("graphml") 
	elem_graphml.setAttribute("xmlns","http://graphml.graphdrawing.org/xmlns")
	elem_graphml.setAttribute("xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance")
	elem_graphml.setAttribute("xsi:schemaLocation","http://graphml.graphdrawing.org/xmlns	http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd")
	doc.appendChild(elem_graphml)

	#Key WCEC
	key_k0 = doc.createElement("key") 
	key_k0.setAttribute("id","k0") 	
	key_k0.setAttribute("attr.name","wcec") 
	key_k0.setAttribute("attr.type","int") 
	key_k0.setAttribute("for","node") 

	valor_default = doc.createTextNode("0")
	default = doc.createElement("default")
	default.appendChild(valor_default)	
 
	key_k0.appendChild(default)
	elem_graphml.appendChild(key_k0)

	#Key Block Type
	key_k1 = doc.createElement("key") 
	key_k1.setAttribute("id","k1") 	
	key_k1.setAttribute("attr.name","type") 
	key_k1.setAttribute("attr.type","string") 
	key_k1.setAttribute("for","node") 


	valor_default = doc.createTextNode("normal")
	default = doc.createElement("default")
	default.appendChild(valor_default)	
 
	key_k1.appendChild(default)
	elem_graphml.appendChild(key_k1)

	#Key "max_loops" Max cycles of the Bloco (Apenas Blocos que sao Loops)
	key_k2 = doc.createElement("key") 
	key_k2.setAttribute("id","k2") 	
	key_k2.setAttribute("attr.name","max_loops") 
	key_k2.setAttribute("attr.type","int") 
	key_k2.setAttribute("for","node") 


	valor_default = doc.createTextNode("1")
	default = doc.createElement("default")
	default.appendChild(valor_default)	
 
	key_k2.appendChild(default)
	elem_graphml.appendChild(key_k2)

	#Key "RWCEC" to edges
	key_k3 = doc.createElement("key") 
	key_k3.setAttribute("id","k3") 	
	key_k3.setAttribute("attr.name","rwcec") 
	key_k3.setAttribute("attr.type","int") 
	key_k3.setAttribute("for","edge") 


	valor_default = doc.createTextNode("-1")
	default = doc.createElement("default")
	default.appendChild(valor_default)	
 
	key_k3.appendChild(default)
	elem_graphml.appendChild(key_k3)
	

	#Key Line_Block
	key_k4 = doc.createElement("key") 
	key_k4.setAttribute("id","k4") 	
	key_k4.setAttribute("attr.name","line") 
	key_k4.setAttribute("attr.type","int") 
	key_k4.setAttribute("for","node") 


	valor_default = doc.createTextNode("-1")
	default = doc.createElement("default")
	default.appendChild(valor_default)	
 
	key_k4.appendChild(default)
	elem_graphml.appendChild(key_k4)
	
	#Key Last_Line_Block
	key_k6 = doc.createElement("key") 
	key_k6.setAttribute("id","k6") 	
	key_k6.setAttribute("attr.name","last_line") 
	key_k6.setAttribute("attr.type","int") 
	key_k6.setAttribute("for","node") 


	valor_default = doc.createTextNode("-1")
	default = doc.createElement("default")
	default.appendChild(valor_default)	
 
	key_k6.appendChild(default)
	elem_graphml.appendChild(key_k6)
	
	
	#Key Loop WCEC
	key_k5 = doc.createElement("key") 
	key_k5.setAttribute("id","k5") 	
	key_k5.setAttribute("attr.name","loop_wcec") 
	key_k5.setAttribute("attr.type","int") 
	key_k5.setAttribute("for","node") 
	
	valor_default = doc.createTextNode("0")
	default = doc.createElement("default")
	default.appendChild(valor_default)	
	key_k5.appendChild(default)
	elem_graphml.appendChild(key_k5)
	
	

	# Creates one graphml element, because it's possible to have many graphs in the same graphml.xml format
	grafo = doc.createElement("graph")
	
	grafo.setAttribute("id", "G")
	grafo.setAttribute("edgedefault","directed")		
	elem_graphml.appendChild(grafo)
	
	node_init = get_node_init()
	node_final = get_node_final()

	#To nodes
	indice = 0
	for node in nodes:
		loops = -1
		
		data = doc.createElement("data")
		data.setAttribute("key","k0")

		wcec = str(node.wcec)
		valor_wcec = doc.createTextNode(wcec)
		data.appendChild(valor_wcec)

		tipo = doc.createElement("data")
		tipo.setAttribute("key","k1")

		key4 = doc.createElement("data")
		key4.setAttribute("key","k4")

		valor_line = str(node.linhas[0])
		line = doc.createTextNode(valor_line)
		key4.appendChild(line)	
		
		key6 = doc.createElement("data")
		key6.setAttribute("key","k6")

		valor_line = str(node.linhas[-1])
		line = doc.createTextNode(valor_line)
		key6.appendChild(line)	
	
		#type of the block
		if (node.tipo.find("if") >= 0) :
			aux = "if"
		elif (node.tipo.find("for") >= 0):
			aux = "for"
			loops = node.loops
		elif (node.tipo.find("while") >= 0):
			aux = "while"
			loops = node.loops
		else:
			aux = "normal"


		tipo_bloco = aux
		string_tipo = doc.createTextNode(tipo_bloco)
		tipo.appendChild(string_tipo)

			
		bloco = doc.createElement("node")
		if (node_init == indice):
			bloco.setAttribute("id","I" + str(indice))
		elif  (node_final == indice):
			bloco.setAttribute("id","F" + str(indice))
		else:
			bloco.setAttribute("id","N" + str(indice))
		bloco.appendChild(data)
		bloco.appendChild(tipo)

		if not(loops == -1):
			number_loops = doc.createTextNode(loops)
			max_loops = doc.createElement("data")
			max_loops.setAttribute("key","k2")
			max_loops.appendChild(number_loops)
			bloco.appendChild(max_loops)
			
			loopwcec_aux = doc.createTextNode("0")
			loopwcec = doc.createElement("data")
			loopwcec.setAttribute("key","k5")
			loopwcec.appendChild(loopwcec_aux)
			bloco.appendChild(loopwcec)
			
		
		bloco.appendChild(key4)
		bloco.appendChild(key6)
		
		grafo.appendChild(bloco)
		indice = indice + 1
	
	#Creates the edges
	indice = 0
	for edge in edges:
					
		number_rwcec = doc.createTextNode("-1")
		rwcec = doc.createElement("data")
		rwcec.setAttribute("key","k3")
		rwcec.appendChild(number_rwcec)

		aresta = doc.createElement("edge")
		aresta.setAttribute("id","E"+str(indice))
		
		if edge[0] == node_init:
			string_idNode_source = "I"+str(edge[0])
		elif edge[0] == node_final:
			string_idNode_source = "F"+str(edge[0])
		else:
			string_idNode_source = "N"+str(edge[0])

		if edge[1] == node_init:
			string_idNode_target = "I"+str(edge[1])
		elif edge[1] == node_final:
			string_idNode_target = "F"+str(edge[1])
		else:
			string_idNode_target = "N"+str(edge[1])
		
		aresta.setAttribute("source",string_idNode_source)
		aresta.setAttribute("target",string_idNode_target)
		aresta.appendChild(rwcec)


		grafo.appendChild(aresta)
		indice = indice + 1
	
		


	return doc

"""Class Block
@ident is the name of the block
@c is the C code of the Block
@assembly is the Assembly Code of the block (with debug information)
@funcao is the funcion that the block is insert
@tipo is the type of the block ("if", "while", etc)
@wcec is the WCEC of the block
@rwcec is the Remaining Worst Case Execution Cycles of the block
@linhas ares the lines of the C code that are passed to function that returns the ASM code
@loops is the max number of iteration of a block ("while" and "for")

"""

class bloco:
	ident = "" 		
	c = "" 			
	assembly = ""
	funcao = ""		
	tipo = "default"	
	wcec = 0
	rwcec = 0
	linhas = []
	loops = 0


	
#These declaration are global variables
lista_funcoes = []
lista_tipos = ["void","int","float","double","char","long"]
lista_tipos = complementa_tipos(lista_tipos)
lista_desvios = ["if","while","do","for","break","switch","case","default"]
lista_stops = lista_desvios
lista_stops.append("}")
lista_stops.append("{")
lista_blocos = []


#These switchs works like switch in a C code

switch_bloco = {
	"if": "if",
	"else": "else",
	"{": "inicio",
	"}": "fim",
	"while": "while",
	"for": "for",
	"do": "do",
	"break" : "break",
	"switch" : "switch",
	"case" : "case",
	"default" : "default",
   
}	

switch_exec = {
	"inicio": func_inicio ,
	"inicio if": func_inicio_if ,
	"if": func_if ,
	"inicio fim": func_inicio_fim ,
	"fim": func_fim ,
	"else": func_else ,
	"else fim": func_else_fim ,
	"else if": func_else_if ,
	"while": func_while ,
	"for": func_for ,
	"Normal Block fim": func_normal_fim ,
	"Normal Block if": func_normal_if ,
	"Normal Block": func_normal ,	
	"inicio break": func_inicio_break ,
	"break" : func_break,
	"switch" : func_switch,
	"case" : func_case,
	"default" : func_default,
}


#These functions works with the module C-to-ASM, and they are useful to get the WCEC 
	
def get_asm_to_wcec(dict_afc,keys_afc,list_lines):
	string_asm = ""
	for key in keys_afc:
		for lines in list_lines:
			if (lines == key):
				string_asm = string_asm + get_str(dict_afc[key][1:])
				break
			else:
				if (key > list_lines[-1]):
					return string_asm
	return string_asm


def get_str(lista):
	string = ""
	for word in lista:
		string = string + word + " "
	return string

	
"""Execution of the Python Code """


"""Openning the ASM FILE """
import sys
from sys import path
path.append('./Calculate-WCEC')
path.append('./Script-Asm-C')

import calculate_wcec
import asmfc

from calculate_wcec import *
from asmfc import *
from xml.dom.minidom import Document



if __name__ == '__main__':
	import sys

	argv = sys.argv
	if len(argv) > 1:
		sfile = argv[1]
	else:
		print "\nExpected asm_file is missing.\n"
		print "Usage: %s <asm_file>\n" % argv[0]
		sys.exit(1)

	afc_dict = get_afc_dict(sfile)
	afc_keys = afc_dict.keys()
	afc_keys.sort()
	#print afc_dict
	cfile = get_c_file(sfile)
	print "Arquivo C: %s\n\n"%cfile

	"""Build of the graph """
	wcec_table = init_wcec_table()
	caminho = "grafoteste.c"
	linhas = abre_arquivo(caminho)

	get_all_blocks(linhas)

	print lista_funcoes
	lista = build_graph(lista_blocos)
	lista_blocos = lista[0]
	arestas =  lista[1]

	#Print all blocks and yours information details: (Based of the graph of each function)

	imprime_todos_blocos()
	#print arestas

	#Cria o grafo final (grafo que sera executado)
	lista = build_func(lista_blocos,arestas)
	arestas = lista[0]
	
	lista_blocos = lista[1]

	#These print is different, they print the graph that will be executed
	#imprime_blocos_final(lista[1])
	
	"""Graph to graphml.xml format """
	graphml = passa_graphml(arestas,lista_blocos)
	arq_gerado = open("graphml.xml","w")
	arq_gerado.write(graphml.toprettyxml(indent="	"));
	arq_gerado.close()

	print arestas

	print lista_funcoes
	
