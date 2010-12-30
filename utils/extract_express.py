# This program is under GPL Licence
#Project: "Gerencia de Consumo de Energia em Ambientes de Codigo Aberto" - UFAM - INdT
#Coordinator: Dr. Prof. Raimundo Barreto - UFAM

#Code: 

#Author: Carlos Mar - UFAM -----   carlos.augusto.mar@gmail.com / caam@dcc.ufam.edu.br
#History: 
# 2008-15-01: version 0.2 implemented

import re

# This function converts variables names and constants in simple symbols. For example: vl_Payment == 50.00 becomes V == K
# This way is very simple to apply reverse polonish algorithm
def justSimpleSymbols(exp):

	er = ""
	exp_r = re.sub(r"if ", r"", exp)
	exp_r = re.sub(r"[a-zA-Z](_*[a-zA-Z]*[0-9]*)*", r"V", exp_r)
	exp_r = re.sub(r"\d+\.\d*", r"K", exp_r)
	exp_r = re.sub(r"\d+", r"K", exp_r)
	exp_r = re.sub(r"V\[\V\]" "|V\[\K\]", r"V", exp_r)
	exp_r = exp_r.split(" ")
	if (len(exp_r) > 0):
		for it in exp_r:
			if (len(it) > 0):
				er = er +  it
	else: er = exp_r

	return er

	  
# This function formats expression with comparators operators in a boolean expression, removing clauses like V == V, V != V, etc.
#
def justBooleanExpress(exp):

	exp_r = exp
	result = []
	letter = 65
	parser = re.compile('[A-Z]==[A-Z]' '|[A-Z]!=[A-Z]' '|[A-Z]>[A-Z]' '|[A-Z]<[A-Z]' '|[A-Z]>=[A-Z]' '|[A-Z]<=[A-Z]' '|[A-Z]')
	operators = parser.findall(exp_r)
	
	for item in operators:
		exp_r = exp_r.replace(item, chr(letter), 1)
		result.append([item, chr(letter)])
		letter = letter + 1
	result.append(exp_r)

	return result
	 

