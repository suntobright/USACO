/*
ID: suntobr1
LANG: C
TASK: clocks
*/

#include<stdio.h>

char turn[9][10] = {
  "ABDE",
  "ABC",
  "BCEF",
  "ADG",
  "BDEFH",
  "CFI",
  "DEGH",
  "GHI",
  "EFHI"
};

int trans(int begin, int kind, int count)
{
  int i, end;
  int clock[9];
  for(i = 9; i > 0; i --)
  {
    clock[i - 1] = begin % 4;
    begin /= 4;
  }
  for(i = 0; turn[kind][i] != '\0'; i ++)
  {
    clock[turn[kind][i] - 'A'] += count;
    clock[turn[kind][i] - 'A'] %= 4;
  }
  for(i = 0, end = 0; i < 9; i ++)
  {
    end *= 4;
    end += clock[i];
  }
  return end;
}

int main()
{
  FILE *fin, *fout;

  int begin, temp, move, tag;
  int i, j;

  fin = fopen("clocks.in", "r");
  fout = fopen("clocks.out", "w");

  for(i = 0, begin = 0; i < 9; i ++)
  {
    fscanf(fin, "%d", &temp);
    begin *= 4;
    begin += (temp / 3) % 4;
  }

  for(i = 0; i < 262144; i ++)
  {
    for(j = 0, temp = begin, move = i; j < 9; j ++)
    {
      temp = trans(temp, j, move % 4);
      move /= 4;
    }
    if(temp == 0)
      break;
  }

  move = i;
  tag = 0;
  for(i = 1; i <= 9; i ++)
  {
    for(j = 0; j < move % 4; j ++)
    {
      if(tag == 0)
      {
        fprintf(fout, "%d", i);
        tag ++;
      }
      else
        fprintf(fout, " %d", i);
    }
    move /= 4;
  }
  fprintf(fout, "\n");

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
