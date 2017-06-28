/*
ID: suntobr1
LANG: C
TASK: snail
*/


#include <stdio.h>

int n;
char grid[128][128];

int getLength(int x, int y, int dx, int dy, int length) {
  int i = 0;

  int currentLength = 0;
  int length1 = 0;
  int length2 = 0;

  while (x + dx >= 0 && x + dx < n
      && y + dy >= 0 && y + dy < n
      && grid[x + dx][y + dy] == '.') {
    currentLength ++;
    x += dx;
    y += dy;
    grid[x][y] = dx == 0 ? '-' : '|';
  }

  if (currentLength == 0) {
    return length;
  }

  length += currentLength;
  if (x + dx == -1 || x + dx == n
      || y + dy == -1 || y + dy == n
      || grid[x + dx][y + dy] == '#') {
    grid[x][y] = '+';
    if (dx == 0) {
      length1 = getLength(x, y, 1, 0, length);
      length2 = getLength(x, y, -1, 0, length);
    } else if (dy == 0) {
      length1 = getLength(x, y, 0, 1, length);
      length2 = getLength(x, y, 0, -1, length);
    }
    length = length1 > length2 ? length1 : length2;
  }

  for (i = 0; i < currentLength; i ++) {
    grid[x][y] = '.';
    x -= dx;
    y -= dy;
  }

  return length;
}

int main(void)
{
  FILE* fin = fopen("snail.in", "rb");
  FILE* fout = fopen("snail.out", "wb");

  int barrierCount = 0;

  int i = 0;
  int j = 0;

  char x = 0;
  char y = 0;

  int length1 = 0;
  int length2 = 0;

  fscanf(fin, "%d%d", &n, &barrierCount);
  for (i = 0; i < n; i ++) {
    for (j = 0; j < n; j ++) {
      grid[i][j] = '.';
    }
  }
  grid[0][0] = '+';

  for (i = 0; i < barrierCount; i ++) {
    fscanf(fin, "\n%c%hhd", &x, &y);
    x -= 'A';
    y --;
    grid[(int) x][(int) y] = '#';
  }

  length1 = getLength(0, 0, 1, 0, 1);
  length2 = getLength(0, 0, 0, 1, 1);

  fprintf(fout, "%d\n", length1 > length2 ? length1 : length2);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
