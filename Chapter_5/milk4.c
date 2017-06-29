/*
ID: suntobr1
LANG: C
TASK: milk4
*/

#include <stdio.h>
#include <stdlib.h>

int goal;
int could[20001];

int pailCount;
int pails[128];
int picked[128];

int currentPicks[128];
int currentPickCount;

int bestPicks[128];
int bestPickCount;

int cmp(const void* a, const void* b) {
  return *((const int *) a) - *((const int *) b);
}

int couldFill() {
  int i = 0;
  int j = 0;

  currentPickCount = 0;
  for (i = 0; i < pailCount; i ++) {
    if (picked[i] == 1) {
      currentPicks[currentPickCount ++] = pails[i];
    }
  }

  for (i = 0; i <= goal; i ++) {
    could[i] = 0;
  }

  could[0] = 1;
  for (i = 1; i <= goal; i ++) {
    for (j = 0; j < currentPickCount && i - currentPicks[j] >= 0; j ++) {
      if (could[i - currentPicks[j]] == 1) {
        could[i] = 1;
        break;
      }
    }
  }

  if (could[goal] == 1) {
    if (currentPickCount < bestPickCount) {
      for (i = 0; i < currentPickCount; i ++) {
        bestPicks[i] = currentPicks[i];
      }
      bestPickCount = currentPickCount;
    }
    return 1;
  }

  return 0;
}

void dfsPick(int start, int alreadyPickCount, int alreadyPickSize) {
  int i = 0;

  if (alreadyPickCount >= bestPickCount - 1 || alreadyPickSize >= goal) {
    return;
  }

  for (i = start; i < pailCount; i ++) {
    if (picked[i] == 0) {
      picked[i] = 1;
      if (couldFill() == 0) {
        dfsPick(i + 1, alreadyPickCount + 1, alreadyPickSize + pails[i]);
      } else {
        picked[i] = 0;
        break;
      }
      picked[i] = 0;
    }
  }
}

int main(void)
{
  FILE* fin = fopen("milk4.in", "rb");
  FILE* fout = fopen("milk4.out", "wb");

  int i = 0;
  int j = 0;

  fscanf(fin, "%d", &goal);
  fscanf(fin, "%d", &pailCount);
  for (i = 0; i < pailCount; i ++) {
    fscanf(fin, "%d", &pails[i]);
  }

  qsort(pails, pailCount, sizeof(int), cmp);
  for (i = 1, j = 0; i < pailCount; i ++) {
    if (pails[i] != pails[j]) {
      pails[++ j] = pails[i];
    }
  }
  pailCount = j + 1;

  for (i = 0; i < pailCount; i ++) {
    bestPicks[i] = pails[i];
  }
  bestPickCount = pailCount;

  dfsPick(0, 0, 0);

  fprintf(fout, "%d", bestPickCount);
  for (i = 0; i < bestPickCount; i ++) {
    fprintf(fout, " %d", bestPicks[i]);
  }
  fprintf(fout, "\n");

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
