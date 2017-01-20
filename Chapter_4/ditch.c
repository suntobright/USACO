/*
ID: b8flowe1
LANG: C
TASK: ditch
*/
#include <stdio.h>

int ditch_count;
int point_count;
int capacity[200][200];
int max_rate;

int min(int a, int b)
{
  return a < b ? a : b;
}

int main(void)
{
  FILE* fin = fopen("ditch.in", "rb");
  FILE* fout = fopen("ditch.out", "wb");

  int i;
  int a, b;
  int temp;

  int max_capacity[200];
  int pre_point[200];
  int used[200];
  int max_value;
  int max_index;

  fscanf(fin, "%d%d", &ditch_count, &point_count);
  for (i = 0; i < ditch_count; i ++)
  {
    fscanf(fin, "%d%d%d", &a, &b, &temp);
    a --;
    b --;
    capacity[a][b] += temp;
  }

  while (1)
  {
    max_capacity[0] = 0;
    pre_point[0] = -1;
    used[0] = 1;
    for (i = 1; i < point_count; i ++)
    {
      max_capacity[i] = capacity[0][i];
      pre_point[i] = 0;
      used[i] = 0;
    }

    while (1)
    {
      max_value = 0;
      max_index = -1;
      for (i = 1; i < point_count; i ++)
        if (used[i] == 0 && max_value < max_capacity[i])
        {
          max_value = max_capacity[i];
          max_index = i;
        }

      if (max_index == -1 || max_index == point_count - 1)
        break;

      used[max_index] = 1;
      for (i = 1; i < point_count; i ++)
        if (used[i] == 0 && max_capacity[i] < min(max_value, capacity[max_index][i]))
        {
          max_capacity[i] = min(max_value, capacity[max_index][i]);
          pre_point[i] = max_index;
        }
    }

    if (max_index == -1)
      break;

    max_rate += max_value;
    while (pre_point[max_index] != -1)
    {
      capacity[pre_point[max_index]][max_index] -= max_value;
      capacity[max_index][pre_point[max_index]] += max_value;

      max_index = pre_point[max_index];
    }
  }

  fprintf(fout, "%d\n", max_rate);

  fclose(fin);
  fclose(fout);

  return 0;
}
