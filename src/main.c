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

int main(int argc, char *argv[])
{
        time_t     inicio, fim;
	struct tm  ts;
	char       buf[80];

	// Obtem o tempo corrente
	time(&inicio);

	puts("Loading CFG\n");
	loadCfg(argv[1]);
	puts("Simulating CFG\n");
	//printf("no raiz: %s\n", start_block->info_node.id);
	runCfg(start_block, atoi(argv[2]), atof(argv[3]), atof(argv[4]));
	puts("Listing CFG\n");
	listNodes(start_block);

	time(&fim);

	printf("Tempo total de simulação: %11.3f segundo(s)\n", difftime(fim, inicio));

	return 0;
}

