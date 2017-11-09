/*
ID: suntobr1
LANG: C++11
TASK: betsy
*/

#include <cstdio>

using namespace std;

int n;

bool visited[9][9];
int count;

int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int getUnvisitedNeighbourCount(int row, int col) {
  int count = 0;
  for (auto& direction : directions) {
    int nextRow = row + direction[0];
    int nextCol = col + direction[1];
    if (!visited[nextRow][nextCol]) {
      count ++;
    }
  }
  return count;
}

void goFrom(int row, int col, int steps) {
  if (row == n && col == 1) {
    if (steps == n * n) {
      count ++;
    }
    return;
  }

  if ((visited[row - 1][col] && visited[row + 1][col]
          && !visited[row][col - 1] && !visited[row][col + 1])
      || (!visited[row - 1][col] && !visited[row + 1][col]
          && visited[row][col - 1] && visited[row][col + 1]))
  {
    return;
  }

  int nextRowWithOnlyOneUnvisitedNeighbour = 0;
  int nextColWithOnlyOneUnvisitedNeighbour = 0;
  int nextCountWithOnlyOneUnvisitedNeighbour = 0;
  for (auto& direction : directions) {
    int nextRow = row + direction[0];
    int nextCol = col + direction[1];
    if (!visited[nextRow][nextCol] && (nextRow != n || nextCol != 1)) {
      if (getUnvisitedNeighbourCount(nextRow, nextCol) == 1) {
        nextRowWithOnlyOneUnvisitedNeighbour = nextRow;
        nextColWithOnlyOneUnvisitedNeighbour = nextCol;
        nextCountWithOnlyOneUnvisitedNeighbour ++;
      }
    }
  }

  if (nextCountWithOnlyOneUnvisitedNeighbour > 1) {
    return;
  }

  if (nextCountWithOnlyOneUnvisitedNeighbour == 1) {
    int nextRow = nextRowWithOnlyOneUnvisitedNeighbour;
    int nextCol = nextColWithOnlyOneUnvisitedNeighbour;
    visited[nextRow][nextCol] = true;
    goFrom(nextRow, nextCol, steps + 1);
    visited[nextRow][nextCol] = false;
    return;
  }

  for (auto& direction : directions) {
    int nextRow = row + direction[0];
    int nextCol = col + direction[1];
    if (!visited[nextRow][nextCol]) {
      visited[nextRow][nextCol] = true;
      goFrom(nextRow, nextCol, steps + 1);
      visited[nextRow][nextCol] = false;
    }
  }
}

int main(void)
{
  FILE* fin = fopen("betsy.in", "rb");
  FILE* fout = fopen("betsy.out", "wb");

  fscanf(fin, "%d", &n);

  for (int i = 0; i <= n + 1; i ++) {
    visited[0][i] = true;
    visited[i][0] = true;
    visited[n + 1][i] = true;
    visited[i][n + 1] = true;
  }

  visited[1][1] = true;
  goFrom(1, 1, 1);

  fprintf(fout, "%d\n", count);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
