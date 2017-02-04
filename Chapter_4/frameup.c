/*
ID: suntobr1
LANG: C
TASK: frameup
*/

#include <stdio.h>

int height;
int width;
char array[30][31];

int hits[26];
int bounds[26][4];

int orders[26][26];

char result[27];

void printResult(int pos, FILE* fout) {
  int i = 0;
  int j = 0;

  int flag = 0;

  for (i = 0; i < 26; i ++) {
    if (hits[i] == 1) {
      for (j = 0; j < 26; j ++) {
        if (hits[j] == 1 && orders[j][i] == 1) {
          break;
        }
      }
      if (j == 26) {
        result[pos] = 'A' + i;
        hits[i] = 0;
        printResult(pos + 1, fout);
        hits[i] = 1;
      }
      flag = 1;
    }
  }

  if (flag == 0) {
    result[pos] = '\0';
    fprintf(fout, "%s\n", result);
  }
}

int main(void)
{
  FILE* fin = fopen("frameup.in", "rb");
  FILE* fout = fopen("frameup.out", "wb");

  int i = 0;
  int j = 0;

  fscanf(fin, "%d%d", &height, &width);
  for (i = 0; i < height; i ++) {
    fscanf(fin, "%s", array[i]);
  }

  for (i = 0; i < 26; i ++) {
    bounds[i][0] = 0x7fffffff;
    bounds[i][1] = 0x7fffffff;
  }

  for (i = 0; i < height; i ++) {
    for (j = 0; j < width; j ++) {
      if (array[i][j] != '.') {
        hits[array[i][j] - 'A'] = 1;
        if (bounds[array[i][j] - 'A'][0] > i) {
          bounds[array[i][j] - 'A'][0] = i;
        }
        if (bounds[array[i][j] - 'A'][1] > j) {
          bounds[array[i][j] - 'A'][1] = j;
        }
        if (bounds[array[i][j] - 'A'][2] < i) {
          bounds[array[i][j] - 'A'][2] = i;
        }
        if (bounds[array[i][j] - 'A'][3] < j) {
          bounds[array[i][j] - 'A'][3] = j;
        }
      }
    }
  }

  for (i = 0; i < 26; i ++) {
    if (hits[i] == 1) {
      for (j = bounds[i][0]; j <= bounds[i][2]; j ++) {
        if (array[j][bounds[i][1]] != '.' && array[j][bounds[i][1]] - 'A' != i) {
          orders[i][array[j][bounds[i][1]] - 'A'] = 1;
        }
        if (array[j][bounds[i][3]] != '.' && array[j][bounds[i][3]] - 'A' != i) {
          orders[i][array[j][bounds[i][3]] - 'A'] = 1;
        }
      }
      for (j = bounds[i][1]; j <= bounds[i][3]; j ++) {
        if (array[bounds[i][0]][j] != '.' && array[bounds[i][0]][j] - 'A' != i) {
          orders[i][array[bounds[i][0]][j] - 'A'] = 1;
        }
        if (array[bounds[i][2]][j] != '.' && array[bounds[i][2]][j] - 'A' != i) {
          orders[i][array[bounds[i][2]][j] - 'A'] = 1;
        }
      }
    }
  }

  printResult(0, fout);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
