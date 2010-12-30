#include <stdlib.h>


/**
	verificar se o rand gera os extremos (ex. 0 e 1)
	O número 0 está sendo gerado e, aparentemente, o número 1 não
**/
double randNumber(double i, double f){

	return i + (f - i) * rand() / ((double) RAND_MAX);
}

