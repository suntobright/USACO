/*
ID: suntobr1
LANG: C
TASK: concom
*/

#include <stdio.h>

int main()
{
  FILE *fin, *fout;

  int array[101][101] = {0};
  int map[101][101] = {0};
  int n, i, j, p, temp, flag;

  fin = fopen("concom.in", "r");
  fout = fopen("concom.out", "w");

  fscanf(fin, "%d", &n);
  for(temp = 0; temp < n; temp ++)
  {
    fscanf(fin, "%d %d %d", &i, &j, &p);
    array[i][j] = p;
    map[i][j] = p > 50 ? 1 : 0;
  }

  flag = 1;
  while(flag == 1)
  {
    flag = 0;
    for(i = 1; i <= 100; i ++)
    {
      for(j = 1; j <= 100; j ++)
      {
        if(i == j || map[i][j] == 1)
          continue;
        for(temp = 0, p = 1; p <= 100; p ++)
        {
          if(i == p || j == p)
            continue;
          if(map[i][p] == 1)
          {
            temp += array[p][j];
          }
        }
        temp += array[i][j];
        if(temp > 50)
        {
          flag = 1;
          map[i][j] = 1;
        }
      }
    }
  }

  for(i = 1; i <= 100; i ++)
  {
    for(j = 1; j <= 100; j ++)
    {
      if(map[i][j] == 1 && i != j)
      {
        fprintf(fout, "%d %d\n", i, j);
      }
    }
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
