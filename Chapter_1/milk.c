/*
ID: suntobr1
LANG: C
TASK: milk
*/

typedef struct
{
  int price;
  int amount;
} Farmer;

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
  return ((Farmer *)a) -> price - ((Farmer *)b) -> price;
}

int main()
{
  FILE *fin, *fout;

  int sum, n, ins, temp;
  Farmer farmer[5000];
  int i;

  fin = fopen("milk.in", "r");
  fout = fopen("milk.out", "w");

  fscanf(fin, "%d %d", &sum, &n);
  for(i = 0; i < n; i ++)
  {
    fscanf(fin, "%d %d", &farmer[i].price, &farmer[i].amount);
  }

  qsort(farmer, n, sizeof(Farmer), cmp);

  ins = 0;
  i = 0;
  while(sum)
  {
    temp = (sum < farmer[i].amount)? sum : farmer[i].amount;
    sum -= temp;
    ins += temp * farmer[i ++].price;
  }

  fprintf(fout, "%d\n", ins);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
