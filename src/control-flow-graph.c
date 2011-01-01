/***
	This program is under GPL Licence
	Project: "C-Code energy estimation of embedded systems"
	Coordinator: Prof. Dr. Raimundo Barreto - UFAM
	Co-Coordinator: Prof. Dr. Meuse Nogueira - CEFET (PE)

	Author: Carlos Mar, Master student of Federal University of Amazonas (UFAM)
	E-mail: carlos.augusto.mar@gmail.com / caam@dcc.ufam.edu.br
	History:
	2007-11-11: version 0.1 implemented
*/

#include <control-flow-graph.h>
#include <string.h>
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

tblock *start_block = NULL;
tblock *end_block = NULL;

double start_range, end_range, step;

/***
	getElement: This function returns a node that contais a set of nodes or edges
	node: Cfg xml file's root node
	tagname: Tag's name of the set of nodes or edges
*/
int  countElement(xmlNode *node, const char *tagname)
{
	int qt=0;
	xmlNode *current = NULL;

	if (!strcmp((char *)node->name, tagname))
		return 0;
	else {
		current = node->children;
		while(current)
		{
			if (!strcmp((char *)current->name, tagname))
				qt++;;

			current = current->next;
		}
	}

	return (qt);
}



/***
	getElement: This function returns a node that contais a set of nodes or edges
	node: Cfg xml file's root node
	tagname: Tag's name of the set of nodes or edges
*/
xmlNode *getElement(xmlNode *node, const char *tagname)
{
	xmlNode *current = NULL;

	if (!strcmp((char *)node->name, tagname))
		return node;
	else {
		current = node->children;
		while(current)
		{
			if (!strcmp((char *)current->name, tagname))
				return(current);

			current = current->next;
		}
	}

	return NULL;
}


/***
	getAttr: Returns the value of attribute attr from current xmlNode
	current: Current node from DOM tree
	attr: Attribute's name wich value will be returned
	Return: A value, represented by a char pointer, of attribute attr or NULL value
*/
char *getAttr(xmlNode *current, const char *attr)
{
	xmlAttr *lAttr;
	char *property = NULL;

	lAttr = current->properties;

	while ((lAttr) && (!property))
	{
            	if( strcmp( (char*)lAttr->name, attr ) == 0 )
                    property = (char*) xmlGetProp(current, lAttr->name);

            	lAttr = lAttr-> next;
	}

	return (property);
}


/***
	getAttrStr: Returns the value of attribute attr from current xmlNode
	current: Current node from DOM tree
	attr: Attribute's name wich value will be returned
	Return: A value, represented by a char pointer, of attribute attr or NULL value
*/
char *getAttrStr(xmlNode *current, const char *attr)
{
	return (getAttr(current, attr));
}


/***
	getAttrChr: Returns the value (char) of attribute attr from current xmlNode
	current: Current node from DOM tree
	attr: Attribute's name wich value will be returned
	Return: A value, represented by a char, of attribute attr or "" value
*/
char getAttrChr(xmlNode *current, const char *attr)
{
	char *property, ret;

	property = getAttr(current, attr);

	if (property && strlen(property) > 0)
		ret = property[0];
	else
		ret = 0;

	free(property);

	return ret;
}


/***
	getAttrInt: Returns the value (int) of attribute attr from current xmlNode
	current: Current node from DOM tree
	attr: Attribute's name wich value will be returned
	Return: A value, represented by a int, of attribute attr or 0 value
*/
int getAttrInt(xmlNode *current, const char *attr)
{
	char *property;
	int ret;

	property = getAttr(current, attr);

	if (property && strlen(property) > 0)
		ret = atoi(property);
	else
		ret = 0.0;

	free(property);

	return ret;

}


/***
	getAttrDbl: Returns the value (double) of attribute attr from current xmlNode
	current: Current node from DOM tree
	attr: Attribute's name wich value will be returned
	Return: A value, represented by a double, of attribute attr or 0 value
*/
double getAttrDbl(xmlNode *current, const char *attr)
{
	char *property;
	double ret;

	property = getAttr(current, attr);

	if (property && strlen(property) > 0)
		ret = atof(property);
	else
		ret = 0.0;

	free(property);

	return ret;
}



