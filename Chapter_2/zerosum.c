/*
ID: suntobr1
LANG: C
TASK: zerosum
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b)
{
  char *x = (char *)a;
  char *y = (char *)b;
  return strcmp(a, b);
}

int main()
{
  FILE *fin, *fout;

  int array[20] = {0};
  int back[20] = {0};
  char record[100][20] = {0};
  char table[4] = " +-";
  int n, m, i, j, k, temp, count;

  fin = fopen("zerosum.in", "r");
  fout = fopen("zerosum.out", "w");

  fscanf(fin, "%d", &n);

  for(m = 1, i = 1; i < n; i ++)
  {
    m *= 3;
  }
  for(count = 0, i = 0; i < m; i ++)
  {
    temp = i;
    for(j = 0; j < n; j ++)
    {
      array[j * 2] = j + 1;
      array[j * 2 + 1] = temp % 3;
      temp /= 3;
    }
    for(j = 0; j < n * 2 - 1; j ++)
    {
      back[j] = array[j];
    }
    for(j = 1, k = 0; j < n * 2 - 1; j += 2)
    {
      if(array[j] == 0)
      {
        array[k] = array[k] * 10 + array[j + 1];
      }
      else
      {
        array[++ k] = array[j];
        array[++ k] = array[j + 1];
      }
    }
    for(temp = array[0], j = 1; j < k; j += 2)
    {
      if(array[j] == 1)
      {
        temp += array[j + 1];
      }
      else
      {
        temp -= array[j + 1];
      }
    }
    if(temp == 0)
    {
      for(j = 0; j < n; j ++)
      {
        record[count][j * 2] = (char)(back[j * 2] + '0');
        record[count][j * 2 + 1] = table[back[j * 2 + 1]];
      }
      record[count][j * 2 - 1] = '\0';
      count ++;
    }
  }

  qsort(record, count, sizeof(char) * 20, cmp);

  for(i = 0; i < count; i ++)
  {
    fprintf(fout, "%s\n", record[i]);
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
