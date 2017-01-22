/*
ID: suntobr1
LANG: C
TASK: kimbits
*/

#include <stdio.h>

void getstring(char temp[], int n, unsigned int num)
{
  int i;
  temp[n] = '\0';
  for (i = n - 1; i >= 0; i--)
  {
    temp[i] = num % 2 + '0';
    num /= 2;
  }
}

long long int c(int k, int n)
{
  int i;
  long long int result = 1;

  for (i = 0; i < k; i++)
  {
    result *= n - i;
    result /= i + 1;
  }

  return result;
}

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int n, l;
  unsigned int no;
  char temp[48];
  long long int count;
  int have;

  int i, j;

  in = fopen("kimbits.in", "rb");
  out = fopen("kimbits.out", "wb");

  fscanf(in, "%d%d%u", &n, &l, &no);
  n++;

  getstring(temp, n, no);

  count = 0;
  have = 0;
  for (i = 0; i < n; i++)
  {
    if (temp[i] == '1')
    {
      for (j = l + 1 - have; j < n - i; j++)
        count += c(j, n - i - 1);
      have++;
    }
  }

  getstring(temp, n, no - 1);
  while (count != 0)
  {
    getstring(temp, n, no);

    have = 0;
    for (i = 0; i < n; i++)
      if (temp[i] == '1')
        have++;

    if (have <= l)
      count--;

    no++;
  }

  fprintf(out, "%s\n", &temp[1]);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
