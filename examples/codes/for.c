#include <stdio.h>

int main()
{
	int a, b;

	/* LP01 @LoopProb(10:40, 3)  */
	for (a=0; a < b; a++)
	{
		puts("teste\n");
		b--;
	}
	
	a = a + b;
	b = b * 9;

	return 0;
}
