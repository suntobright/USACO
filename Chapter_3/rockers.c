/*
ID: suntobr1
LANG: C
TASK: rockers
*/

#include <stdio.h>

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int n, t, m;
  int len[24];
  int max[24][24] = {0};

  int i, j, k;

  in = fopen("rockers.in", "rb");
  out = fopen("rockers.out", "wb");

  fscanf(in, "%d%d%d", &n, &t, &m);
  for (i = 0; i < n; i ++)
    fscanf(in, "%d", &len[i]);

  for (i = 0; i < n; i ++)
  {
    for (j = m - 1; j >= 0; j --)
      for (k = t; k >= len[i]; k --)
        if (max[j][k] < max[j][k - len[i]] + 1)
          max[j][k] = max[j][k - len[i]] + 1;

    for (j = 1; j < m; j ++)
      for (k = 0; k < len[i]; k ++)
        if (max[j][k] < max[j - 1][t])
          max[j][k] = max[j - 1][t];
  }

  fprintf(out, "%d\n", max[m - 1][t]);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
