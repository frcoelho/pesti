#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
	char node;
	int value;
	int custo;
	struct tree *right;
	struct tree *left;
	struct tree *next;
	struct tree *parent;
} ttree;

ttree *root = NULL;
ttree *newe, *oper1, *oper2, *top = NULL;

int main()
{
	unsigned char i=0;
	char express[] = "AB*CD*+";
	int cost=0;

	while (express[i])
	{
		if ((express[i] == '*') || (express[i] == '+'))
		{
			oper1 = top;
			top = top->next;
			oper2 = top;
			top = top->next;
			newe = insert_tree(oper2, oper1, express[i]);
			newe->value = 0;
			newe->custo = (i+1)*5;
			newe->next = top;
			top = newe;
		}
		else {
			newe = (ttree *) malloc(sizeof(ttree));
			newe->node = express[i];
			newe->value = (i==0) || (i==3);
			newe->custo = (i+1)*5;
			newe->next = top;
			top = newe;
		}
		i++;
	}
	avalia(root, &cost);
	printtree(root);
	puts("\n\n");
	puts(express);
	puts("\n\n");

	printf("custo total: %d\n", cost);

	return 0;
}


void insert_tree(ttree *ope, ttree *opd, char elem)
{
	ttree *newe = (ttree *) malloc(sizeof(ttree));
	newe->node = elem;
	newe->next = NULL;

	newe->right = opd;
	newe->left = ope;

	opd->parent = newe;
	ope->parent = newe;

	root = newe;
	
	return (newe);
}

int avalia(ttree *r, int *c){
	int a, flag=0;

	if (r){
		a = avalia(r->left, c);
		switch(r->node){
			case '*':{
					if (a==0)
						flag = 1;
			} break;
			case '+':{
					if (a==1)
						flag=1;
			} break;
			default: a = r->value; *c = *c + r->custo; flag=1;
		}	
		if (flag)
			return(a);
		else {
			a = avalia(r->right, c);	
			return(a);
		}
	}
	else return(3);
}

void printtree(ttree *r)
{
	if (r)
	{
		printtree(r->left);
		printf("%c	%d	%d\n", r->node, r->value, r->custo);
		printtree(r->right);	
	}
}