/***

*/
void createListProbSwitch(xmlNode *node, tbranch_switch_node *switch_node)
{
	int qtcases, i;
	xmlNode *current;

	qtcases = countElement(node, "probability");
	if (qtcases > 0){
		switch_node->prob_cases = (trange_probability *) malloc(sizeof(trange_probability) * qtcases);
		switch_node->qtcases = qtcases;
		current = node->children;
		i=0;
		while(current)
		{
			if (!strcmp((char *)current->name, "probability")){
				switch_node->prob_cases[i].prob_start = getAttrDbl(current, "start");
				switch_node->prob_cases[i].prob_finish = getAttrDbl(current, "finish");
				start_range = getAttrDbl(current, "start-range");
				end_range = getAttrDbl(current, "end-range");
				step = getAttrDbl(current, "step");

				i++;
			}
			current = current->next;
		}
	}

}


/***

*/
void createListProbLoop(xmlNode *node, tloop_node *loop_node)
{
	char *type, *pdf, *idloop;

	type = getAttrStr(node, "type");
	idloop = getAttrStr(node, "idloop");
	strncpy(loop_node->idloop, idloop, 8);
	free(idloop);
	loop_node->type_loop = type[0];
	switch (type[0])
	{
		case '1': {
				loop_node->probability.prob_start = 1;
				loop_node->probability.prob_finish = getAttrDbl(node, "max-times");
				loop_node->probability.probability_density_function =  '1';
			} break;
		case '2': {
				loop_node->probability.prob_start = getAttrDbl(node, "start");
				loop_node->probability.prob_finish = getAttrDbl(node, "finish");
				start_range = getAttrDbl(node, "start-range");
				end_range = getAttrDbl(node, "end-range");
				step = getAttrDbl(node, "step");
				pdf = getAttrStr(node, "pdf");
				loop_node->probability.probability_density_function = pdf[0];
				free(pdf);
			} break;
	}
	free(type);
}

/***
	This function builds the list of clauses wich belong to IF node
*/
void buildClauses(xmlNode *node, tclauses_cond *clauses){

	int qtclauses, i;
	xmlNode *current, *probability;
	char *tmp;

	qtclauses = countElement(node, "condition");
	if (qtclauses > 0){
		clauses->lconditions = (tcondition *) malloc(sizeof(tcondition) * qtclauses);
		clauses->qtclauses = qtclauses;
		current = node->children;
		i=0;
		while(current) // scan tags condition
		{
			if (!strcmp((char *)current->name, "condition")){ // "probability"
				clauses->lconditions[i].timesexec = 0;
				tmp = getAttrStr(current, "id");
				strncpy(clauses->lconditions[i].info_cond.id, tmp, 5);
				free(tmp);
				clauses->lconditions[i].info_cond.clock_cycles = getAttrDbl(current, "clock-cycles");
				clauses->lconditions[i].info_cond.energy = getAttrDbl(current, "energy");
				clauses->lconditions[i].info_cond.consumed_cycles = 0.0;
				clauses->lconditions[i].info_cond.consumed_energy = 0.0;
				probability = current->children;
				while(probability) // scan tags probability
				{
					if (!strcmp((char *)probability->name, "probability")){
						start_range = getAttrDbl(probability, "start-range");
						end_range = getAttrDbl(probability, "end-range");
						step = getAttrDbl(probability, "step");
						clauses->lconditions[i].probability.prob_start = getAttrDbl(probability, "start");
						clauses->lconditions[i].probability.prob_finish = getAttrDbl(probability, "finish");
						clauses->lconditions[i].probability.probability_density_function = getAttrChr(probability, "pdf");
					}
					probability = probability->next;
				}
				i++;
			}
			current = current->next;
		}
	}
}

