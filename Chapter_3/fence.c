/*
ID: suntobr1
LANG: C
TASK: fence
*/

#include <stdio.h>

int n;
int map[512][512];
int have[512];
int path[512];
int count;

void findpath(int from)
{
  int i = 0;

  for (i = 0; i < 512; i ++)
    if (map[from][i] != 0)
    {
      map[from][i] --;
      map[i][from] --;
      findpath(i);
    }

  path[count++] = from;
}

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int x, y;
  int sum;
  int i, j;

  in = fopen("fence.in", "rb");
  out = fopen("fence.out", "wb");

  fscanf(in, "%d", &n);
  for (i = 0; i < n; i++)
  {
    fscanf(in, "%d%d", &x, &y);
    map[x][y] ++;
    map[y][x] ++;
    have[x] = 1;
    have[y] = 1;
  }

  for (i = 0; i < 512; i++)
    if (have[i] == 1)
    {
      sum = 0;
      for (j = 0; j < 512; j++)
        sum += map[i][j];

      if (sum % 2 != 0)
        break;
    }

  if (i == 512)
    for (i = 0; have[i] == 0; i++);

  findpath(i);

  for (i = count - 1; i >= 0; i--)
    fprintf(out, "%d\n", path[i]);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
