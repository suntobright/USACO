/*
ID: suntobr1
LANG: C
TASK: nocows
*/

#include <stdio.h>

int main()
{
  FILE *fin, *fout;

  long long array[100][200] = {0};
  int query[8] = {0, 1, 3, 7, 15, 31, 63, 127};
  int n, k, level, i, j, end1, end2;

  fin = fopen("nocows.in", "r");
  fout = fopen("nocows.out", "w");

  fscanf(fin, "%d %d", &n, &k);

  array[1][1] = 1;

  for(level = 2; level <= k; level ++)
  {
    end1 = level > 7 ? 199 : query[level];
    for(i = 2 * level - 1; i <= end1; i += 2)
    {
      end2 = level > 8 ? 199 : query[level - 1];
      for(j = 2 * level - 3; j <= end2 && j <= i - 2; j += 2)
      {
        array[level][i] += array[level - 1][j] * array[0][i - j - 1] * 2;
        array[level][i] += array[level - 1][j] * array[level - 1][i - j - 1];
        array[level][i] %= 9901;
      }
    }
    for(j = 2 * level - 3; j <= end2; j += 2)
    {
      array[0][j] += array[level - 1][j];
      array[0][j] %= 9901;
    }
  }

  fprintf(fout, "%lld\n", array[k][n]);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
