##	This script should be called from command line as follows: python result-extractor <nmfile-witho-no-extension> <number of files>. 
##	e.g.: python result-extractor bolha 2
##	At the end of execution it produces a csv file with information about total time simulation (in cycles) for programs <nmfile-witho-no-extension>. 
##	This results are provided by SimpleScalar toolset (sim-outoforder)
##	It should be executed inside directory where are located outputs from SimpleScalar simulation

import os, glob, shutil, math
from random import *
import re




def bubblesort(numbers):

	i = len(numbers)-1
	count=0
	while(i>=0):
		j=1
		while(j<=i):
			if (numbers[j-1] > numbers[j]):
			        temp = numbers[j-1];
			        numbers[j-1] = numbers[j];
			        numbers[j] = temp;
			j = j+1
		i = i-1				


array_cycle = []

psim_cycle = re.compile('sim_cycle')
vsim_cycle = re.compile(r'\d+')

#sim_cycle = open('simple-scalar.csv', 'w')
#sim_cycle.write('PROGRAM;TOTAL_CYCLES\n')



if __name__ == '__main__':
	import sys

	argv = sys.argv

	simul = []
	pesti = open(argv[1])

	sample = pesti.readlines()
	pesti.close()

	for elem in sample:
		energy = elem.split(":")[0].strip()
		#if(float(energy) >= 83477.0):
		simul.append(float(energy))


	bubblesort(simul)
	len_simul = len(simul)
	Range = simul[len_simul-1] - simul[0]
	K = int(math.ceil(1+3.22*math.log10(len_simul))) * 2
	h = math.ceil(float(Range) / float(K))
#	h=176
	print "h"
	print h
	classes = []
	iclass = simul[0]		# elemento do conjunto que possui menor valor
	c = 1
	while((c <= K) and (h !=0 )):
		classes.append([iclass, iclass + h, 0])
		iclass = iclass + h
		c = c + 1

	if (len(classes) == 0):
		classes.append([iclass, iclass + 1, 0])

	for item in simul:
		for elem in classes:
			if (item >= elem[0] and item < elem[1]):
				elem[2] = elem[2] + 1
				break

	for elem in classes:
		elem[2] = (float(elem[2]) / float(len_simul))*100

	prob_sample = open('pesti-results.csv', 'w')
	prob_sample.write('CLASS;FREQ\n')

	for elem in classes:
		prob_sample.write(str(elem[0])  + '-' + str(elem[1])+';'+str(elem[2])+'\n') #
	
	prob_sample.close()

			






