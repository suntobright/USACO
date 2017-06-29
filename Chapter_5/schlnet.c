/*
ID: suntobr1
LANG: C
TASK: schlnet
*/

#include <stdio.h>

#define ONE_WAY   0
#define BOTH_WAY  1

int net[128][128];
int visited[128];
int count = 0;
int blockCount = 0;
int zeroOutCount = 0;
int zeroInCount = 0;

int max(int a, int b) {
  return a > b ? a : b;
}

void flood(int pos, int direction) {
  int i = 0;
  for (i = 0; i < count; i ++) {
    if (pos != i && visited[i] == 0) {
      if (net[pos][i] == 1 || (direction == BOTH_WAY && net[i][pos] == 1)) {
        visited[i] = 1;
        flood(i, direction);
      }
    }
  }
}

int main(void)
{
  FILE* fin = fopen("schlnet.in", "rb");
  FILE* fout = fopen("schlnet.out", "wb");

  int i = 0;
  int j = 0;
  int result = 0;

  fscanf(fin, "%d", &count);
  for (i = 0; i < count; i ++) {
    while (1) {
      fscanf(fin, "%d", &j);
      if (j == 0) {
        break;
      }
      net[i][j - 1] = 1;
    }
  }

  for (i = 0; i < count; i ++) {
    for (j = 0; j < count; j ++) {
      if (i != j) {
        if (net[j][i] == 1) {
          break;
        }
      }
    }
    if (j == count) {
      zeroInCount ++;
      visited[i] = 1;
      flood(i, ONE_WAY);
    }
    for (j = 0; j < count; j ++) {
      if (i != j) {
        if (net[i][j] == 1) {
          break;
        }
      }
    }
    if (j == count) {
      zeroOutCount ++;
    }
  }

  for (i = 0; i < count; i ++) {
    if (visited[i] == 0) {
      blockCount ++;
      visited[i] = 1;
      flood(i, BOTH_WAY);
    }
  }

  result = zeroInCount + blockCount;
  fprintf(fout, "%d\n", result);
  if (zeroInCount == 0 && zeroOutCount == 0) {
    result = blockCount == 1 ? 0 : blockCount;
  } else {
    result = max(zeroInCount + blockCount, zeroOutCount);
  }
  fprintf(fout, "%d\n", result);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
