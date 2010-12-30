# This program is under GPL Licence
#Project: "Gerencia de Consumo de Energia em Ambientes de Codigo Aberto" - UFAM - INdT
#Coordinator: Dr. Prof. Raimundo Barreto - UFAM

#Code: Generator of Control Flow Graph from a C code (Jonatas) with WCEC (Carlos Bruno) 

#Author: Jonatas Costa de Oliveira - UFAM -----   jonatasoli@gmail.com / jco@dcc.ufam.edu.br
#History: 
# 2007-14-05: version 0.2 implemented

r"""This code aims to generate the flow graph from a C Code in the graphml format, more informations in README

	ps: Some coments, especialy "prints", are useful to tests"""

def buildGroupsInstructions(nmarquivo):
	arqinst = open(nmarquivo, "r")
	linhas = arqinst.readlines()
	arqinst.close()

	linst = []
	for i in range(0, 3):
		linst.append(linhas[i].strip().split(";"))

	return (linst)

def buildMatrizCost(nmarquivo):
	arqinst = open(nmarquivo, "r")
	linhas = arqinst.readlines()
	arqinst.close()

	linst = []
	for i in range(3, len(linhas)):
		strcusto = linhas[i].strip().split(";")
		fcusto = []
		print strcusto
		for custo in strcusto:
			fcusto.append(float(custo))
		linst.append(fcusto)

	return (linst)

def findInstruction(instruction):

	local = -1
	for i in range(0, 3):
		cont = instrucoes[i].count(instruction)
		if (cont > 0):
			local = i
			break
	return (local)
	
	

if __name__ == '__main__':
	import sys

	argv = sys.argv


	instrucoes = buildGroupsInstructions(argv[1])
	matrizcusto = buildMatrizCost(argv[1])
	print matrizcusto
	inst1 = findInst(argv[2])
	inst2 = findInst(argv[3])

	print matrizcusto[inst1][inst2]
