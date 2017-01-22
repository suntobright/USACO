/*
ID: suntobr1
LANG: C
TASK: fence9
*/

#include <stdio.h>

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int n, m, p;
  int begin, end;
  int sum;

  int i;

  in = fopen("fence9.in", "rb");
  out = fopen("fence9.out", "wb");

  fscanf(in, "%d%d%d", &n, &m, &p);

  sum = 0;
  begin = 0;
  end = p;
  for (i = 1; i < m; i++)
  {
    while (begin * m <= n * i)
      begin++;
    while (end * m < m * p + n * i - p * i)
      end++;
    while (end * m >= m * p + n * i - p * i)
      end--;

    sum += end - begin + 1;
  }

  fprintf(out, "%d\n", sum);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
