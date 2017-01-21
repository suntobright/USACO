/*
ID: suntobr1
LANG: C
TASK: combo
*/

#include <stdio.h>

int main(void)
{
  FILE* fin = fopen("combo.in", "rb");
  FILE* fout = fopen("combo.out", "wb");

  int n = 0;
  int combos[2][3] = {{0}};
  int count = 1;

  int i = 0;
  int j = 0;

  int diff = 0;
  int overlap = 0;

  fscanf(fin, "%d", &n);
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {
      fscanf(fin, "%d", &combos[i][j]);
    }
  }

  if (n <= 5) {
    count = n * n * n;
  } else {
    for (i = 0; i < 3; i++) {
      diff = combos[0][i] - combos[1][i];
      if (diff < 0) {
        diff = -diff;
      }
      overlap = 0;
      if (diff > 5) {
        overlap += 0;
      } else {
        overlap += 5 - diff;
      }
      diff = n - diff;
      if (diff > 5) {
        overlap += 0;
      } else {
        overlap += 5 - diff;
      }

      count *= overlap;
    }

    count = 250 - count;
  }



  fprintf(fout, "%d\n", count);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
