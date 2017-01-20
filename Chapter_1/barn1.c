/*
ID: suntobr1
LANG: C
TASK: barn1
*/

#include <stdio.h>

int main()
{
  FILE *fin, *fout;

  int stall[200] = {0};
  int m, s, c;
  int i, j, k, max, temp;

  fin = fopen("barn1.in", "r");
  fout = fopen("barn1.out", "w");

  fscanf(fin, "%d %d %d", &m, &s, &c);
  for(i = 0; i < c; i ++)
  {
    fscanf(fin, "%d", &temp);
    stall[temp - 1] = 1;
  }

  for(i = 0; stall[i] == 0; i ++)
    stall[i] = 1;
  for(i = s - 1; stall[i] == 0; i --)
    stall[i] = 1;

  for(i = 1; i < m; i ++)
  {
    max = 0;
    for(j = 0; j < s;)
    {
      if(stall[j] == 0)
      {
        for(k = j + 1; stall[k] == 0; k ++);
        if(max < k - j)
        {
          max = k - j;
          temp = j;
        }
        j = k + 1;
      }
      else
        j ++;
    }
    while(stall[temp] == 0)
      stall[temp ++] = 1;
  }

  for(i = 0, temp = c; i < s; i ++)
    if(stall[i] == 0)
      temp ++;

  fprintf(fout, "%d\n", temp);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
