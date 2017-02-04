/*
ID: suntobr1
LANG: C
TASK: shuttle
*/

#include <stdio.h>

int main(void)
{
  FILE* fin = fopen("shuttle.in", "rb");
  FILE* fout = fopen("shuttle.out", "wb");

  int n = 0;
  int numbers[256] = {0};
  int count = 0;

  int length = 0;
  int i = 0;
  int j = 0;
  int sign = 0;

  fscanf(fin, "%d", &n);

  numbers[count ++] = n;
  sign = 1;
  for (length = 2; length <= n + 1; length ++) {
    for (i = 1; i < length; i ++) {
      numbers[count] = numbers[count - 1] + sign * 2;
      count ++;
    }
    numbers[count] = numbers[count - 1] + sign;
    count ++;
    sign *= -1;
  }

  numbers[count - 1] = numbers[count - 2] + sign;
  for (length = n; length >= 2; length --) {
    for (i = 1; i < length; i ++) {
      numbers[count] = numbers[count - 1] + sign * 2;
      count ++;
    }
    numbers[count] = numbers[count - 1] - sign;
    count ++;
    sign *= -1;
  }

  for (i = 0; i < count;) {
    fprintf(fout, "%d", numbers[i ++]);
    for (j = 0; j < 19 && i < count; i ++, j ++) {
      fprintf(fout, " %d", numbers[i]);
    }
    fprintf(fout, "\n");
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
