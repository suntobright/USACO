/*
ID: suntobr1
LANG: C
TASK: friday
*/

#include <stdio.h>

int main(void)
{
  FILE* fin = fopen("friday.in", "rb");
  FILE* fout = fopen("friday.out", "wb");

  int n = 0;
  int weekDayCounts[7] = {0};

  int monthDayCounts[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
  };
  int pos = 0;

  int i = 0;
  int j = 0;

  fscanf(fin, "%d", &n);

  weekDayCounts[pos] ++;
  for (i = 0; i < n; i ++) {
    int year = 1900 + i;
    int isLeap = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
    for (j = 0; j < 12; j ++) {
      pos += monthDayCounts[isLeap][j];
      pos %= 7;
      weekDayCounts[pos] ++;
    }
  }
  weekDayCounts[pos] --;

  fprintf(fout, "%d", weekDayCounts[0]);
  for (i = 1; i < 7; i ++) {
    fprintf(fout, " %d", weekDayCounts[i]);
  }
  fprintf(fout, "\n");

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
