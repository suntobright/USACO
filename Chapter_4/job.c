/*
ID: suntobr1
LANG: C
TASK: job
*/

#include <stdio.h>
#include <stdlib.h>

int count;
int a_count;
int b_count;
int a[30];
int b[30];

int cmp(const void* a, const void* b)
{
  return *((const int*) a) - *((const int*) b);
}

int main(void)
{
  FILE* fin = fopen("job.in", "rb");
  FILE* fout = fopen("job.out", "wb");

  int a_time[1000];
  int a_delay[30] = {0};
  int a_max = 0;
  int b_time[1000];
  int b_delay[30] = {0};
  int b_max = 0;

  int i, j;
  int min_value;
  int min_index;

  fscanf(fin, "%d%d%d", &count, &a_count, &b_count);
  for (i = 0; i < a_count; i ++)
    fscanf(fin, "%d", &a[i]);
  for (i = 0; i < b_count; i ++)
    fscanf(fin, "%d", &b[i]);

  for (i = 0; i < count; i ++)
  {
    min_value = 20001;
    min_index = -1;
    for (j = 0; j < a_count; j ++)
    {
      if (a_max >= a_delay[j] + a[j])
      {
        a_delay[j] += a[j];
        a_time[i] = a_delay[j];
        break;
      }
      else if (min_value > a_delay[j] + a[j])
      {
        min_value = a_delay[j] + a[j];
        min_index = j;
      }
    }

    if (j == a_count)
    {
      a_max = min_value;
      a_delay[min_index] += a[min_index];
      a_time[i] = a_max;
    }
  }

  for (i = 0; i < count; i ++)
  {
    min_value = 20001;
    min_index = -1;
    for(j = 0; j < b_count; j ++)
    {
      if (b_max >= b_delay[j] + b[j])
      {
        b_delay[j] += b[j];
        b_time[i] = b_delay[j];
        break;
      }
      else if (min_value > b_delay[j] + b[j])
      {
        min_value = b_delay[j] + b[j];
        min_index = j;
      }
    }

    if (j == b_count)
    {
      b_max = min_value;
      b_delay[min_index] += b[min_index];
      b_time[i] = b_max;
    }
  }

  for (i = 0; i < count; i ++)
    if (b_max < a_time[i] + b_time[count - 1 - i])
      b_max = a_time[i] + b_time[count - 1 - i];

  fprintf(fout, "%d %d\n", a_max, b_max);

  fclose(fin);
  fclose(fout);

  return 0;
}