/***

*/
ttree_express *insTreeExpress(ttree_express *opl, ttree_express *opr, char elem)
{
	ttree_express *newe = (ttree_express *) malloc(sizeof(ttree_express));

	newe->idnode = elem;
	newe->next = NULL;
	newe->clause = NULL;

	newe->right = opr;
	newe->left = opl;

	opr->parent = newe;
	opl->parent = newe;

	return (newe);
}

/***
	This function finds a clause inside branch's list conditions
*/
tcondition *findClause(char idclause, tclauses_cond *clauses){

	unsigned int k=0;

	while(k<clauses->qtclauses && clauses->lconditions[k].info_cond.id[0] != idclause){
		k++;
	}

	if (k<clauses->qtclauses)
		return (clauses->lconditions)+k;
	else return NULL;
}


/***
	This procedure builds the binary tree wich represents the boolean express
*/
void buildTreeExpress(tclauses_cond *clauses){
	unsigned int i=0;

	ttree_express *newe = NULL, *oper1, *oper2, *top = NULL;

	while (clauses->bexpress[i])
	{

		if ((clauses->bexpress[i] == '*') || (clauses->bexpress[i] == '+')) // *: represents operator &&  +: represents operator ||
		{
			oper1 = top;
			top = top->next;
			oper2 = top;
			top = top->next;
			newe = insTreeExpress(oper2, oper1, clauses->bexpress[i]);
			clauses->root_express = newe;
			newe->next = top;
			top = newe;
		}
		else {
			newe = (ttree_express *) malloc(sizeof(ttree_express));
			newe->idnode = clauses->bexpress[i];
			newe->next = top;
			newe->left = NULL;
			newe->right = NULL;
			newe->clause = findClause(newe->idnode, clauses);
			top = newe;
		}
		i++;
	}

	if (clauses->root_express == NULL)
		clauses->root_express = newe;
}

/***
	createNode: This function creates a new node wich will be pointed by the current block of the graph
	current: Current node (block) of the graph
*/
void *createNode(xmlNode *current)
{
	char class, *tmp;
	xmlNode *axcurrent=NULL;

	class = getAttrChr(current, "class");
	switch(class)
	{
		case 48: // sequential block
			{
				tsequential_node *snode;
				snode = (tsequential_node *) malloc(sizeof(tsequential_node));
				snode->next_node = NULL;
				return ((void *) snode);
			} break;
		case 49: // branch block
			{
				tbranch_node *bnode;
				bnode = (tbranch_node *) malloc(sizeof(tbranch_node));
				bnode->clauses = (tclauses_cond *) malloc(sizeof(tclauses_cond));
				bnode->then_node = NULL;
				bnode->else_node = NULL;
				bnode->clauses->root_express = NULL;
				tmp = getAttrStr(current, "bool-express");
				strncpy(bnode->clauses->bexpress, tmp, 100);
				free(tmp);
				buildClauses(current, bnode->clauses);
				buildTreeExpress(bnode->clauses);
				printf("ROOT: %p\n", bnode->clauses->root_express);
				return ((void *) bnode);
			} break;
		case 50:  // loop block
			{
				tloop_node *lnode;
				lnode = (tloop_node *) malloc(sizeof(tloop_node));
				lnode->next_node = NULL;
				lnode->exit_node = NULL;
				lnode->clauses = NULL;
				lnode->nrloops   = 0;
				lnode->running = 0;

				if (getAttrStr(current, "bool-express") == NULL){
					current = getElement(current, "probability");
					createListProbLoop(current, lnode);
				} else {
					lnode->clauses = (tclauses_cond *) malloc(sizeof(tclauses_cond));
					axcurrent =  getElement(current, "condition");
					axcurrent =  getElement(axcurrent, "probability");
					strcpy(lnode->idloop, getAttrStr(axcurrent, "idloop"));
					lnode->type_loop = '3';
					tmp = getAttrStr(current, "bool-express");
					strncpy(lnode->clauses->bexpress, tmp, 100);
					free(tmp);
					buildClauses(current, lnode->clauses);
					buildTreeExpress(lnode->clauses);
					printf("WHILE ROOT: %p\n", lnode->clauses->root_express);
				}
				return ((void *) lnode);
			} break;
		case 51:  // switch block
			{
				tbranch_switch_node *lswitch;
				lswitch = (tbranch_switch_node *) malloc(sizeof(tbranch_switch_node));
				lswitch->first_case = NULL;
				lswitch->last_case  = NULL;
				lswitch->prob_cases = NULL;
				lswitch->qtcases = 0;
				createListProbSwitch(current, lswitch);
				return ((void *) lswitch);
			} break;
		case 52:  // case block
			{
				tcase_node *lcase;
				lcase = (tcase_node *) malloc(sizeof(tcase_node));
				return ((void *) lcase);
			}

	}

	return NULL;
}

