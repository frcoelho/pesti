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

#include <stdlib.h>

/***
*/

typedef struct range_probability{
	double prob_start;
	double prob_finish;
	unsigned char probability_density_function;
} trange_probability;

/***
*/

typedef struct list_prob_switch{
	trange_probability case_probability;
	struct list_prob_switch *next;
} tlist_prob_switch;

/***
	 Struct that stores information about energy and clock-cycle consumption
*/
typedef struct node{
	char id[5];
	unsigned int clock_cycles;
	unsigned int consumed_cycles;
	double energy;	
	double consumed_energy;	
} tnode ;

/***
	Struct that represents a cfg's generic block. 
	Field class_node indicates if the block is branch, loop, switch, case or normal block
	Field node points to a struct that represents one of structs: loop, branch, switch, case, etc.
*/
typedef struct block{
	tnode info_node;
	char class_node;
	void *node;
	struct block *next_block;
	unsigned int timesexec;
} tblock;

/***
	 Struct that represents a sequential node of control flow graph, i.e just is connected to another node
*/
typedef struct sequential_node{
	tblock *next_node;
} tsequential_node;

/***
	Struct that represents every one of the if's or while's clauses 
*/
typedef struct condition{
	trange_probability probability;
	tnode info_cond;
	unsigned int timesexec;
} tcondition;

/***
*/
typedef struct tree_express{
	char   idnode;
	struct tree_express *right;
	struct tree_express *left;
	struct tree_express *next;
	struct tree_express *parent;
	tcondition *clause;
} ttree_express;

/***
*/
typedef struct clauses_cond{
	unsigned int qtclauses;
	tcondition *lconditions;
	ttree_express *root_express;
	char bexpress[100];	
} tclauses_cond;


/***
	 Struct that represents a branch node, i.e a IF with THEN and/or ELSE
*/
typedef struct branch_node{
	tblock *then_node;
	tblock *else_node;
	tclauses_cond *clauses; 
} tbranch_node;


/***
	 Struct that represents a loop node wich is connected to two others node, a node of exit loop and a node that is inside the loop
*/
typedef struct loop_node{
	trange_probability probability;	
	tblock *next_node;
	tblock *exit_node;
	char idloop[8];
	unsigned char running;
	unsigned char type_loop;
	unsigned int nrloops;
	tclauses_cond *clauses; 
} tloop_node;


/***
	 Struct that represents a node that is inside a case node
*/
typedef struct case_node{
	tblock *next_node;
} tcase_node;


typedef struct switch_case{
	tblock *node_case;
	struct switch_case *next_case;
} tswitch_case;

/***
	 Struct that represents a switch node
*/
typedef struct branch_switch_node{
	tswitch_case *first_case;
	tswitch_case *last_case;
	trange_probability *prob_cases;
	int qtcases;
} tbranch_switch_node;





