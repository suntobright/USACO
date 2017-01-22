/*
ID: b8flowe1
LANG: C
TASK: ratios
*/

#include <stdio.h>

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int have[3][3];
  int goal[3];

  int count[3] = { 0 };

  int i, j, k, l, u;

  in = fopen("ratios.in", "rb");
  out = fopen("ratios.out", "wb");

  for (i = 0; i < 3; i++)
    fscanf(in, "%d", &goal[i]);
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      fscanf(in, "%d", &have[i][j]);

  for (i = 0; i < 100; i++)
  {
    for (j = 0; j < 100; j++)
    {
      for (k = 0; k < 100; k++)
      {
        if (i + j + k == 0)
          continue;

        for (l = 0; l < 3; l++)
          count[l] = 0;

        for (l = 0; l < 3; l++)
        {
          count[l] += have[0][l] * i;
          count[l] += have[1][l] * j;
          count[l] += have[2][l] * k;
        }

        if (count[0] % goal[0] == 0)
        {
          u = count[0] / goal[0];
          if (count[1] == goal[1] * u && count[2] == goal[2] * u)
            break;
        }
      }

      if (k < 100)
        break;
    }

    if (j < 100)
      break;
  }

  if (i < 100)
    fprintf(out, "%d %d %d %d\n", i, j, k, u);
  else
    fprintf(out, "NONE\n");

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
