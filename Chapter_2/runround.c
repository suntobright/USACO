/*
ID: suntobr1
LANG: C
TASK: runround
*/

#include <stdio.h>

int main()
{
  FILE *fin, *fout;
  int m, temp, count, i;
  int num[10], query[10], check[10];

  fin = fopen("runround.in", "r");
  fout = fopen("runround.out", "w");

  fscanf(fin, "%d", &m);

  while(1)
  {
    m ++;
    temp = m;
    for(i = 0; i < 10; i ++)
    {
      query[i] = 0;
      check[i] = 0;
      num[i] = temp % 10;
      temp /= 10;
    }
    for(i = 9; i >= 0 && num[i] == 0; i --);
    count = i + 1;
    while(query[i] == 0 && check[num[i]] == 0)
    {
      query[i] = 1;
      check[num[i]] = 1;
      i -= num[i];
      while(i < 0)
        i += count;
    }
    if(count == i + 1)
    {
      for(i = 0; i < 10; i ++)
      {
        count -= query[i];
      }
    }
    if(count == 0)
    {
      fprintf(fout, "%d\n", m);
      break;
    }
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
