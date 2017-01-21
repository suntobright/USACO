/*
ID: suntobr1
LANG: C
TASK: holstein
*/

#include <stdio.h>

int cmp(int a, int b, int bits)
{
  int i;
  for(i = 0; i < bits; i ++)
  {
    if((a & 1) == (b & 1))
    {
      a = a >> 1;
      b = b >> 1;
    }
    else
      break;
  }
  return (a & 1) - (b & 1);
}

int main()
{
  FILE *fin, *fout;
  int request[25] = {0};
  int scoop[15][25] = {0};
  int sum[25] = {0};
  int type, kind, pick, poss, count;
  int recount, repick;
  int i, j, k;

  fin = fopen("holstein.in", "r");
  fout = fopen("holstein.out", "w");

  fscanf(fin, "%d", &type);
  for(i = 0; i < type; i ++)
  {
    fscanf(fin, "%d", &request[i]);
  }
  fscanf(fin, "%d", &kind);
  for(i = 0; i < kind; i ++)
  {
    for(j = 0; j < type; j ++)
    {
      fscanf(fin, "%d", &scoop[i][j]);
    }
  }

  for(i = 1, poss = 1 << kind, recount = kind + 1; i < poss; i ++)
  {
    for(j = 0; j < type; j ++)
    {
      sum[j] = 0;
    }
    for(j = 0, pick = i, count = 0; j < kind; j ++, pick = pick >> 1)
    {
      if((pick & 1) == 1)
      {
        for(k = 0; k < type; k ++)
        {
          sum[k] += scoop[j][k];
        }
        count ++;
      }
    }
    for(j = 0; j < type && sum[j] >= request[j]; j ++);
    if((j == type) && (count < recount || (count == recount && cmp(i, repick, kind) > 0)))
    {
      recount = count;
      repick = i;
    }
  }

  fprintf(fout, "%d", recount);
  for(i = 0; i < kind; i ++, repick = repick >> 1)
  {
    if((repick & 1) == 1)
    {
      fprintf(fout, " %d", i + 1);
    }
  }
  fprintf(fout, "\n");

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
