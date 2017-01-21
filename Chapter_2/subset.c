/*
ID: suntobr1
LANG: C
TASK: subset
*/

#include <stdio.h>

int main()
{
  FILE *fin, *fout;
  int n, sum, i, j;
  int count[40][800] = {0};

  fin = fopen("subset.in", "r");
  fout = fopen("subset.out", "w");

  fscanf(fin, "%d", &n);

  for(i = 1; i <= n; i ++)
  {
    sum = (1 + i) * i / 2;
    for(j = 0; j < sum; j ++)
    {
      count[i][j] = (j > i) ? count[i - 1][j - i] : 0;
      count[i][j] += count[i - 1][j];
    }
    count[i][j] = 1;
  }

  if(sum % 2 == 1)
    fprintf(fout, "0\n");
  else
    fprintf(fout, "%d\n", count[n][sum / 2]);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
