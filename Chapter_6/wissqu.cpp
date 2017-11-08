/*
ID: suntobr1
LANG: C++11
TASK: wissqu
*/

#include <algorithm>
#include <cstdio>

using namespace std;

FILE* fin;
FILE* fout;

char pasture[4][5];
bool replaced[4][4];
int herdCounts[5] = {3, 3, 3, 4, 3};

char herds[16];
int rows[16];
int cols[16];
int pos;
bool printed;

int wayCount;

inline bool couldReplace(int row, int col, char herd) {
  for (int i = max(row - 1, 0); i <= min(row + 1, 3); i ++) {
    for (int j = max(col - 1, 0); j <= min(col + 1, 3); j ++) {
      if (pasture[i][j] == herd) {
        return false;
      }
    }
  }

  return true;
}

void replace() {
  if (pos == 16) {
    if (!printed) {
      for (int i = 0; i < 16; i ++) {
        fprintf(fout, "%c %d %d\n", herds[i], rows[i], cols[i]);
      }
      printed = true;
    }
    wayCount ++;
  } else {
    for (char herd = 'A'; herd <= 'E'; herd ++) {
      if (herdCounts[herd - 'A'] > 0) {
        herds[pos] = herd;
        herdCounts[herd - 'A'] --;
        for (int i = 0; i < 4; i ++) {
          for (int j = 0; j < 4; j ++) {
            if (!replaced[i][j] && couldReplace(i, j, herd)) {
              char originalHerd = pasture[i][j];
              pasture[i][j] = herd;
              replaced[i][j] = true;
              rows[pos] = i + 1;
              cols[pos] = j + 1;
              pos ++;
              replace();
              pasture[i][j] = originalHerd;
              replaced[i][j] = false;
              pos --;
            }
          }
        }
        herdCounts[herd - 'A'] ++;
      }
    }
  }
}

int main(void)
{
  fin = fopen("wissqu.in", "rb");
  fout = fopen("wissqu.out", "wb");

  for (int i = 0; i < 4; i ++) {
    fscanf(fin, "%s", pasture[i]);
  }

  herds[pos] = 'D';
  herdCounts['D' - 'A'] --;
  for (int i = 0; i < 4; i ++) {
    for (int j = 0; j < 4; j ++) {
      if (couldReplace(i, j, 'D')) {
        char originalHerd = pasture[i][j];
        pasture[i][j] = 'D';
        replaced[i][j] = true;
        rows[pos] = i + 1;
        cols[pos] = j + 1;
        pos ++;
        replace();
        pasture[i][j] = originalHerd;
        replaced[i][j] = false;
        pos --;
      }
    }
  }

  fprintf(fout, "%d\n", wayCount);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
