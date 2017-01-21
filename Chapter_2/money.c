/*
ID: suntobr1
LANG: C
TASK: money
*/

#include <stdio.h>

int main()
{
  FILE *fin, *fout;

  long long array[25][10001] = {0};
  int value[25] = {0};
  int v, n, i, j, temp;

  fin = fopen("money.in", "r");
  fout = fopen("money.out", "w");

  fscanf(fin, "%d %d", &v, &n);
  for(i = 0; i < v; i ++)
  {
    fscanf(fin, "%d", &value[i]);
  }

  for(i = 0; i <= n; i += value[0])
  {
    array[0][i] = 1;
  }

  for(i = 1; i < v; i ++)
  {
    for(j = 0; j <= n; j ++)
    {
      for(temp = 0; temp <= j; temp += value[i])
      {
        array[i][j] += array[i - 1][j - temp];
      }
    }
  }

  fprintf(fout, "%lld\n", array[v - 1][n]);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
