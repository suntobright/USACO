/*
ID: suntobr1
LANG: C
TASK: stall4
*/

#include <stdio.h>

int map[402][402];
int cow_count;
int stall_count;
int max_match;

int min(int a, int b)
{
  return a < b ? a : b;
}

int main(void)
{
  FILE* fin = fopen("stall4.in", "rb");
  FILE* fout = fopen("stall4.out", "wb");

  int temp_stall_count;
  int temp_stall_number;
  int destination;

  int max_path[402];
  int pre_node[402];
  int used[402];

  int max_value;
  int max_pos;

  int i, j;

  fscanf(fin, "%d%d", &cow_count, &stall_count);
  for (i = 1; i <= cow_count; i ++)
  {
    map[0][i] = 1;
    fscanf(fin, "%d", &temp_stall_count);
    for (j = 0; j < temp_stall_count; j ++)
    {
      fscanf(fin, "%d", &temp_stall_number);
      map[i][cow_count + temp_stall_number] = 1;
    }
  }
  destination = cow_count + stall_count + 1;
  for (i = cow_count + 1; i < destination; i ++)
    map[i][destination] = 1;

  while (1)
  {
    max_path[0] = 0;
    pre_node[0] = -1;
    used[0] = 1;
    for (i = 1; i <= destination; i ++)
    {
      max_path[i] = map[0][i];
      pre_node[i] = 0;
      used[i] = 0;
    }

    while (1)
    {
      max_value = 0;
      max_pos = -1;
      for (i = 1; i <= destination; i ++)
        if (used[i] == 0 && max_value < max_path[i])
        {
          max_value = max_path[i];
          max_pos = i;
        }

      if (max_pos == -1 || max_pos == destination)
        break;

      used[max_pos] = 1;
      for (i = 1; i <= destination; i ++)
        if (used[i] == 0 && max_path[i] < min(max_value, map[max_pos][i]))
        {
          max_path[i] = min(max_value, map[max_pos][i]);
          pre_node[i] = max_pos;
        }
    }

    if (max_pos == -1)
      break;

    max_match += max_value;
    while (pre_node[max_pos] != -1)
    {
      map[pre_node[max_pos]][max_pos] -= max_value;
      map[max_pos][pre_node[max_pos]] += max_value;

      max_pos = pre_node[max_pos];
    }
  }

  fprintf(fout, "%d\n", max_match);

  fclose(fin);
  fclose(fout);

  return 0;
}