/***
	addBlock: Adds the current node in the queue of blocks
	current: Current node from cfg's nodes list
*/
void addBlock(xmlNode *current)
{
	char *id;

	id = getAttrStr(current, "id");

	if (start_block == NULL)
	{
		//puts("inicio entao\n");
		start_block = (tblock *) malloc(sizeof(tblock));
		start_block->next_block = NULL;
		strncpy(start_block->info_node.id, id, 5);
		start_block->info_node.clock_cycles = getAttrInt(current, "clock-cycles");
		start_block->class_node = getAttrChr(current, "class");
		start_block->info_node.energy = getAttrDbl(current, "energy");
		start_block->info_node.consumed_cycles = 0;
		start_block->info_node.consumed_energy = 0;
		start_block->timesexec = 0;
		start_block->node = createNode(current);
		end_block = start_block;
		//puts("fim entao\n");
	}
	else
	{
		puts("inicio senao\n");
		puts(id);
		tblock *new_block;

		new_block = (tblock *) malloc(sizeof(tblock));
		new_block->next_block = NULL;
		end_block->next_block = new_block;
		end_block = new_block;
		strncpy(new_block->info_node.id, id, 5);
		new_block->info_node.clock_cycles = getAttrInt(current, "clock-cycles");
		new_block->info_node.energy = getAttrDbl(current, "energy");
		new_block->info_node.consumed_cycles = 0;
		new_block->info_node.consumed_energy = 0;
		new_block->timesexec = 0;
		new_block->class_node = getAttrChr(current, "class");
		new_block->node = createNode(current);
		puts("fim senao\n");
	}

	free(id);
}


/***
	loadNodes: Builds a queue of blocks based on tags "node" from cfg-xml file
	nodes: Node that contains the cfg's list nodes
*/
void loadNodes(xmlNode *nodes)
{
	xmlNode *current = NULL;
	puts("antes do while\n");
	current = nodes->children;
	while(current)
	{
		if (current->type == XML_ELEMENT_NODE)
			addBlock(current);
		current = current->next;
	}
	puts("depois do while\n");
}


void printtree(ttree_express *r)
{
	if (r)
	{
		printtree(r->left);
		/*if (r->parent){
			puts("tem pai\n");
			printf("Pai: %c\n", r->parent->idnode);
			puts("pai exibido\n");
		}
		else puts("Sem pai\n");*/
		printf("%c\n", r->idnode);
		printtree(r->right);
	}
}

static void freeTree(ttree_express *r)
{
	if (!r)
		return;

	freeTree(r->left);
	freeTree(r->right);
	free(r);
}

void freeNodes(tblock *start)
{
	tblock *blk = start, *tmp_blk;

	while (blk) {
		switch (blk->class_node) {
		case 49:
			{
				tbranch_node *node = blk->node;
				freeTree(node->clauses->root_express);
				free(node->clauses->lconditions);
				free(node->clauses);
				break;
			}
		case 51:
			{
				tbranch_switch_node *node = blk->node;
				free(node->prob_cases);
				tswitch_case *sw = node->first_case;
				while (sw) {
					tswitch_case *tmp = sw;
					sw = sw->next_case;
					free(tmp);
				}
				break;
			}
		case 50:
			{
				tloop_node *node = blk->node;
				if (node->clauses) {
					freeTree(node->clauses->root_express);
					free(node->clauses->lconditions);
					free(node->clauses);
				}
				break;
			}
		}
		tmp_blk = blk;
		blk = blk->next_block;
		free(tmp_blk->node);
		free(tmp_blk);
	}
}

