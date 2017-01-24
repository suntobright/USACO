/*
ID: suntobr1
LANG: C
TASK: buylow
*/

#include <stdio.h>

#define COUNT_SIZE  10

int n;
int prices[5001];
int nexts[5001];
int lengths[5001];
int counts[5001][COUNT_SIZE];

int add(int a[], int b[]) {
  int i = 0;
  int flag = 0;

  for (i = 0; i < COUNT_SIZE; i++) {
    a[i] += b[i] + flag;
    flag = a[i] / 1000000000;
    a[i] %= 1000000000;
  }

  return flag;
}

void set(int a[], int b[]) {
  int i = 0;
  for (i = 0; i < COUNT_SIZE; i++) {
    a[i] = b[i];
  }
}

void print(FILE* fout, int a[]) {
  int i = 0;
  int flag = 0;

  for (i = COUNT_SIZE - 1; i >= 0; i--) {
    if (flag == 0) {
      if (a[i] != 0) {
        flag = 1;
        fprintf(fout, "%d", a[i]);
      }
    } else {
      fprintf(fout, "%09d", a[i]);
    }
  }

  if (flag == 0) {
    fprintf(fout, "0");
  }
  fprintf(fout, "\n");
}

int main(void)
{
  FILE* fin = fopen("buylow.in", "rb");
  FILE* fout = fopen("buylow.out", "wb");

  int i = 0;
  int j = 0;

  int flag = 0;

  fscanf(fin, "%d", &n);
  for (i = 0; i < n; i++) {
    fscanf(fin, "%d", &prices[i]);
  }

  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (prices[i] == prices[j]) {
        break;
      }
    }
    nexts[i] = j;
    lengths[i] = 1;
    counts[i][0] = 1;
  }

  for (i = 0; i < n + 1; i++) {
    for (j = 0; j < i; j++) {
      if (nexts[j] < i) {
        continue;
      }

      if (prices[j] > prices[i]) {
        if (lengths[j] + 1 == lengths[i]) {
          flag = add(counts[i], counts[j]);
          if (flag != 0) {
            fprintf(fout, "Warning: COUNT_SIZE is too small\n");
          }
        } else if (lengths[j] + 1 > lengths[i]) {
          lengths[i] = lengths[j] + 1;
          set(counts[i], counts[j]);
        }
      }
    }
  }

  fprintf(fout, "%d ", lengths[n] - 1);
  print(fout, counts[n]);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
