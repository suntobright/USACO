/*
ID: suntobr1
LANG: C
TASK: sprime
*/

#include <stdio.h>
#include <math.h>

int num[1000];
int count;

void search(int prime, int len, int n)
{
  int i, max;
  for(i = 2, max = (int)sqrt(prime); i <= max && prime % i != 0; i ++);
  if(i > max)
  {
    if(len == n)
      num[count ++] = prime;
    else
      for(i = 1; i < 10; i += 2)
        search(prime * 10 + i, len + 1, n);
  }
}

int main()
{
  FILE *fin, *fout;
  int n, i;

  fin = fopen("sprime.in", "r");
  fout = fopen("sprime.out", "w");

  fscanf(fin, "%d", &n);

  for(i = 2; i < 10; i ++)
    search(i, 1, n);

  for(i = 0; i < count; i ++)
    fprintf(fout, "%d\n", num[i]);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
