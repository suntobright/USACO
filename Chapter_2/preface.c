/*
ID: suntobr1
LANG: C
TASK: preface
*/

#include <stdio.h>

int main()
{
  FILE *fin, *fout;

  int query[10][3] = {
    {0, 0, 0},
    {1, 0, 0},
    {2, 0, 0},
    {3, 0, 0},
    {1, 1, 0},
    {0, 1, 0},
    {1, 1, 0},
    {2, 1, 0},
    {3, 1, 0},
    {1, 0, 1}
  };
  char letters[] = "IVXLCDM";
  int counts[7] = {0};
  int i, temp, n, pos, j, cur;

  fin = fopen("preface.in", "r");
  fout = fopen("preface.out", "w");

  fscanf(fin, "%d", &n);
  for(i = 1; i <= n; i ++)
  {
    temp = i;
    cur = 0;
    while(temp != 0)
    {
      pos = temp % 10;
      for(j = 0; j < 3; j ++)
      {
        if (cur + j < 7) {
          counts[cur + j] += query[pos][j];
        }
      }
      temp /= 10;
      cur += 2;
    }
  }

  for(i = 0; i < 7; i ++)
  {
    if(counts[i] != 0)
      fprintf(fout, "%c %d\n", letters[i], counts[i]);
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
