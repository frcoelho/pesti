# *************************************************************************************
# -CURSO: Engenharia da Computacao --
# Obs.: Estudante na UFAM
# ***
# Carlos Bruno Oliveira Lopes 
# ***
# --- versao 0.2 ---
# 
# -Funcao: Calcula o ciclo de execucao do pior caso por bloco --
# ************************************************************************************


def init_wcec_table(tabAsm):
	# endereco de memoria para o arquivo
	pont = open (tabAsm, 'r')
	linesofile = pont.readlines()
	tab = {}
	for e in linesofile:
		elem = e.split()
		tab[str.upper(elem[0])] = [int(elem[1].strip()), float(elem[2].strip())]
	return tab

# /* funcao que calcula o WCEC */
def cal_wcec (linst, wcec_table):	
	
	wcec = 0;
	for e in linst:
		if (wcec_table.get(str.upper(e))!=None):
			wcec = wcec + wcec_table[str.upper(e)][1]

	return (wcec)

# /* funcao que calcula o WCEC */
def cal_energy (linst, wcec_table):	
	
	energy = 0;
	for e in linst:
		if (wcec_table.get(str.upper(e))!=None):
			energy = energy + wcec_table[str.upper(e)][1]

	return (energy)

# procura a instrucao na lista de instrucoes para usar seu indice na tabela de custo de efeito inter instrucao
def findInstruction(instruction, instrucoes):

	local = -1
	for i in range(0, 7):
		cont = instrucoes[i].count(instruction)
		if (cont > 0):
			local = i
			break
	return (local)

# calcula o custo energetico do efeito inster instrucao
def cal_insteffect_energy(linst, instrucoes, effect_table):
	custo=0.0
	if (len(linst)>0):
		inst1 = linst[0].strip().upper()
		#custo = custo + (-0.784)
		for i in range(1, len(linst)):
			i1 = findInstruction(inst1, instrucoes)
			i2 = findInstruction(linst[i].strip().upper(), instrucoes)
			if (i1 >=0 and i2 >=0):
				custo = custo + effect_table[i1][i2]
			else:
				print inst1 + "/" + linst[i].strip().upper()	 
			inst1=linst[i].strip().upper()	
	return(custo)

def is_empty_cycle(ainst):
	for e in ainst:
		if (e > 0):
			return (1)
	return (0)

# function que calcula o wcec de cada bloco levando em conta o tamanho do pipeline do processador considerado
def cal_wcec_pipeline (linst, ibloco, wcec_table, tampipe):	
	cycle_inst = []
	for e in linst:
		if (wcec_table.get(str.upper(e))!=None):
			cycle_inst.append(wcec_table.get(str.upper(e))[0])
		else: print str.upper(e)
	if (len(cycle_inst)>0):
		cycles_ibloco = cycle_inst[ibloco]
	else: cycles_ibloco = 0
	cycles=0
	cycle_ibloco = 0
	while (is_empty_cycle(cycle_inst)==1):
		if (cycles > len(cycle_inst)):
			upperbound = len(cycle_inst)
		else: upperbound = cycles

		i=0
		pipe=1
		while(i<upperbound):
			if ((cycle_inst[i] > 0) and (pipe <= tampipe)): # pipe <= 6. O 6 pode ser transformado em parametro e corresponderia ao tamanho do pipeline
				cycle_inst[i] = cycle_inst[i] - 1
				pipe = pipe+1			

			i = i + 1
		cycles = cycles + 1

		if ((cycle_inst[ibloco] != cycles_ibloco) and (cycle_ibloco==0)):
			cycle_ibloco = cycles	

	return (cycles-cycle_ibloco)




