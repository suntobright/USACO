/*
ID: suntobr1
LANG: C
TASK: camelot
*/

#include <stdio.h>

int n;
int r, c;
int king;
int kingdist[800];
int knights[800];
int count;
int path[800][800][2];
int sum[800];
int cost[800];

int rar(int x, int y)
{
  return x * c + y;
}

void unrar(int *x, int *y, int no)
{
  *x = no / c;
  *y = no % c;
}

int abs(int num)
{
  if (num < 0)
    num = -num;
  return num;
}

int max(int a, int b)
{
  return a > b ? a : b;
}

int min(int a, int b)
{
  return a < b ? a : b;
}

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  char temp[2];
  int x, y;
  int a, b;
  int cost;

  int i, j, k;

  in = fopen("camelot.in", "rb");
  out = fopen("camelot.out", "wb");

  fscanf(in, "%d%d", &r, &c);
  n = r * c;
  fscanf(in, "%s%d", temp, &x);
  y = temp[0] - 'A';
  x--;
  king = rar(x, y);
  while (fscanf(in, "%s%d", temp, &x) != EOF)
  {
    y = temp[0] - 'A';
    x--;
    knights[count++] = rar(x, y);
  }

  unrar(&a, &b, king);
  for (i = 0; i < n; i++)
  {
    unrar(&x, &y, i);
    kingdist[i] = max(abs(a - x), abs(b - y));
  }

  for (i = 0; i < n; i++)
  {
    path[i][i][0] = 0;
    path[i][i][1] = kingdist[i];

    for (j = i + 1; j < n; j++)
    {
      unrar(&x, &y, i);
      unrar(&a, &b, j);

      if ((abs(x - a) == 2 && abs(y - b) == 1) || (abs(x - a) == 1 && abs(y - b) == 2))
      {
        path[i][j][0] = path[j][i][0] = 1;
        path[i][j][1] = path[j][i][1] = min(kingdist[i], kingdist[j]) + 1;
      }
      else
      {
        path[i][j][0] = path[j][i][0] = 0xfffff;
        path[i][j][1] = path[j][i][1] = 0xfffff;
      }
    }
  }

  for (k = 0; k < n; k++)
    for (i = 0; i < n; i++)
      if (path[i][k][0] != 0xfffff)
        for (j = i + 1; j < n; j++)
          if (path[k][j][0] != 0xfffff)
          {
            if (path[i][j][0] > path[i][k][0] + path[k][j][0])
              path[i][j][0] = path[j][i][0] = path[i][k][0] + path[k][j][0];
            if (path[i][j][1] > path[i][k][0] + path[k][j][1])
              path[i][j][1] = path[j][i][1] = path[i][k][0] + path[k][j][1];
            if (path[i][j][1] > path[i][k][1] + path[k][j][0])
              path[i][j][1] = path[j][i][1] = path[i][k][1] + path[k][j][0];
          }

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      path[i][j][1] -= path[i][j][0];

  for (i = 0; i < n; i++)
    for (j = 0; j < count; j++)
      sum[i] += path[i][knights[j]][0];

  cost = 0xfffff;
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < count; j++)
      if (cost > sum[i] + path[i][knights[j]][1])
        cost = sum[i] + path[i][knights[j]][1];

    if (cost > sum[i] + kingdist[i])
      cost = sum[i] + kingdist[i];
  }

  fprintf(out, "%d\n", cost);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
