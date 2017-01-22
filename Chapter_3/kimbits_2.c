/*
ID: b8flowe1
LANG: C
TASK: kimbits
*/

#include <stdio.h>

long long int cpick(int k, int n)
{
  long long int result = 1;
  int i;

  for (i = 0; i < k; i++)
  {
    result *= n - i;
    result /= i + 1;
  }

  return result;
}

long long int getsize(int n, int m)
{
  long long int result = 0;
  int i;

  for (i = 0; i <= m; i++)
    result += cpick(i, n);

  return result;
}

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int n, l;
  long long int no;

  int i;
  long long int size;
  int have;

  in = fopen("kimbits.in", "rb");
  out = fopen("kimbits.out", "wb");

  fscanf(in, "%d%d%lld", &n, &l, &no);

  have = 0;
  for (i = 0; i < n; i++)
  {
    size = getsize(n - i - 1, l - have);

    if (no > size)
    {
      fprintf(out, "1");
      have++;
      no -= size;
    }
    else
      fprintf(out, "0");
  }

  fprintf(out, "\n");

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
