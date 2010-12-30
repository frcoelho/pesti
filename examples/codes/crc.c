#include <stdio.h>

int main(int argc, char *argv[])
{
	unsigned char aa[]= "asdffeagewaHAFEFaeDsFEawFdsFaefaeerdjgpim23" ;
	unsigned short i1, i2;
	int n;
	static unsigned short icrctb[256], init;
	static unsigned char rchr[256];
	unsigned short tmp1, tmp2, j, cword;
	static unsigned char it[16] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
	int i, flag;
	unsigned short ans;
	unsigned short crc;
	unsigned char *lin;
	unsigned int len;
	short jinit;
	int jrev;
	init=0;
	crc=0;
	cword=crc;
	lin=aa;
	len=40;
	jinit=0;
	jrev=1;
	/* @BranchProb(0.5, 1) */
	if (!init)
	{
	      init = 1;
	      /* LP01 @LoopMax(255, 1) */
	      for (j = 0; j <= 255; j++)
	      {
	    	  ans = (j << 8 ^ 0 << 8);
		      /* LP02 @LoopMax(8, 1) */
			  for (i = 0; i < 8; i++)
			  {
				  flag = ans & 0x8000;
				  /* @BranchProb(0.5, 1) */
			      if (flag)
			      {
			    	  ans = (ans <<= 1) ^ 4129;
			      }
			      else
			      {
			    	  ans <<= 1;
			      }
			  }
			  icrctb[j] = ans; 
			  rchr[j] = (it[j & 0xF] << 4 | it[j >> 4]);
	      }
	}
	  /* @BranchProb(0.5, 1) */
	  if (jinit >= 0)
	  {
	    cword = ((unsigned char ) jinit) | (((unsigned char ) jinit) << 8);
	  }
	  else 
		  {
		  /* @BranchProb(0.5, 1) */
		  	if (jrev < 0)
		  	{
		  		cword = rchr[((unsigned char ) ((cword) >> 8))] | rchr[((unsigned char ) ((cword) & 0xFF))] << 8;
		  	}
		  }
    /* LP03 @LoopMax(40, 1) */
	  for (j = 1; j <= len; j++)
	  {
		  /* @BranchProb(0.5, 1) */
	      if (jrev < 0)
	      {
	    	  tmp1 = rchr[lin[j]] ^ ((unsigned char ) ((cword) >> 8));
	      } 
	      else
	      {
	    	  tmp1 = lin[j] ^ ((unsigned char ) ((cword) >> 8));
	      }
	      cword = icrctb[tmp1] ^ ((unsigned char ) ((cword) & 0xFF)) << 8;
	  }
	  /* @BranchProb(0.5, 1) */
	  if (jrev >= 0)
	  {
	      tmp2 = cword;
	  } 
	  else
	  {
	      tmp2 = rchr[((unsigned char ) ((cword) >> 8))] | rchr[((unsigned char ) ((cword) & 0xFF))] << 8;
	  }
	  i1=tmp2;	
	  return 0;	  
}
