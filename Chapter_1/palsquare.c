/*
ID: suntobr1
LANG: C
TASK: palsquare
*/

#include <stdio.h>
#include <string.h>

char map[] = "0123456789ABCDEFGHIJ";

void trans(char squareb[], int square, int base)
{
  int i;
  i = 0;
  do
  {
    squareb[i ++] = map[square % base];
    square /= base;
  }while(square != 0);
  squareb[i] = '\0';
}

int check(char squareb[])
{
  int mid, len, i;
  len = strlen(squareb);
  mid = len / 2;
  for(i = 0; i < mid && squareb[i] == squareb[len - i - 1]; i ++);
  if(i == mid)
    return 1;
  else
    return 0;
}

void reverse(char numb[])
{
  char temp[20];
  int i, len;
  strcpy(temp, numb);
  len = strlen(numb);
  for(i = 0; i < len; i ++)
    numb[i] = temp[len - i - 1];
}

int main()
{
  FILE *fin, *fout;

  int base;
  int square, num;
  char squareb[20], numb[20];

  fin = fopen("palsquare.in", "r");
  fout = fopen("palsquare.out", "w");

  fscanf(fin, "%d", &base);

  for(num = 1; num <= 300; num ++)
  {
    square = num * num;
    trans(squareb, square, base);
    if(check(squareb) == 1)
    {
      trans(numb, num, base);
      reverse(numb);
      fprintf(fout, "%s %s\n", numb, squareb);
    }
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
