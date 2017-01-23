/*
ID: suntobr1
LANG: C
TASK: cowtour
*/

#include <stdio.h>
#include <math.h>

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int n;
  int position[160][2];
  double path[160][160] = { 0 };
  double max;
  double min;

  int i, j, k;
  char temp[160];
  double temp1, temp2, temp3;

  in = fopen("cowtour.in", "rb");
  out = fopen("cowtour.out", "wb");

  fscanf(in, "%d", &n);
  for (i = 0; i < n; i++)
    fscanf(in, "%d%d", &position[i][0], &position[i][1]);
  for (i = 0; i < n; i++)
  {
    fscanf(in, "%s", temp);
    for (j = i + 1; j < n; j++)
      if (temp[j] == '1')
        path[i][j] = path[j][i] = sqrt(pow((double)(position[i][0] - position[j][0]), 2) + pow((double)(position[i][1] - position[j][1]), 2));
      else
        path[i][j] = path[j][i] = 1e101;
  }

  for (k = 0; k < n; k++)
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
        if (path[i][j] > path[i][k] + path[k][j])
          path[i][j] = path[i][k] + path[k][j];

  max = 0;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (path[i][j] < 1e100 && max < path[i][j])
        max = path[i][j];

  min = 1e101;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j ++)
      if (path[i][j] > 1e100)
      {
        temp1 = 0;
        for (k = 0; k < n; k++)
          if (path[i][k] < 1e100 && temp1 < path[i][k])
            temp1 = path[i][k];

        temp2 = 0;
        for (k = 0; k < n; k++)
          if (path[k][j] < 1e100 && temp2 < path[k][j])
            temp2 = path[k][j];

        temp3 = sqrt(pow((double)(position[i][0] - position[j][0]), 2) + pow((double)(position[i][1] - position[j][1]), 2));

        if (min > temp1 + temp2 + temp3)
          min = temp1 + temp2 + temp3;
      }

  max = max > min ? max : min;
  fprintf(out, "%.6lf\n", max);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
