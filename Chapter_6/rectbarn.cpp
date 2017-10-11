/*
ID: suntobr1
LANG: C++11
TASK: rectbarn
*/

#include <stdio.h>

#include <vector>

using namespace std;

int main(void)
{
  FILE* fin = fopen("rectbarn.in", "rb");
  FILE* fout = fopen("rectbarn.out", "wb");

  int rows = 0;
  int columns = 0;
  int pieces = 0;

  fscanf(fin, "%d%d%d", &rows, &columns, &pieces);
  vector<vector<bool> > field(rows, vector<bool>(columns, false));

  for (int i = 0; i < pieces; i ++) {
    int row = 0;
    int column = 0;

    fscanf(fin, "%d%d", &row, &column);
    field[row - 1][column - 1] = true;
  }

  vector<int> heights(columns, 0);
  vector<int> leftExpands(columns, columns);
  vector<int> rightExpands(columns, columns);
  int maxArea = 0;
  for (int i = 0; i < rows; i ++) {
    int begin = 0;
    int end = 0;
    while (end < columns) {
      while (end < columns && field[i][end] == false) {
        end ++;
      }

      if (end < columns) {
        heights[end] = 0;
        leftExpands[end] = columns;
        rightExpands[end] = columns;
      }

      for (int j = begin; j < end; j ++) {
        heights[j] ++;
        leftExpands[j] = min(leftExpands[j], j - begin);
        rightExpands[j] = min(rightExpands[j], end - j);

        int area = heights[j] * (leftExpands[j] + rightExpands[j]);
        if (maxArea < area) {
          maxArea = area;
        }
      }

      end ++;
      begin = end;
    }
  }

  fprintf(fout, "%d\n", maxArea);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
