#include <stdio.h>
#include "header.h"


int main()
 {
	unsigned short a;
	a = 5;
	a = fat(a, 8);
	printf("%d\n", a);
	return 0;
}

unsigned short fat(unsigned short x, int z)
{
	unsigned short f=1;
	/* LP01 @LoopProb(0.83, 1)  */	
	while (x > 0) 
	{
		f = f * x;
		x--;
	}
	return f;
}



