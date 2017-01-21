/*
ID: suntobr1
LANG: C
TASK: numtri
*/

#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
  return a > b ? a : b;
}

int main()
{
  FILE *fin, *fout;
  int array[1000][1001] = {0};
  int sum[1000][1001] = {0};
  int i, j, n, temp;

  fin = fopen("numtri.in", "r");
  fout = fopen("numtri.out", "w");

  fscanf(fin, "%d", &n);
  for(i = 0; i < n; i ++)
  {
    for(j = 1; j <= i + 1; j ++)
    {
      fscanf(fin, "%d", &array[i][j]);
    }
  }

  for(i = 1, sum[0][1] = array[0][1]; i < n; i ++)
  {
    for(j = 1; j <= i + 1; j ++)
    {
      sum[i][j] = max(sum[i - 1][j - 1] + array[i][j], sum[i - 1][j] + array[i][j]);
    }
  }

  for(i = 1, temp = 0; i <= n; i ++)
  {
    if(temp < sum[n - 1][i])
      temp = sum[n - 1][i];
  }


  fprintf(fout, "%d\n", temp);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
