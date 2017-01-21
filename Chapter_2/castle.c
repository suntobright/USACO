/*
ID: suntobr1
LANG: C
TASK: castle
*/

#include <stdio.h>

int layout[50][50];
int map[50][50];
int size[2500];

void assign(int i, int j, int count)
{
  map[i][j] = count;
  if((layout[i][j] & (1 << 0)) == 0 && map[i][j - 1] == 0)
    assign(i, j - 1, count);
  if((layout[i][j] & (1 << 1)) == 0 && map[i - 1][j] == 0)
    assign(i - 1, j, count);
  if((layout[i][j] & (1 << 2)) == 0 && map[i][j + 1] == 0)
    assign(i, j + 1, count);
  if((layout[i][j] & (1 << 3)) == 0 && map[i + 1][j] == 0)
    assign(i + 1, j, count);
}

int main()
{
  FILE *fin, *fout;
  int m, n;
  int count, max, temp;
  char direc;
  int i, j, ii, jj;

  fin = fopen("castle.in", "r");
  fout = fopen("castle.out", "w");

  fscanf(fin, "%d %d", &m, &n);

  for(i = 0; i < n; i ++)
  {
    for(j = 0; j < m; j ++)
    {
      fscanf(fin, "%d", &layout[i][j]);
    }
  }

  count = 0;
  for(i = 0; i < n; i ++)
  {
    for(j = 0; j < m; j ++)
    {
      if(map[i][j] == 0)
        assign(i, j, ++count);
      size[map[i][j] - 1] ++;
    }
  }

  max = 0;
  for(j = 0; j < m; j ++)
  {
    for(i = n - 1; i >= 0; i --)
    {
      if(i > 0 && map[i][j] != map[i - 1][j])
      {
        temp = size[map[i][j] - 1] + size[map[i - 1][j] - 1];
        if(max < temp)
        {
          max = temp;
          ii = i + 1;
          jj = j + 1;
          direc = 'N';
        }
      }
      if(j < m - 1 && map[i][j] != map[i][j + 1])
      {
        temp = size[map[i][j] - 1] + size[map[i][j + 1] - 1];
        if(max < temp)
        {
          max = temp;
          ii = i + 1;
          jj = j + 1;
          direc = 'E';
        }
      }
    }
  }

  temp = 0;
  for(i = 0; i < count; i ++)
  {
    if(temp < size[i])
      temp = size[i];
  }

  fprintf(fout, "%d\n", count);
  fprintf(fout, "%d\n", temp);
  fprintf(fout, "%d\n", max);
  fprintf(fout, "%d %d %c\n", ii, jj, direc);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
