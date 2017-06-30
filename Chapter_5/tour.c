/*
ID: suntobr1
LANG: C
TASK: tour
*/

#include <stdio.h>
#include <string.h>

int cityCount;
char cities[100][16];
int flightCount;
int flights[100][100];

int visitedCounts[100][100];

int max(int a, int b) {
  return a > b ? a : b;
}

int locate(char city[]) {
  int i = 0;
  for (i = 0; i < cityCount; i ++) {
    if (strcmp(cities[i], city) == 0) {
      break;
    }
  }
  return i;
}

int main(void)
{
  FILE* fin = fopen("tour.in", "rb");
  FILE* fout = fopen("tour.out", "wb");

  int i = 0;
  int j = 0;
  int k = 0;

  int row = 0;
  int col = 0;
  char city[16] = "";

  int maxCount = 0;

  fscanf(fin, "%d%d", &cityCount, &flightCount);
  for (i = 0; i < cityCount; i ++) {
    fscanf(fin, "%s", cities[i]);
  }
  for (i = 0; i < flightCount; i ++) {
    fscanf(fin, "%s", city);
    row = locate(city);
    fscanf(fin, "%s", city);
    col = locate(city);
    flights[row][col] = flights[col][row] = 1;
  }

  visitedCounts[0][0] = 1;
  for (i = 0; i < cityCount; i ++) {
    for (j = i + 1; j < cityCount; j ++) {
      maxCount = 0;
      for (k = 0; k < j; k ++) {
        if (flights[k][j] == 1) {
          maxCount = max(maxCount, visitedCounts[i][k]);
        }
      }
      if (maxCount > 0) {
        visitedCounts[i][j] = visitedCounts[j][i] = maxCount + 1;
      }
    }
  }

  maxCount = 0;
  for (i = 0; i < cityCount - 1; i ++) {
    if (flights[i][cityCount - 1] == 1) {
      maxCount = max(maxCount, visitedCounts[cityCount - 1][i]);
    }
  }
  visitedCounts[cityCount - 1][cityCount - 1] = maxCount;

  fprintf(fout, "%d\n", max(1, visitedCounts[cityCount - 1][cityCount - 1]));

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
