/*
ID: suntobr1
LANG: C
TASK: bigbrn
*/

#include <stdio.h>

int max(int a, int b) {
  return a > b ? a : b;
}

int min(int a, int b) {
  return a < b ? a : b;
}

int main(void)
{
  FILE* fin = fopen("bigbrn.in", "rb");
  FILE* fout = fopen("bigbrn.out", "wb");

  int grid[1024][1024];
  int gridLength = 0;
  int maxLength = 0;
  int treeCount = 0;
  int row = 0;
  int col = 0;

  int i;
  int j;

  fscanf(fin, "%d%d", &gridLength, &treeCount);
  for (i = 0; i < gridLength; i ++) {
    for (j = 0; j < gridLength; j ++) {
      grid[i][j] = 1;
    }
  }
  for (i = 0; i < treeCount; i ++) {
    fscanf(fin, "%d%d", &row, &col);
    grid[row - 1][col - 1] = 0;
  }

  maxLength = grid[0][0];
  for (i = 1; i < gridLength; i ++) {
    maxLength = max(maxLength, grid[0][i]);
    maxLength = max(maxLength, grid[i][0]);
  }

  for (i = 1; i < gridLength; i ++) {
    for (j = 1; j < gridLength; j ++) {
      if (grid[i][j] == 1) {
        grid[i][j] = min(grid[i - 1][j], grid[i][j - 1]);
        grid[i][j] = min(grid[i - 1][j - 1], grid[i][j]);
        grid[i][j] ++;
        maxLength = max(maxLength, grid[i][j]);
      }
    }
  }

  fprintf(fout, "%d\n", maxLength);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
