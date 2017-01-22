/*
ID: suntobr1
LANG: C
TASK: game1
*/

#include <stdio.h>

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int n;
  int num[128] = { 0 };
  int max[128][2] = { 0 };

  int i, j;
  int temp;

  in = fopen("game1.in", "rb");
  out = fopen("game1.out", "wb");

  fscanf(in, "%d", &n);
  for (i = 0; i < n; i++)
    fscanf(in, "%d", &num[i]);

  for (i = 0; i < n; i++)
    max[i][0] = num[i];

  for (i = 1; i < n; i++)
    for (j = 0; j < n - i; j++)
      if (num[j] + max[j + 1][1] > num[j + i] + max[j][1])
      {
        max[j][0] = num[j] + max[j + 1][1];
        max[j][1] = max[j + 1][0];
      }
      else
      {
        temp = max[j][0];
        max[j][0] = num[j + i] + max[j][1];
        max[j][1] = temp;
      }

  fprintf(out, "%d %d\n", max[0][0], max[0][1]);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
