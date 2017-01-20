/*
ID: suntobr1
LANG: C
TASK: dualpal
*/

#include <stdio.h>
#include <string.h>

char map[] = "0123456789";

void trans(char numb[], int num, int base)
{
  int i;
  i = 0;
  do
  {
    numb[i ++] = map[num % base];
    num /= base;
  }while(num != 0);
  numb[i] = '\0';
}

int check(char numb[])
{
  int mid, len, i;
  len = strlen(numb);
  mid = len / 2;
  for(i = 0; i < mid && numb[i] == numb[len - i - 1]; i ++);
  if(i == mid)
    return 1;
  else
    return 0;
}

int main()
{
  FILE *fin, *fout;

  int n, s, sum;
  char si[35];
  int i;

  fin = fopen("dualpal.in", "r");
  fout = fopen("dualpal.out", "w");

  fscanf(fin, "%d %d", &n, &s);

  s ++;
  while(n)
  {
    for(i = 2, sum = 0; i <= 10 && sum < 2; i ++)
    {
      trans(si, s, i);
      sum += check(si);
    }
    if(sum == 2)
    {
      fprintf(fout, "%d\n", s);
      n --;
    }
    s ++;
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
