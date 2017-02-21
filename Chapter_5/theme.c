/*
ID: suntobr1
LANG: C
TASK: theme
*/

#include <stdio.h>

int count;
int notes[5000];
int next[5000];

int longest = 4;
int flag;

int main(void)
{
  FILE* fin = fopen("theme.in", "rb");
  FILE* fout = fopen("theme.out", "wb");

  int i = 0;
  int j = 0;
  int k = 0;

  int length = 0;

  fscanf(fin, "%d", &count);
  for (i = 0; i < count; i ++) {
    fscanf(fin, "%d", &notes[i]);
  }

  for (i = count - 1; i > 0; i --) {
    notes[i] -= notes[i - 1];
  }

  for (i = 1; i < count - longest * 2; i ++) {
    next[i] = 0;
    k = 0;
    for (j = i + 1; j < count - longest - 1; j ++) {
      while (k > 0 && notes[i + k] != notes[j]) {
        k = next[i + k - 1];
      }
      if (notes[i + k] == notes[j]) {
        k ++;
      }
      next[j] = k;
    }

    length = 0;
    for (j = i + longest + 1; j < count && j <= count + length - longest; j ++) {
      while (length > 0 && notes[i + length] != notes[j]) {
        length = next[i + length - 1];
      }
      if (notes[i + length] == notes[j]) {
        length ++;
        if (i + length * 2 > j) {
          length = next[i + length - 1];
        }
        if (length >= longest) {
          flag = 1;
          longest = length;
        }
      }
    }
  }

  fprintf(fout, "%d\n", flag ? longest + 1 : 0);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
