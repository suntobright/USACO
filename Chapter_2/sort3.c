/*
ID: suntobr1
LANG: C
TASK: sort3
*/

#include <stdio.h>

int main()
{
  FILE *fin, *fout;
  int n, i, j, temp, sum;
  int array[1000];
  int count[3] = {0};
  int matrx[3][3] = {0};

  fin = fopen("sort3.in", "r");
  fout = fopen("sort3.out", "w");

  fscanf(fin, "%d", &n);
  for(i = 0; i < n; i ++)
  {
    fscanf(fin, "%d", &array[i]);
  }

  for(i = 0; i < n; i ++)
  {
    count[array[i] - 1] ++;
  }
  count[1] += count[0];
  count[2] += count[1];

  for(i = 0, j = 0; i < 3; i ++)
  {
    while(j < count[i])
    {
      matrx[i][array[j ++] - 1] ++;
    }
  }

  sum = 0;
  temp = matrx[0][1] < matrx[1][0] ? matrx[0][1] : matrx[1][0];
  sum += temp;
  temp = matrx[0][2] < matrx[2][0] ? matrx[0][2] : matrx[2][0];
  sum += temp;
  temp = matrx[1][2] < matrx[2][1] ? matrx[1][2] : matrx[2][1];
  sum += temp;
  matrx[1][2] -= temp;
  matrx[2][1] -= temp;

  sum += matrx[1][2] * 2 + matrx[2][1] * 2;

  fprintf(fout, "%d\n", sum);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
