/*
ID: suntobr1
LANG: C
TASK: ariprog
*/

typedef struct
{
  int a, b;
} Record;

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
  Record *va = (Record *)a;
  Record *vb = (Record *)b;
  if(va -> b == vb -> b)
    return va -> a - vb -> a;
  else
    return va -> b - vb -> b;
}

int main()
{
  FILE *fin, *fout;

  int query[125001] = {0};
  int array[21100];
  Record record[10000];
  int n, m, a, b, p, q, count, max;
  int i, j, k;

  fin = fopen("ariprog.in", "r");
  fout = fopen("ariprog.out", "w");

  fscanf(fin, "%d", &n);
  fscanf(fin, "%d", &m);

  for(p = 0; p <= m; p ++)
  {
    for(q = p; q <= m; q ++)
    {
      query[p * p + q * q] = 1;
    }
  }

  count = 0;
  max = m * m * 2 + 1;
  for(i = 0; i < max; i ++)
  {
    if(query[i] == 1)
      array[count ++] = i;
  }

  max = 0;
  for(i = 0; i < count; i ++)
  {
    a = array[i];
    for(j = i + 1; j < count; j ++)
    {
      b = array[j] - array[i];
      for(k = 2, p = array[j]; k < n; k ++)
      {
        p += b;
        if(p > 125000 || query[p] == 0)
          break;
      }
      if(k == n)
      {
        record[max].a = a;
        record[max].b = b;
        max ++;
      }
    }
  }

  qsort(record, max, sizeof(Record), cmp);

  if(max == 0)
    fprintf(fout, "NONE\n");
  for(i = 0; i < max; i ++)
    fprintf(fout, "%d %d\n", record[i].a, record[i].b);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
