/*
ID: suntobr1
LANG: C
TASK: spin
*/

#include <stdio.h>

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int count[5];
  int wedge[5][5][2];
  int speed[5];
  int have[5] = { 0 };

  int i, j, k;
  int n;
  int start, end;

  int wheel[360];
  int cur[360];

  in = fopen("spin.in", "rb");
  out = fopen("spin.out", "wb");

  for (i = 0; i < 5; i++)
  {
    fscanf(in, "%d%d", &speed[i], &count[i]);
    for (j = 0; j < count[i]; j++)
      fscanf(in, "%d%d", &wedge[i][j][0], &wedge[i][j][1]);
  }

  for (i = 0; i < 5; i++)
    have[i] -= speed[i];

  for (n = 0; n < 360; n++)
  {
    for (i = 0; i < 5; i++)
      have[i] = (have[i] + speed[i]) % 360;

    for (i = 0; i < 360; i++)
      wheel[i] = 1;

    for (i = 0; i < 5; i++)
    {
      for (j = 0; j < 360; j++)
        cur[j] = 0;

      for (j = 0; j < count[i]; j++)
        for (k = 0; k <= wedge[i][j][1]; k++)
          cur[(have[i] + wedge[i][j][0] + k) % 360] = 1;

      for (j = 0; j < 360; j++)
        wheel[j] &= cur[j];
    }

    for (i = 0; i < 360; i++)
      if (wheel[i] == 1)
        break;

    if (i < 360)
      break;
  }

  if (n == 360)
    fprintf(out, "none\n");
  else
    fprintf(out, "%d\n", n);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
