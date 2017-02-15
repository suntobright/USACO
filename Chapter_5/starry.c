/*
ID: suntobr1
LANG: C
TASK: starry
*/

#include <stdio.h>
#include <string.h>

int height;
int width;
char sky[100][101];

int clusterCount;
char clusters[500][100][101];
int positions[500][2];
int boundaries[500][4];

char variants[8][100][101];
int variantSizes[8][2];

void mark(int posX, int posY, char map[][101], char symbol, int index) {
  int queue[10000][2] = {{0}};
  int begin = 0;
  int end = 0;

  int i = 0;
  int j = 0;

  map[posX][posY] = symbol;
  if (index != -1) {
    clusters[index][posX][posY] = '1';
    boundaries[index][0] = boundaries[index][2] = posX;
    boundaries[index][1] = boundaries[index][3] = posY;
  }

  queue[begin][0] = posX;
  queue[begin ++][1] = posY;
  while (begin != end) {
    int x = queue[end][0];
    int y = queue[end ++][1];

    for (i = x > 0 ? x - 1 : 0; i <= x + 1 && i < height; i ++) {
      for (j = y > 0 ? y - 1 : 0; j <= y + 1 && j < width; j ++) {
        if (map[i][j] == '1') {
          map[i][j] = symbol;
          if (index != -1) {
            clusters[index][i][j] = '1';
            boundaries[index][0] = boundaries[index][0] < i ? boundaries[index][0] : i;
            boundaries[index][1] = boundaries[index][1] < j ? boundaries[index][1] : j;
            boundaries[index][2] = boundaries[index][2] > i ? boundaries[index][2] : i;
            boundaries[index][3] = boundaries[index][3] > j ? boundaries[index][3] : j;
          }

          queue[begin][0] = i;
          queue[begin ++][1] = j;
        }
      }
    }
  }

  if (index != -1) {
    for (i = boundaries[index][0]; i <= boundaries[index][2]; i ++) {
      for (j = boundaries[index][1]; j <= boundaries[index][3]; j ++) {
        if (clusters[index][i][j] == '1') {
          clusters[index][i][j] = 0;
          clusters[index][i - boundaries[index][0]][j - boundaries[index][1]] = '1';
        } else {
          clusters[index][i - boundaries[index][0]][j - boundaries[index][1]] = '0';
        }
      }
    }

    boundaries[index][2] -= boundaries[index][0];
    boundaries[index][3] -= boundaries[index][1];
    boundaries[index][0] -= boundaries[index][0];
    boundaries[index][1] -= boundaries[index][1];
  }
}

void generate(int index) {
  int i = 0;
  int j = 0;

  int x = boundaries[index][2];
  int y = boundaries[index][3];

  for (i = 0; i <= x; i ++) {
    for (j = 0; j <= y; j ++) {
      variants[0][i][j]         = clusters[index][i][j];
      variants[1][x - i][j]     = clusters[index][i][j];
      variants[2][i][y - j]     = clusters[index][i][j];
      variants[3][x - i][y - j] = clusters[index][i][j];
      variants[4][j][i]         = clusters[index][i][j];
      variants[5][j][x - i]     = clusters[index][i][j];
      variants[6][y - j][i]     = clusters[index][i][j];
      variants[7][y - j][x - i] = clusters[index][i][j];
    }
  }

  for (i = 0; i < 4; i ++) {
    variantSizes[i][0] = x;
    variantSizes[i][1] = y;
  }

  for (i = 4; i < 8; i ++) {
    variantSizes[i][0] = y;
    variantSizes[i][1] = x;
  }
}

int match(int index) {
  int i = 0;
  int j = 0;

  for (i = 0; i < 8; i ++) {
    if (boundaries[index][2] == variantSizes[i][0]
        && boundaries[index][3] == variantSizes[i][1]) {
      for (j = 0; j <= boundaries[index][2]; j ++) {
        if (memcmp(clusters[index][j], variants[i][j], boundaries[index][3] + 1) != 0) {
          break;
        }
      }

      if (j > boundaries[index][2]) {
        return 1;
      }
    }
  }

  return 0;
}

int main(void)
{
  FILE* fin = fopen("starry.in", "rb");
  FILE* fout = fopen("starry.out", "wb");

  int i = 0;
  int j = 0;

  char symbol = 'a';

  char tempSky[100][101] = {{0}};

  fscanf(fin, "%d%d", &width, &height);
  for (i = 0; i < height; i ++) {
    fscanf(fin, "%s", sky[i]);
    strcpy(tempSky[i], sky[i]);
  }

  for (i = 0; i < height; i ++) {
    for (j = 0; j < width; j ++) {
      if (tempSky[i][j] == '1') {
        positions[clusterCount][0] = i;
        positions[clusterCount][1] = j;
        mark(i, j, tempSky, '0', clusterCount ++);
      }
    }
  }

  symbol = 'a';
  for (i = 0; i < clusterCount; i ++) {
    if (sky[positions[i][0]][positions[i][1]] == '1') {
      mark(positions[i][0], positions[i][1], sky, symbol, -1);
      generate(i);
      for (j = i + 1; j < clusterCount; j ++) {
        if (match(j) == 1) {
          mark(positions[j][0], positions[j][1], sky, symbol, -1);
        }
      }
      symbol ++;
    }
  }

  for (i = 0; i < height; i ++) {
    fprintf(fout, "%s\n", sky[i]);
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
