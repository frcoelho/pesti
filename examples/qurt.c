#include "common.h"

int main()
{
  double a[3], x1[2], x2[2];
  int result, r;

  a[0] = 1.75;
  a[1] = -3.2;
  a[2] = 2.45;
  r = qurt(a, x1, x2);
  result = *(int *) &x1[0];

  return 0;
}

double fabs(double x) 
{
	double y;
  /* @BranchProb(0.0, 1)*/
  if (x < 0)
  {
	y = -x;
  }
  else
  {
	y = x;
  }
  return  (y);
}

double sqrt(double val) 
{
  double x = val/10;
  double dx;
  double delta;
  double min_tol = 0.00001;
  double fdelta;
  int i, flag;

  flag = 0;
  /* @BranchProb(0.0, 1) */
  if ( val == 0 ) 
  {
    x = 0;
  }  
  else
 {
    /* LP01 @LoopMax(20, 1) */
    for (i=1; i<20; i++) 
     {
	/* @BranchProb(0.35, 1) */
      if ( flag != 0) 
      {
	dx = (val - (x*x)) / (2.0 * x);
	x = x + dx;
	delta = val - (x*x);
	fdelta = fabs(delta);
	/* @BranchProb(0.05, 1) */ 
	if ( fdelta <= min_tol ) 
	{
		flag = 1;
	}
      }
      else 
	{
	  x =x;
	}
    }
 }
  return x;
}

int qurt(double a[], double x1[], double x2[])
{
  double d, w1, w2, res;
  int ret=0;

  /* @BranchProb(0.0, 1) */
  if (a[0] == 0.0)
  {
    ret = (999);
  }
  d = a[1] * a[1] - 4 * a[0] * a[2];
  w1 = 2.0 * a[0];
  res = fabs(d);
  w2 = sqrt(res);
  /* @BranchProb(1.0, 1) */
  if (d > 0.0)
    {
      x1[0] = (-a[1] + w2) / w1;
      x1[1] = 0.0;
      x2[0] = (-a[1] - w2) / w1;
      x2[1] = 0.0;

    } 
  else 
  {
      /* @BranchProb(0.0, 1) */
      if (d == 0.0)
    {
      x1[0] = -a[1] / w1;
      x1[1] = 0.0;
      x2[0] = x1[0];
      x2[1] = 0.0;
    } 
  else
    {
      w2 /= w1;
      x1[0] = -a[1] / w1;
      x1[1] = w2;
      x2[0] = x1[0];
      x2[1] = -w2;
    }
  }
      return (ret);
}
