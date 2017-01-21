/*
ID: suntobr1
LANG: C
TASK: maze1
*/

#include <stdio.h>

const int table[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int w, h;
  char map[256][96] = { 0 };
  int cnt[256][96] = { 0 };
  int list[4096][2] = { 0 };
  int begin = 0;
  int end = 0;

  int i;
  int x, y;
  int a, b;

  in = fopen("maze1.in", "rb");
  out = fopen("maze1.out", "wb");

  fscanf(in, "%d%d", &w, &h);
  fgets(map[0], 96, in);
  for (i = 0; i < h * 2 + 1; i++)
    fgets(map[i], 96, in);

  for (i = 1; i < w * 2 + 1; i += 2)
  {
    if (map[0][i] == ' ' && cnt[1][i] == 0)
    {
      cnt[1][i] = 1;
      list[begin][0] = 1;
      list[begin][1] = i;
      begin++;
    }
    if (map[h * 2][i] == ' ' && cnt[h * 2 - 1][i] == 0)
    {
      cnt[h * 2 - 1][i] = 1;
      list[begin][0] = h * 2 - 1;
      list[begin][1] = i;
      begin++;
    }
  }

  for (i = 1; i < h * 2 + 1; i += 2)
  {
    if (map[i][0] == ' ' && cnt[i][1] == 0)
    {
      cnt[i][1] = 1;
      list[begin][0] = i;
      list[begin][1] = 1;
      begin++;
    }
    if (map[i][w * 2] == ' ' && cnt[i][w * 2 - 1] == 0)
    {
      cnt[i][w * 2 - 1] = 1;
      list[begin][0] = i;
      list[begin][1] = w * 2 - 1;
      begin++;
    }
  }

  while (begin != end)
  {
    x = list[end][0];
    y = list[end][1];
    end++;

    for (i = 0; i < 4; i++)
    {
      a = x + table[i][0];
      b = y + table[i][1];

      if (a > 0 && a < h * 2)
        if (b > 0 && b < w * 2)
          if (map[a][b] == ' ')
          {
            a += table[i][0];
            b += table[i][1];

            if (cnt[a][b] == 0)
            {
              cnt[a][b] = cnt[x][y] + 1;
              list[begin][0] = a;
              list[begin][1] = b;
              begin++;
            }
          }
    }
  }

  fprintf(out, "%d\n", cnt[x][y]);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
