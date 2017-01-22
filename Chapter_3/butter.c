/*
ID: suntobr1
LANG: C
TASK: butter
*/

#include <stdio.h>

int path[800][800];
int cow[800] = { 0 };

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int n, p, c;

  int i, j, k;
  int x, y, z;
  int min;
  int temp;

  in = fopen("butter.in", "rb");
  out = fopen("butter.out", "wb");

  fscanf(in, "%d%d%d", &n, &p, &c);
  for (i = 0; i < n; i++)
  {
    fscanf(in, "%d", &x);
    x--;
    cow[x] ++;
  }
  for (i = 0; i < p; i++)
  {
    path[i][i] = 0;
    for (j = i + 1; j < p; j++)
      path[i][j] = path[j][i] = 0x3fffffff;
  }
  for (i = 0; i < c; i++)
  {
    fscanf(in, "%d%d%d", &x, &y, &z);
    x--;
    y--;
    path[x][y] = path[y][x] = z;
  }

  for (k = 0; k < p; k++)
    for (i = 0; i < p; i++)
      for (j = i + 1; j < p; j++)
        if (path[i][j] > path[i][k] + path[k][j])
          path[i][j] = path[j][i] = path[i][k] + path[k][j];

  min = 0x3fffffff;
  for (i = 0; i < p; i++)
  {
    temp = 0;
    for (j = 0; j < p; j++)
      temp += cow[j] * path[i][j];

    if (min > temp)
      min = temp;
  }

  fprintf(out, "%d\n", min);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
