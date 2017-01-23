/*
ID: suntobr1
LANG: C
TASK:
*/

#include <stdio.h>

int main(void)
{
  FILE* fin = fopen(".in", "rb");
  FILE* fout = fopen(".out", "wb");

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
