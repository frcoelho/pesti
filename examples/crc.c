#include <stdio.h>
#include "crc.h"

int main(int argc, char *argv[])
{
  unsigned char aa[] = "asdffeagewaHAFEFaeDsFEawFdsFaefaeerdjgpim23";
  unsigned short i1, i2;

  i1 = icrc(0, aa, 40, (short) 0, 1);
  /* @BranchProb(1.0, 1) */
  if (i2==387)
  {
	i1=0;
  }
  return 0;
}

unsigned short icrc1(unsigned short crc, unsigned char onech)
{
  int i, flag;
  unsigned short ans = (crc ^ onech << 8);
  /* LP01 @LoopMax(8, 1) */
  for (i = 0; i < 8; i++)
  {
	  flag = ans & 0x8000;
	  /* @BranchProb(0.50, 1) */
	  if (flag != 0)
	  {
		ans = (ans <<= 1) ^ 4129;
	  }
          else
      	  {
		ans <<= 1;
      	  }
  }
  return ans;
}

unsigned short icrc(unsigned short crc, unsigned char *lin, unsigned int len, short jinit, int jrev)
{
  static unsigned short icrctb[256], init = 0;
  static unsigned char rchr[256];
  unsigned short tmp1, tmp2, j, cword = crc;
  static unsigned char it[16] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};

  /* @BranchProb(0.4896, 1) */
  if (init!=0)
  {
      init = 1;
      /* LP02 @LoopMax(256, 1) */
      for (j=0; j <= 255; j++)
      {
    	  icrctb[j] = icrc1(j << 8, (unsigned char) 0);
    	  rchr[j] = (unsigned char) (it[j & 0xF] << 4 | it[j >> 4]);
      }
  }
  /* @BranchProb(0.5186, 1) */
  if (jinit >= 0)
  {
    cword = ((unsigned char) jinit) | (((unsigned char) jinit) << 8);
  }
  else 
  {
	  /* @BranchProb(0.2364, 1) */
	  if (jrev < 0)
	  {
	  		cword = rchr[((unsigned char) ((cword) >> 8))] | rchr[((unsigned char) ((cword) & 0xFF))] << 8;
	  }
  }   
  /* LP03 @LoopMax(40, 1) */
  for (j = 1; j <= len; j++)
  {
      /* @BranchProb(0.4804, 1) */
      if (jrev < 0)
      {
    	  tmp1 = rchr[lin[j]] ^ ((unsigned char) ((cword) >> 8));
      } 
      else
      {
    	  tmp1 = lin[j] ^ ((unsigned char) ((cword) >> 8));
      }
      cword = icrctb[tmp1] ^ ((unsigned char) ((cword) & 0xFF)) << 8;
  }
  /* @BranchProb(0.5218, 1) */
  if (jrev >= 0)
  {
      tmp2 = cword;
  } 
  else
  {
      tmp2 = rchr[((unsigned char) ((cword) >> 8))] | rchr[((unsigned char) ((cword) & 0xFF))] << 8;
  }
  
  return (tmp2);
}

