/*
ID: suntobr1
LANG: C
TASK: checker
*/

#include<stdio.h>

int array[13][13];
int record[3][13];
int stack[13];
int count;

void place(int x, int y, int n, int type)
{
  int i, a, b;
  for(i = x + 1, a = y - 1, b = y + 1; i < n; i ++)
  {
    array[i][y] += type;
    if(a >= 0)
      array[i][a --] += type;
    if(b < n)
      array[i][b ++] += type;
  }
}

int search(int step, int n)
{
  int sum, i;
  if(step == n)
  {
    if(count != 3)
    {
      for(i = 0; i < n; i ++)
        record[count][i] = stack[i];
      count ++;
    }
    sum = 1;
  }
  else
  {
    sum = 0;
    for(i = 0; i < n; i ++)
    {
      if(array[step][i] == 0)
      {
        stack[step] = i + 1;
        place(step, i, n, 1);
        sum += search(step + 1, n);
        place(step, i, n, -1);
      }
    }
  }
  return sum;
}

int main()
{
  FILE *fin, *fout;
  int n, sum, i, j;

  fin = fopen("checker.in", "r");
  fout = fopen("checker.out", "w");

  fscanf(fin, "%d", &n);

  sum = search(0, n);

  for(i = 0; i < count; i ++)
  {
    fprintf(fout, "%d", record[i][0]);
    for(j = 1; j < n; j ++)
      fprintf(fout, " %d", record[i][j]);
    fprintf(fout, "\n");
  }
  fprintf(fout, "%d\n", sum);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
