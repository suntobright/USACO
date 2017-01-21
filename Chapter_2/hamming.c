/*
ID: suntobr1
LANG: C
TASK: hamming
*/

#include <stdio.h>

int dis(int a, int b, int bits)
{
  int i, sum;
  for(i = 0, sum = 0; i < bits; i ++)
  {
    sum += (a & 1) ^ (b & 1);
    a = a >> 1;
    b = b >> 1;
  }
  return sum;
}

int main()
{
  FILE *fin, *fout;
  int n, b, d;
  int query[256] = {0};
  int flag, count;
  int i, j;

  fin = fopen("hamming.in", "r");
  fout = fopen("hamming.out", "w");

  fscanf(fin, "%d %d %d", &n, &b, &d);

  for(i = 0; i < (1 << b); i ++)
  {
    if(query[i] == 0)
    {
      for(j = i + 1; j < (1 << b); j ++)
      {
        if(dis(i, j, b) < d)
        {
          query[j] = 1;
        }
      }
    }
  }

  for(i = 0, flag = 0, count = 0; i < (1 << b) && count < n; i ++)
  {
    if(query[i] == 0)
    {
      if(flag == 0)
      {
        fprintf(fout, "%d", i);
        flag ++;
        count ++;
      }
      else
      {
        fprintf(fout, " %d", i);
        flag ++;
        count ++;
        if(flag == 10)
        {
          fprintf(fout, "\n");
          flag = 0;
        }
      }
    }
  }
  if(flag != 0)
  {
    fprintf(fout, "\n");
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
