/*
ID: suntobr1
LANG: C
TASK: crypt1
*/

#include <stdio.h>

int num[10] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9};

int check(int ins)
{
  int count;
  for(count = 0; ins != 0; ins /= 10)
  {
    count += num[ins % 10];
  }
  return count;
}

int main()
{
  FILE *fin, *fout;

  int n, i, j, a, b, ins, count;

  fin = fopen("crypt1.in", "r");
  fout = fopen("crypt1.out", "w");

  fscanf(fin, "%d", &n);
  for(i = 0; i < n; i ++)
  {
    fscanf(fin, "%d", &j);
    num[j] = 1;
  }

  for(i = 100, count = 0; i < 1000; i ++)
  {
    if(check(i) == 3)
    {
      for(j = 10; j < 100; j ++)
      {
        if(check(j) == 2)
        {
          a = i * (j % 10);
          b = i * (j / 10);
          ins = a + b * 10;
          if(check(a) == 3 && check(b) == 3 && check(ins) == 4)
            count ++;
        }
      }
    }
  }

  fprintf(fout, "%d\n", count);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
