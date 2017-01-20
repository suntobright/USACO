/*
ID: suntobr1
LANG: C
TASK: test
*/

#include <stdio.h>

int main()
{
  FILE *fin, *fout;
  int a, b;

  fin = fopen("test.in", "r");
  fout = fopen("test.out", "w");

  fscanf(fin, "%d %d", &a, &b);
  fprintf(fout, "%d\n", a + b);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
