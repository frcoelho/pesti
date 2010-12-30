/***
	This program is under GPL Licence
	Project: "C-Code energy estimation of embedded systems"
	Coordinator: Prof. Dr. Raimundo Barreto - UFAM
	Co-Coordinator: Prof. Dr. Meuse Nogueira - CEFET (PE)

	Author: Carlos Mar, Master student of Federal University of Amazonas (UFAM)
	E-mail: carlos.augusto.mar@gmail.com / caam@dcc.ufam.edu.br
	History:
	2007-14-1: version 0.1 implemented
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <headers-functions.h>

/***
	Global variables imported from control-flow-graph.c
*/

extern tblock *start_block;
extern tblock *end_block;

extern double start_range, end_range, step;

void setup(double finish)
{
	tblock *ptr;
	int i;

	ptr = start_block;
	while (ptr) {
		switch (ptr->class_node) {
		case 49: // branch node
			{
				tbranch_node *node = ptr->node;
				ttree_express *expr = node->clauses->root_express;
				expr->clause->probability.prob_finish = finish;
				break;
			}
		case 50: // loop node
			{
				tloop_node *node = ptr->node;
				if (node->type_loop == '2')
					node->probability.prob_finish = finish;
				break;
			}
		case 51: // switch node
			{
				tbranch_switch_node *node = ptr->node;
				for (i = 0; i < node->qtcases; i++)
					node->prob_cases[i].prob_finish = finish;
				break;
			}
		}
		ptr = ptr->next_block;
	}
}

int main(int argc, char *argv[])
{
        time_t     inicio, fim;
	struct tm  ts;
	char       buf[80];
	double i;

	if (argc != 5) {
		printf("Usage: %s <CFG> <iterations> <error> <confidence>\n",
				argv[0]);
		exit(-1);
	}
	// Obtem o tempo corrente
	time(&inicio);

	puts("Loading CFG\n");
	loadCfg(argv[1]);
	//printf("no raiz: %s\n", start_block->info_node.id);

	for (i = start_range; i <= end_range; i += step) {
		setup(i);
		printf("Simulating CFG (finish=%f)\n", i);
		runCfg(start_block, atoi(argv[2]), atof(argv[3]), atof(argv[4]));
		printf("Listing CFG (finish=%f)\n", i);
		listNodes(start_block, i);
	}

	time(&fim);

	printf("Tempo total de simulação: %11.3f segundo(s)\n", difftime(fim, inicio));

	return 0;
}

