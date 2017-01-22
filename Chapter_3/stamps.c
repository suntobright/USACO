/*
ID: suntobr1
LANG: C
TASK: stamps
*/

#include <stdio.h>

unsigned char count[2001920];

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int k, n;
  int cent[64];

  int i, j;
  unsigned char min;

  in = fopen("stamps.in", "rb");
  out = fopen("stamps.out", "wb");

  fscanf(in, "%d%d", &k, &n);
  for (i = 0; i < n; i++)
    fscanf(in, "%d", &cent[i]);

  for (i = 1; i < 2001920; i++)
    count[i] = 0xf0;

  for (i = 1;; i++)
  {
    min = 0xf0;
    for (j = 0; j < n; j++)
      if (i >= cent[j] && min > count[i - cent[j]] + 1)
        min = count[i - cent[j]] + 1;

    if (min > k)
      break;

    count[i] = min;
  }

  fprintf(out, "%d\n", i - 1);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
