/*
ID: suntobr1
LANG: C
TASK: fact4
*/

#include <stdio.h>

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int n;
  int num;
  int remain = 1;
  int count = 0;

  int i;

  in = fopen("fact4.in", "rb");
  out = fopen("fact4.out", "wb");

  fscanf(in, "%d", &n);

  for (i = 2; i <= n; i++)
  {
    num = i;

    while (num % 2 == 0)
    {
      num /= 2;
      count++;
    }

    while (num % 5 == 0)
    {
      num /= 5;
      count--;
    }

    remain *= num;
    remain %= 10;
  }

  while (count--)
  {
    remain *= 2;
    remain %= 10;
  }

  fprintf(out, "%d\n", remain);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
