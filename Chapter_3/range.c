/*
ID: suntobr1
LANG: C
TASK: range
*/

#include <stdio.h>

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int n;
  int map[256][256];
  int count[256] = { 0 };
  int size;
  char temp[256];
  int i, j;

  in = fopen("range.in", "rb");
  out = fopen("range.out", "wb");

  fscanf(in, "%d", &n);
  for (i = 0; i < n; i++)
  {
    fscanf(in, "%s", temp);
    for (j = 0; j < n; j++)
      map[i][j] = temp[j] - '0';
  }

  for (size = 1; size < n; size++)
    for (i = 0; i < n - size; i++)
      for (j = 0; j < n - size; j++)
        if (map[i][j] + map[i][j + 1] + map[i + 1][j] + map[i + 1][j + 1] == size * 4)
        {
          map[i][j] ++;
          count[size + 1] ++;
        }

  for (size = 2; count[size] != 0; size++)
    fprintf(out, "%d %d\n", size, count[size]);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