void listNodes(tblock *start, double finish)
{
	FILE *pesti;
	tblock *node_start = start;
	char filename[20];

	snprintf(filename, sizeof(filename), "pesti_%f.csv", finish);
	pesti = fopen(filename, "w+");
	fprintf(pesti, "%s", "ID;CLASS;TIMES_EXEC;CYCLES;CYCLES_CONSUMED;ENERGY;ENERGY_CONSUMED\n");

	while(node_start)
	{
		puts("Inicio\n");
		fprintf(pesti, "%s;%d;%d;%d;%d;%11.3f;%11.3f\n", node_start->info_node.id, node_start->class_node, node_start->timesexec, node_start->info_node.clock_cycles, node_start->info_node.consumed_cycles, node_start->info_node.energy, node_start->info_node.consumed_energy);

		printf("ID: %s\n", node_start->info_node.id);
		printf("Cycles: %d\n", node_start->info_node.clock_cycles);
		printf("Consumed Cycles: %d\n", node_start->info_node.consumed_cycles);
		printf("Energy: %11.3f\n", node_start->info_node.energy);
		printf("Consumed Energy: %11.3f\n", node_start->info_node.consumed_energy);
		printf("Class node: %d\n", node_start->class_node);
		printf("Address node: %p\n", node_start->node);
		printf("Times Exec.: %d\n", node_start->timesexec);



		if (node_start->class_node == 49){
			tbranch_node *bnode = ((tbranch_node *) (node_start->node));
			int k;
			printf("Boolean Express: %s\n", bnode->clauses->bexpress);
			printf("CLAUSES: %d \n", bnode->clauses->qtclauses);
			for (k=0; k < bnode->clauses->qtclauses; k++){
				printf("	Id: %s\n", bnode->clauses->lconditions[k].info_cond.id);
				printf("	Cycles: %d\n", bnode->clauses->lconditions[k].info_cond.clock_cycles);
				printf("	Consumed Cycles: %d\n", bnode->clauses->lconditions[k].info_cond.consumed_cycles);
				printf("	Energy: %11.3f\n", bnode->clauses->lconditions[k].info_cond.energy);
				printf("	Consumed Energy: %11.3f\n", bnode->clauses->lconditions[k].info_cond.consumed_energy);
				printf("	Times Exec.: %d\n", bnode->clauses->lconditions[k].timesexec);
				printf("	Start: %g	Finish: %g\n", bnode->clauses->lconditions[k].probability.prob_start, bnode->clauses->lconditions[k].probability.prob_finish);
			}
			puts("listando expressoes\n");
			printtree(bnode->clauses->root_express);
			puts("expressoes listadas\n");
			puts("\n\n");
		}

		if (node_start->class_node == 51){
			tbranch_switch_node *axsw = (tbranch_switch_node *) (node_start->node); //()->prob_cases;
			printf("Qtde. Cases: %d\n", axsw->qtcases);
		}

		if (node_start->class_node == 50){
			tloop_node *loop = (tloop_node *) (node_start->node);
			if (loop->clauses == NULL){
				printf("Id Loop: %s\n", loop->idloop);
				printf("Loop type: %c\n", loop->type_loop);
				printf("NrLoops: %d\n", loop->nrloops);
				printf("Start: %g	Finish: %g\n", loop->probability.prob_start, loop->probability.prob_finish);
			} else {

			int m;
			printf("Boolean Express: %s\n", loop->clauses->bexpress);
			printf("CLAUSES: %d \n", loop->clauses->qtclauses);

			for (m=0; m < loop->clauses->qtclauses; m++){
				printf("	Id: %s\n", loop->clauses->lconditions[m].info_cond.id);
				printf("	Cycles: %d\n", loop->clauses->lconditions[m].info_cond.clock_cycles);
				printf("	Consumed Cycles: %d\n", loop->clauses->lconditions[m].info_cond.consumed_cycles);
				printf("	Energy: %11.3f\n", loop->clauses->lconditions[m].info_cond.energy);
				printf("	Consumed Energy: %11.3f\n", loop->clauses->lconditions[m].info_cond.consumed_energy);
				printf("	Times Exec.: %d\n", loop->clauses->lconditions[m].timesexec);
				printf("	Start: %g	Finish: %g\n", loop->clauses->lconditions[m].probability.prob_start, loop->clauses->lconditions[m].probability.prob_finish);
			}
			printtree(loop->clauses->root_express);
			puts("\n\n");
			}
		}

		puts("\n\n");
		node_start = node_start->next_block;
		puts("Fim\n");
	}

	fclose(pesti);
}

