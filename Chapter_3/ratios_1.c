/*
ID: b8flowe1
LANG: C
TASK: ratios
*/

#include <stdio.h>

typedef struct
{
  int numerator;
  int denominator;
} Fraction;

int gcd_in(int a, int b)
{
  return b > 0 ? gcd_in(b, a % b) : a;
}

int gcd(int a, int b)
{
  if (a < 0)
    a = -a;
  if (b < 0)
    b = -b;
  if (a > b)
    return gcd_in(a, b);
  else
    return gcd_in(b, a);
}

Fraction div(Fraction a, Fraction b)
{
  Fraction result;
  int factor;

  result.numerator = a.numerator * b.denominator;
  result.denominator = a.denominator * b.numerator;

  if (result.denominator < 0)
  {
    result.numerator *= -1;
    result.denominator *= -1;
  }

  factor = gcd(result.numerator, result.denominator);

  result.numerator /= factor;
  result.denominator /= factor;

  return result;
}

Fraction sub(Fraction a, Fraction b)
{
  Fraction result;
  int factor;

  result.numerator = a.numerator * b.denominator - a.denominator * b.numerator;
  result.denominator = a.denominator * b.denominator;

  if (result.numerator != 0)
  {
    factor = gcd(result.numerator, result.denominator);

    result.numerator /= factor;
    result.denominator /= factor;
  }
  else
    result.denominator = 1;

  return result;
}

Fraction mul(Fraction a, Fraction b)
{
  Fraction result;

  result.numerator = a.numerator * b.numerator;
  result.denominator = a.denominator * b.denominator;

  if (result.numerator == 0)
    result.denominator = 1;

  return result;
}

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  Fraction fraction[3][4];

  int i, j, k;
  int u, x, y, z;

  in = fopen("ratios.in", "rb");
  out = fopen("ratios.out", "wb");

  for (j = 0; j < 4; j++)
    for (i = 0; i < 3; i++)
    {
      fscanf(in, "%d", &fraction[i][(j + 3) % 4].numerator);
      fraction[i][(j + 3) % 4].denominator = 1;
    }

  for (i = 0; i < 3; i++)
    if (fraction[i][i].numerator != 0)
    {
      for (j = 3; j >= i; j--)
        fraction[i][j] = div(fraction[i][j], fraction[i][i]);
      for (j = i + 1; j < 3; j++)
        for (k = 3; k >= i; k--)
          fraction[j][k] = sub(fraction[j][k], mul(fraction[i][k], fraction[j][i]));
    }

  for (i = 2; i > 0; i--)
    for (j = 0; j < i; j++)
      for (k = 3; k >= i; k--)
        fraction[j][k] = sub(fraction[j][k], mul(fraction[i][k], fraction[j][i]));

  u = fraction[0][3].denominator * fraction[1][3].denominator / gcd(fraction[0][3].denominator, fraction[1][3].denominator);
  u = u * fraction[2][3].denominator / gcd(u, fraction[2][3].denominator);

  x = fraction[0][3].numerator * u / fraction[0][3].denominator;
  y = fraction[1][3].numerator * u / fraction[1][3].denominator;
  z = fraction[2][3].numerator * u / fraction[2][3].denominator;

  if (x >= 0 && x < 100 && y >= 0 && y < 100 && z >= 0 && z < 100)
    fprintf(out, "%d %d %d %d\n", x, y, z, u);
  else
    fprintf(out, "NONE\n");

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
