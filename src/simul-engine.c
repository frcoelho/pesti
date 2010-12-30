/***
	This program is under GPL Licence
	Project: "C-Code energy estimation of embedded systems"
	Coordinator: Prof. Dr. Raimundo Barreto - UFAM
	Co-Coordinator: Prof. Dr. Meuse Nogueira - CEFET (PE)

	Author: Carlos Mar, Master student of Federal University of Amazonas (UFAM)
	E-mail: caam@dcc.ufam.edu.br / carlos.augusto.mar@gmail.com
	History:
	2007-14-1: version 0.1 implemented
*/


#include <time.h>
#include <headers-functions.h>

#define  	PENALTY		3

/***
	Global variables imported from control-flow-graph.c
*/
extern tblock *start_block;
extern tblock *end_block;



/***
*/
tblock *runCase(tblock *current, double prob)
{
	tswitch_case *case_node=NULL;
	tbranch_switch_node *switch_node=NULL;
	int i=0, j=0, flsearch=0;


	switch_node = ((tbranch_switch_node *) (current->node));

	while ((i < switch_node->qtcases) && (!flsearch))
	{
		flsearch = ((prob >= switch_node->prob_cases[i].prob_start) && (prob <= switch_node->prob_cases[i].prob_finish));
		i++;
	}

	if (flsearch){
		i--;
		case_node = switch_node->first_case;
		for(j=0; j < i; j++)
			case_node = case_node->next_case;
		return (case_node->node_case);
	}
	else return NULL;
}

/***
*/
int evalluableExpress(ttree_express *root, double *energycost, double *cyclecost){
	int result, flag=0;
	double p;

	if (root){
		result = evalluableExpress(root->left, energycost, cyclecost);
		switch(root->idnode){
			case '*':{
					if (result==0)
						flag = 1;
			} break;
			case '+':{
					if (result==1)
						flag=1;
			} break;
			default: {
					p = (double) ((randNumber(0.0, 1.0)));
					if ((p >= root->clause->probability.prob_start) && (p <= root->clause->probability.prob_finish) && (p != 0.0))
						result = 1;
					else result = 0;
					root->clause->info_cond.consumed_cycles += root->clause->info_cond.clock_cycles;
					root->clause->info_cond.consumed_energy += root->clause->info_cond.energy;
					root->clause->timesexec++;
					*energycost = *energycost + root->clause->info_cond.energy; //root->clause->info_cond.consumed_energy;
					*cyclecost = *cyclecost + root->clause->info_cond.clock_cycles;
					flag=1;
				}
		}
		if (flag)
			return(result);
		else {
			result = evalluableExpress(root->right, energycost, cyclecost);
			return(result);
		}
	}
	else return(3);
}




/***
*/
tblock *runBranch(tbranch_node *branch, double *energycost, double *cyclecost)
{
	int bpath;

	bpath = evalluableExpress(branch->clauses->root_express, energycost, cyclecost);
	//printf("BPATH: %d\n", bpath);
	if (bpath != 0){
		*cyclecost = *cyclecost+PENALTY; // penalidade para cache miss. Esta sendo utilizada uma penalidade de 4 ciclos de clock sempre que o branch e tomado
		return (branch->then_node);
	}
	else return (branch->else_node);

}


/***
	This function simulates loop execution (for, while)
*/
tblock *runLoop(tloop_node *loop, double *energycost, double *cyclecost)
{
	unsigned int times;
	unsigned int lpath;

	// check if loop is running. 0: stoped - 1: running
	if (!loop->running){
		switch (loop->type_loop){
			case '1': {	// loop FOR with max iteration defined previous
					loop->nrloops = loop->probability.prob_finish+1;
					//*cost = *cost + PENALTY; // penalidade de cache miss (in assembly is a jump)
				} break;
			case '2': {     // loop FOR with max iteration defined by probabilities
					times =  ((int) (randNumber(loop->probability.prob_start, loop->probability.prob_finish)));
					loop->nrloops = times+1;
					//*cost = *cost + PENALTY; // penalidade de cache miss (in assembly is a jump)
				} break;
			case '3': loop->nrloops = 0; break; // LOOP While
		}
		loop->running = 1; // to start loop
	}

	if (loop->running == 1){
		if (loop->type_loop == '3'){
			loop->nrloops++;
			lpath = evalluableExpress(loop->clauses->root_express, energycost, cyclecost);	// Evalluate while express condition
			// Go inside the loop
			if (lpath)
				return(loop->next_node);
			else {
				// exit loop
				loop->running = 0;
				*cyclecost = *cyclecost + PENALTY; // penalidade de cache miss
				return(loop->exit_node);
			}
		} else {
			loop->nrloops--;
			// Go inside loop FOR
			if (loop->nrloops > 0)
				return (loop->next_node);
			else{
				// exit loop FOR
				loop->running = 0;
				*cyclecost = *cyclecost + PENALTY; // penalidade de cache miss
				return(loop->exit_node);
			}
		}
	}
}


/***
	This function executes cfg's simulation
	start_graph: Pointer to cfg's start block.
*/
//void runCfg(tblock *start_graph, tblock *end_graph, unsigned int nrexecutions, double max_err, double confidence)
void runCfg(tblock *start_graph, unsigned int nrexecutions, double max_err, double confidence)
{
	tblock *start;
	unsigned int j, nrsimulations=0;
	double p, energy_one_path, cycles_one_path;
	// seed for generating random number
	srand(time(0));
	do{
	   for (j=1; j <= nrexecutions; j++){
		start = start_graph;
		energy_one_path = 0.0;
		cycles_one_path = 0.0;
		while(start){
			start->info_node.consumed_energy += start->info_node.energy;
			start->info_node.consumed_cycles += start->info_node.clock_cycles;
			start->timesexec++;
			energy_one_path += start->info_node.energy;
			cycles_one_path += start->info_node.clock_cycles;
			//printf("no atual: %s	iteracao: %d classe: %d\n", start->info_node.id, j, start->class_node);
			switch(start->class_node){
				case 48:{ // sequential node
					start = ((tsequential_node *) (start->node))->next_node;
				} break;
				case 49:{ // branch node
						tbranch_node *branch = (tbranch_node *) start->node;
						//printf("EXpressao: %s\n", branch->bexpress);
						start = runBranch(branch, &energy_one_path, &cycles_one_path);
				} break;
				case 50:{ // loop node
						tloop_node *loop = (tloop_node *) start->node;
						start = runLoop(loop, &energy_one_path, &cycles_one_path);
				} break;
				case 51:{ // switch node
					p = (double) ((int) (100 * randNumber(0.0, 1.0)))/100.0;
					printf("Switch Prob.: %g\n", p);
					start = runCase(start, p);
				} break;
				case 52:{ // case node
					start = ((tcase_node *) (start->node))->next_node;
				} break;
			}
		}
		addSample(energy_one_path, cycles_one_path);
    	}
	nrsimulations++;
     } while (!stopSimulation ( (double) (nrsimulations*nrexecutions), max_err, confidence));

	dumpStatistics();
	freeSample();
}


