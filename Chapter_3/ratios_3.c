/*
ID: b8flowe1
LANG: C
TASK: ratios
*/

#include <stdio.h>

int det(int a[][3])
{
  int result = 0;

  result += a[0][0] * (a[1][1] * a[2][2] - a[2][1] * a[1][2]);
  result -= a[0][1] * (a[1][0] * a[2][2] - a[1][2] * a[2][0]);
  result += a[0][2] * (a[1][0] * a[2][1] - a[1][1] * a[2][0]);

  return result;
}

int gcd(int a, int b)
{
  return b == 0 ? a : gcd(b, a % b);
}

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int have[3][3];
  int goal[3];

  int i, j;
  int x[3];
  int  z;
  int temp;

  in = fopen("ratios.in", "rb");
  out = fopen("ratios.out", "wb");

  for (i = 0; i < 3; i++)
    fscanf(in, "%d", &goal[i]);
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      fscanf(in, "%d", &have[j][i]);

  z = det(have);
  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 3; j++)
    {
      temp = have[j][i];
      have[j][i] = goal[j];
      goal[j] = temp;
    }

    x[i] = det(have);

    for (j = 0; j < 3; j++)
    {
      temp = have[j][i];
      have[j][i] = goal[j];
      goal[j] = temp;
    }
  }

  temp = z;
  for (i = 0; i < 3; i++)
    temp = temp > x[i] ? gcd(temp, x[i]) : gcd(x[i], temp);

  z /= temp;
  for (i = 0; i < 3; i++)
    x[i] /= temp;

  for (i = 0; i < 3; i++)
    if (x[i] < 0 || x[i] >= 100)
      break;

  if (i == 3 && z > 0 && z < 100)
  {
    for (i = 0; i < 3; i++)
      fprintf(out, "%d ", x[i]);
    fprintf(out, "%d\n", z);
  }
  else
    fprintf(out, "NONE\n");

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
