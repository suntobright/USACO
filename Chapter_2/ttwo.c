/*
ID: suntobr1
LANG: C
TASK: ttwo
*/

#include <stdio.h>

#define N  0
#define E  1
#define S  2
#define  W  3

typedef struct
{
  int x;
  int y;
  int dir;
} Position;

const int table[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, {0, -1} };

char map[16][16] = { 0 };
char state[16][16][4][16][16][4] = { 0 };

void getNext(Position *pos)
{
  int a = pos->x + table[pos->dir][0];
  int b = pos->y + table[pos->dir][1];

  if (a >= 0 && a < 10)
    if (b >= 0 && b < 10)
      if (map[a][b] != '*')
      {
        pos->x = a;
        pos->y = b;
        return;
      }

  pos->dir = (pos->dir + 1) % 4;
  return;
}

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int i, j;
  Position farmer, cow;
  int steps;

  in = fopen("ttwo.in", "rb");
  out = fopen("ttwo.out", "wb");

  for (i = 0; i < 10; i++)
    fscanf(in, "%s", map[i]);

  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++)
    {
      if (map[i][j] == 'F')
      {
        farmer.x = i;
        farmer.y = j;
        farmer.dir = N;
      }
      else if (map[i][j] == 'C')
      {
        cow.x = i;
        cow.y = j;
        cow.dir = N;
      }
    }

  steps = 0;
  while (farmer.x != cow.x || farmer.y != cow.y)
  {
    if (state[farmer.x][farmer.y][farmer.dir][cow.x][cow.y][cow.dir] == 0)
      state[farmer.x][farmer.y][farmer.dir][cow.x][cow.y][cow.dir] = 1;
    else
      break;

    getNext(&farmer);
    getNext(&cow);

    steps++;
  }

  if (farmer.x != cow.x || farmer.y != cow.y)
    steps = 0;
  fprintf(out, "%d\n", steps);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
