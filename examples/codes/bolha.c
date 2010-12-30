
int main()
{
	int i, j, temp, numbers[] = {348,211,819,875,125,784,102,788,178,958} ;

	while(1){
	/* LP01 @LoopMax(9, 1)  */
	for (i=9; i >= 0; i--)  	
	{
	    /* LP02 @LoopMax(5, 1)  */
	    for (j=1; j <= i; j++)
	    {
	      /* @BranchProb(0.4946, 1)  */
	      if ( numbers[i] > numbers[j] )
	      {
	        temp = numbers[j-1];
	        numbers[j-1] = numbers[j];
	        numbers[j] = temp;
	      }
	    }
	}
	}
	return 0;
}


