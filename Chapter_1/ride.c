/*
ID: suntobr1
LANG: C
TASK: ride
*/

#include <stdio.h>

int main()
{
  FILE *fin, *fout;
  char comet[10], group[10];
  int a, b;
  int i;

  fin = fopen("ride.in", "r");
  fout = fopen("ride.out", "w");

  fscanf(fin, "%s", comet);
  fscanf(fin, "%s", group);

  for(i = 0, a = 1; comet[i] != '\0'; i ++)
  {
    a *= comet[i] - 'A' + 1;
    a %= 47;
  }

  for(i = 0, b = 1; group[i] != '\0'; i ++)
  {
    b *= group[i] - 'A' + 1;
    b %= 47;
  }

  if(a == b)
    fprintf(fout, "GO\n");
  else
    fprintf(fout, "STAY\n");

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
