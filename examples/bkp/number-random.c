#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double randomnumber(double i, double f){

	return i + (f - i) * rand() / ((double) RAND_MAX);
}


int main(int argc, char *argv[]){
	
	int pass;

	srand(time(0));
	for (pass = 0; pass < atoi(argv[1]); pass++)
		printf("%d: %d\n", pass, (int) (randomnumber(atoi(argv[2]), atoi(argv[3]))));

	return 0;
}
