# This program is under GPL Licence
#Project: "Gerencia de Consumo de Energia em Ambientes de Codigo Aberto" - UFAM - INdT
#Coordinator: Dr. Prof. Raimundo Barreto - UFAM

#Code: Generator of Control Flow Graph from a C code (Jonatas) with WCEC (Carlos Bruno) 

#Author: Carlos A. Mar - UFAM -----   carlos.augusto.mar@gmail.com / caam@dcc.ufam.edu.br
#History: 
# 2008-17-01: version 0.2 implemented

import extract_express

from extract_express import *

def ObterPrioridade(caracter):
	retorno= 0
	pri2 = "~"
	pri3 = "*"
	pri4 = "+"

	if(caracter.find("(") >= 0):
		retorno = 1
	elif(pri2.find(caracter) >= 0):
		retorno = 4
	elif(pri3.find(caracter) >= 0):
		retorno = 3
	elif(pri4.find(caracter) >= 0):
		retorno = 2

	return retorno;

def IsOperando(caracter):
	letras = "ABCDEFGHIJKLMNOPQRSTUVXZ"
	return (letras.find(caracter) >= 0)

def IsOperador(caracter):
	operadores = "~*+"
	return (operadores.find(caracter) >= 0)

def trocarOperador(bexp):
	bexp = bexp.replace("&&", "*")
	bexp = bexp.replace("||", "+")
	bexp = bexp.replace("!", "")

	return bexp

def converterPosFixa(expInfixa):
	resultado = "";
	pilha = []
	caracter = ""
	prioridade = 0;

	bexp = trocarOperador(expInfixa)
	print "Nova expressao: " + bexp
	for caracter in bexp:

		if (IsOperando(caracter)):
			resultado += caracter
		elif (IsOperador(caracter)):
			prioridade = ObterPrioridade(caracter)
			for e in pilha:
			    if (ObterPrioridade(e) >= prioridade):
				resultado += e
				pilha.remove(e)
			    else: break
			pilha.insert(0, caracter)
		elif (caracter.find("(") >= 0):
			pilha.insert(0, caracter)
		elif (caracter.find(")") >= 0):
			item = pilha.pop(0)
			while (item != "("):
				resultado += item
				item = pilha.pop(0)

	while (len(pilha) > 0):
		resultado += pilha.pop(0)

	return resultado

