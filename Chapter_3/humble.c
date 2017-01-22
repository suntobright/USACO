/*
ID: suntobr1
LANG: C
TASK: humble
*/

#include <stdio.h>

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int k, n;
  int prime[128];

  int pos[128] = { 0 };
  int num[100352] = { 1 };
  int count = 1;

  int i;
  int min;
  int pick;

  in = fopen("humble.in", "rb");
  out = fopen("humble.out", "wb");

  fscanf(in, "%d%d", &k, &n);
  for (i = 0; i < k; i++)
    fscanf(in, "%d", &prime[i]);

  while (count != n + 1)
  {
    min = 0x7fffffff;
    pick = -1;
    for (i = 0; i < k; i++)
    {
      while (num[pos[i]] * prime[i] <= num[count - 1])
        pos[i] ++;

      if (min > num[pos[i]] * prime[i])
      {
        min = num[pos[i]] * prime[i];
        pick = i;
      }
    }

    num[count++] = min;
    pos[pick] ++;
  }

  fprintf(out, "%d\n", num[n]);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
