/*
ID: suntobr1
LANG: C
TASK: race3
*/

#include <stdio.h>

int n;
int arrows[51][51];

int marks[51];

int unavoidable(int point) {
  int i = 0;
  int queue[50] = {0};
  int begin = 0;
  int end = 0;

  for (i = 0; i < n; i++) {
    marks[i] = 0;
  }

  marks[0] = 1;
  queue[begin++] = 0;
  while (begin != end) {
    int current = queue[end++];
    if (current == point) {
      continue;
    }
    for (i = 0; arrows[current][i] >= 0; i++) {
      int next = arrows[current][i];
      if (marks[next] == 0) {
        marks[next] = 1;
        queue[begin++] = next;
      }
    }
  }

  if (marks[n - 1] == 1) {
    return 0;
  } else {
    return 1;
  }
}

int splitting(int point) {
  int i = 0;
  int queue[50] = {0};
  int begin = 0;
  int end = 0;

  marks[point] = 2;
  queue[begin++] = point;
  while (begin != end) {
    int current = queue[end++];
    for (i = 0; arrows[current][i] >= 0; i++) {
      int next = arrows[current][i];
      if (marks[next] == 0) {
        marks[next] = 2;
        queue[begin++] = next;
      } else if (marks[next] == 1) {
        return 0;
      }
    }
  }

  return 1;
}

int main(void)
{
  FILE* fin = fopen("race3.in", "rb");
  FILE* fout = fopen("race3.out", "wb");

  int i = 0;
  int j = 0;

  int temp = 0;

  int unavoidables[50] = {0};
  int unavoidableCount = 0;

  int splittings[50] = {0};
  int splittingCount = 0;

  i = 0;
  do {
    j = 0;
    do {
      temp = -2;
      fscanf(fin, "%d", &temp);
      arrows[i][j++] = temp;
    } while (temp >= 0);
    i++;
  } while (temp != -1);
  n = i - 1;

  for (i = 1; i < n - 1; i++) {
    if (unavoidable(i) == 1) {
      unavoidables[unavoidableCount++] = i;
      if (splitting(i) == 1) {
        splittings[splittingCount++] = i;
      }
    }
  }

  fprintf(fout, "%d", unavoidableCount);
  for (i = 0; i < unavoidableCount; i++) {
    fprintf(fout, " %d", unavoidables[i]);
  }
  fprintf(fout, "\n");
  fprintf(fout, "%d", splittingCount);
  for (i = 0; i < splittingCount; i++) {
    fprintf(fout, " %d", splittings[i]);
  }
  fprintf(fout, "\n");

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