/***
	searchBlock: This function searches for a node, at the queue blocks, based on its ID
	start: Queue's start block
	id: Block's id
*/
tblock *searchBlock(tblock *start, const char *id)
{
	tblock *bstart = start;
	tblock *prev = NULL;
	char flag_stop = 1;

	while ((bstart) && (flag_stop) && (id))
	{
		flag_stop = strcmp(bstart->info_node.id, id);
		prev = bstart;
		bstart = bstart->next_block;
	}
	if (!flag_stop)
		return(prev);
	else return (NULL);
}



/***
	buildGraphFromEdges: This function builds the execution graph based on structs defined in control-flow-graph.h
	edges: Set of edges loaded from cfg xml file
*/
void buildGraphFromEdges(xmlNode *edges)
{
	xmlNode *current = NULL;
	tblock *from = NULL, *to = NULL;
	char *tmp;

	current = edges->children;
	while(current) {
		if (current->type == XML_ELEMENT_NODE) {
			tmp = getAttrStr(current, "from-idnode");
			from = searchBlock(start_block, tmp);
			free(tmp);
			tmp = getAttrStr(current, "to-idnode");
			to = searchBlock(start_block, tmp);
			free(tmp);
			printf("%s->%s\n",from->info_node.id, to->info_node.id);
			if (from && to) {
				switch(from->class_node) {
					case 48: // normal block
						((tsequential_node *) (from->node))->next_node = to; break;
					case 49: // branch block
						{
							if (!((tbranch_node *) (from->node))->then_node)
								((tbranch_node *) (from->node))->then_node = to;
							else ((tbranch_node *) (from->node))->else_node = to;
						} break;
					case 50: // loop block
						{
							if (!((tloop_node *) from->node)->next_node)
								((tloop_node *) from->node)->next_node = to;
							else ((tloop_node *) from->node)->exit_node = to;
						} break;
					case 51: // switch block
						{
							tswitch_case *new_case;
							new_case = (tswitch_case *) malloc(sizeof(tswitch_case));
							new_case->node_case = to;
							new_case->next_case = NULL;

							if (((tbranch_switch_node *) from->node)->first_case == NULL){

								((tbranch_switch_node *) from->node)->first_case = new_case;
								((tbranch_switch_node *) from->node)->last_case = new_case;
							}
							else{
								((tbranch_switch_node *) from->node)->last_case->next_case = new_case;
								((tbranch_switch_node *) from->node)->last_case = new_case;
							}

						} break;
					case 52: // case node
							((tcase_node *) from->node)->next_node = to; break;
				}
			}
		}
		current = current->next;
	}
}

/***
	loadCfg: This function loads cfg file to RAM memory using libxml API functions
	xmlfile: Cfg's file name
*/
void loadCfg(char *xmlfile)
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    LIBXML_TEST_VERSION

    doc = xmlParseFile(xmlfile);

    if (doc == NULL) {
        printf("error: could not parse file file.xml\n");
	exit(1);
    }

    root_element = xmlDocGetRootElement(doc);

	puts("carregando nodos\n");
    loadNodes(getElement(root_element, "nodes"));
	puts("construindo arestas\n");
    buildGraphFromEdges(getElement(root_element, "edges"));

    xmlFreeDoc(doc);
    xmlCleanupParser();
}

