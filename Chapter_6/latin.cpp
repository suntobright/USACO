/*
ID: suntobr1
LANG: C++11
TASK: latin
*/

#include <cstdio>

using namespace std;

int n;

int square[7][7];
bool usedInRow[7][7];
bool usedInCol[7][7];

int cache[4][13];

int fill(int row, int col) {
  if (row == n) {
    return 1;
  }

  int cycleCount = 0;
  int cycleProduct = 1;
  if (row == 2 && col == 1) {
    bool visited[7] = {false};
    for (int i = 0; i < n; i ++) {
      if (!visited[i]) {
        visited[i] = true;

        int cycleLength = 1;
        for (int next = square[1][i]; next != i; next = square[1][next]) {
          visited[next] = true;
          cycleLength ++;
        }

        cycleCount ++;
        cycleProduct *= cycleLength;
      }
    }

    if (cache[cycleCount][cycleProduct] != -1) {
      return cache[cycleCount][cycleProduct];
    }
  }

  int count = 0;
  for (int i = 0; i < n; i ++) {
    if (!usedInRow[row][i] && !usedInCol[col][i]) {
      usedInRow[row][i] = usedInCol[col][i] = true;
      square[row][col] = i;
      count += col < n - 1 ? fill(row, col + 1) : fill(row + 1, 1);
      usedInRow[row][i] = usedInCol[col][i] = false;
    }
  }

  if (row == 2 && col == 1) {
    cache[cycleCount][cycleProduct] = count;
  }

  return count;
}

int main(void)
{
  FILE* fin = fopen("latin.in", "rb");
  FILE* fout = fopen("latin.out", "wb");

  fscanf(fin, "%d", &n);

  for (int i = 0; i < n; i ++) {
    square[0][i] = i;
    square[i][0] = i;

    usedInRow[0][i] = true;
    usedInRow[i][i] = true;
    usedInCol[0][i] = true;
    usedInCol[i][i] = true;
  }

  for (auto& row : cache) {
    for (auto& value : row) {
      value = -1;
    }
  }

  long long count = fill(1, 1);
  for (int i = 2; i < n; i ++) {
    count *= i;
  }

  fprintf(fout, "%lld\n", count);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
