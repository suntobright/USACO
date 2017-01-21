/*
ID: suntobr1
LANG: C
TASK: wormhole
*/

#include <stdio.h>
#include <stdlib.h>

int count;
int coordinates[12][2];
int pairs[12];
int used[12];
int passed[12][2];

int cmp(const void* a, const void* b)
{
  const int* x = a;
  const int* y = b;

  return (x[1] != y[1]) ? x[1] - y[1] : x[0] - y[0];
}

int check_trapped()
{
  int start = 0;
  int pos = 0;
  int through_wormhole = 0;

  int i, j;

  for (start = 0; start < count; start ++)
  {
    pos = start;
    through_wormhole = 0;
    for (i = 0; i < count; i ++)
      for (j = 0; j < 2; j ++)
        passed[i][j] = 0;

    do {
      if (passed[pos][through_wormhole] == 1)
        return 1;

      passed[pos][through_wormhole] = 1;
      if (through_wormhole == 0)
      {
        for (i = 0; i < count; i ++)
          if (pairs[i] == pos)
            break;
        pos = i % 2 == 0 ? pairs[i + 1] : pairs[i - 1];
        through_wormhole = 1;
      }
      else
      {
        if (pos + 1 < count && coordinates[pos][1] == coordinates[pos + 1][1])
          pos = pos + 1;
        else
          pos = -1;
        through_wormhole = 0;
      }
    }
    while (pos != -1);
  }

  return 0;
}

int get_possible_count(int pos)
{
  int i = 0;
  int result = 0;

  if (pos == count)
  {
    if (check_trapped() == 1)
      result = 1;
  }
  else if (pos % 2 == 0)
  {
    for (i = 0; i < count; i ++)
      if (used[i] == 0)
        break;

    used[i] = 1;
    pairs[pos] = i;
    result += get_possible_count(pos + 1);
    used[i] = 0;
  }
  else
  {
    for (i = pairs[pos - 1] + 1; i < count; i ++)
      if (used[i] == 0)
      {
        used[i] = 1;
        pairs[pos] = i;
        result += get_possible_count(pos + 1);
        used[i] = 0;
      }
    }

  return result;
}

int main(void)
{
  FILE* fin = fopen("wormhole.in", "rb");
  FILE* fout = fopen("wormhole.out", "wb");

  int result = 0;

  int i = 0;

  fscanf(fin, "%d", &count);
  for (i = 0; i < count; i ++)
    fscanf(fin, "%d%d", &coordinates[i][0], &coordinates[i][1]);

  qsort(coordinates, count, sizeof(coordinates[0]), cmp);

  for (i = 0; i < count; i ++)
    used[i] = 0;

  result = get_possible_count(0);

  fprintf(fout, "%d\n", result);

  fclose(fin);
  fclose(fout);

  return 0;
}
