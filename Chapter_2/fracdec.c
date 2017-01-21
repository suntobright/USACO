/*
ID: suntobr1
LANG: C
TASK: fracdec
*/

#include <stdio.h>

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int n, d;
  int before;
  char after[102400] = ".";
  int pos[102400] = { 0 };
  int cur;

  char result[102400];

  int i;

  in = fopen("fracdec.in", "rb");
  out = fopen("fracdec.out", "wb");

  fscanf(in, "%d%d", &n, &d);

  before = n / d;
  n %= d;

  cur = 1;
  while (pos[n] == 0)
  {
    pos[n] = cur;

    n *= 10;
    after[cur++] = (n / d) + '0';
    n %= d;
  }

  if (n != 0)
  {
    after[cur + 1] = ')';
    for (i = cur; i > pos[n]; i--)
      after[i] = after[i - 1];
    after[i] = '(';
  }
  else if (cur != 2)
    after[--cur] = '\0';

  sprintf(result, "%d%s", before, after);

  for (i = 0; result[i] != '\0'; i++)
  {
    fprintf(out, "%c", result[i]);
    if ((i + 1) % 76 == 0)
      fprintf(out, "\n");
  }
  fprintf(out, "\n");

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
