/*
ID: suntobr1
LANG: C
TASK: skidesign
*/

#include <stdio.h>

int count;
int hills[1000];

int main(void)
{
  FILE* fin = fopen("skidesign.in", "rb");
  FILE* fout = fopen("skidesign.out", "wb");

  int i;

  int height;
  int min_height;
  int max_height;
  int min_cost;
  int cost;

  fscanf(fin, "%d", &count);
  for (i = 0; i < count; i ++)
    fscanf(fin, "%d", &hills[i]);

  min_height = 100;
  max_height = 0;
  for (i = 0; i < count; i ++)
  {
    if (max_height < hills[i])
      max_height = hills[i];
    if (min_height > hills[i])
      min_height = hills[i];
  }

  min_cost = 10000000;
  for (height = min_height; height <= max_height - 17; height ++)
  {
    cost = 0;
    for (i = 0; i < count; i ++)
      if (hills[i] < height)
        cost += (height - hills[i]) * (height - hills[i]);
      else if (hills[i] > height + 17)
        cost += (hills[i] - height - 17) * (hills[i] - height - 17);

    if (min_cost > cost)
      min_cost = cost;
  }

  fprintf(fout, "%d\n", min_cost);

  fclose(fin);
  fclose(fout);

  return 0;
}
