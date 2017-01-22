/*
ID: suntobr1
LANG: C
TASK: inflate
*/

#include <stdio.h>

int max(int a, int b)
{
  return a > b ? a : b;
}

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int m, n;
  int dp[10240] = { 0 };
  int point[10240];
  int time[10240];

  int i, j;

  in = fopen("inflate.in", "rb");
  out = fopen("inflate.out", "wb");

  fscanf(in, "%d%d", &m, &n);
  for (i = 0; i < n; i++)
    fscanf(in, "%d%d", &point[i], &time[i]);

  for (i = 0; i < n; i++)
    for (j = time[i]; j <= m; j++)
      dp[j] = max(dp[j], dp[j - time[i]] + point[i]);

  fprintf(out, "%d\n", dp[m]);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
