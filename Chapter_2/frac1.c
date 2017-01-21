/*
ID: suntobr1
LANG: C
TASK: frac1
*/

typedef struct
{
  int x, y;
} Frac;

#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b)
{
  if(a == 0)
    return b;
  else
    return gcd(b % a, a);
}

int cmp(const void *a, const void *b)
{
  Frac p, q;

  p = *((Frac *)a);
  q = *((Frac *)b);

  return p.x * q.y - p.y * q.x;
}

int main()
{
  FILE *fin, *fout;
  int n, i, j, count;
  Frac frac[8000] = {{0, 1}, {1, 1}};

  fin = fopen("frac1.in", "r");
  fout = fopen("frac1.out", "w");

  fscanf(fin, "%d", &n);

  count = 2;
  for(i = 1; i <= n; i ++)
  {
    for(j = i + 1; j <= n; j ++)
    {
      if(gcd(i, j) == 1)
      {
        frac[count].x = i;
        frac[count].y = j;
        count ++;
      }
    }
  }

  qsort(frac, count, sizeof(Frac), cmp);

  for(i = 0; i < count; i ++)
  {
    fprintf(fout, "%d/%d\n", frac[i].x, frac[i].y);
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
