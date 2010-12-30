  a[0] = 1.5;
  a[1] = -2.5;
  a[2] = 1.5;
  r = qurt(a, x1, x2);
  result += *(int *) &x1[1];
  a[0] = 1.8;
  a[1] = -4.275;
  a[2] = 8.31;
  r = qurt(a, x1, x2);
  result -= *(int *) &x1[1];

