/*
ID: suntobr1
LANG: C
TASK: pprime
*/

#include <stdio.h>
#include <math.h>

int main()
{
  FILE *fin, *fout;
  int begin, end;
  int array[1000] = {5, 7, 11, 0};
  int count;
  int num[7];
  int pos, max, temp;
  int i, j;

  fin = fopen("pprime.in", "r");
  fout = fopen("pprime.out", "w");

  fscanf(fin, "%d %d", &begin, &end);

  for(i = 10, count = 3; i < 9999; i ++)
  {
    for(temp = i, pos = 4; temp != 0; temp /= 10)
      num[-- pos] = temp % 10;
    if(num[pos] % 2 == 0 || num[pos] == 5)
    {
      for(j = pos, temp = 1; j < 3; j ++)
        temp *= 10;
      i += temp - 1;
      continue;
    }
    for(j = pos; j < 3; j ++)
      num[6 - j] = num[j];
    for(j = pos, max = 7 - pos, temp = 0; j < max; j ++)
    {
      temp *= 10;
      temp += num[j];
    }
    for(j = 2, max = (int)sqrt(temp); j <= max && temp % j != 0; j ++);
    if(j > max)
      array[count ++] = temp;
  }

  for(i = 0; i < count && array[i] < begin; i ++);
  for(; i < count && array[i] <= end; i ++)
    fprintf(fout, "%d\n", array[i]);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
