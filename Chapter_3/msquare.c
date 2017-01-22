/*
ID: suntobr1
LANG: C
TASK: msquare
*/

#include <stdio.h>

const int table[8] = { 5040, 720, 120, 24, 6, 2, 1, 1 };
const int trans[3][8] =
{
  {7, 6, 5, 4, 3, 2, 1, 0},
  {3, 0, 1, 2, 5, 6, 7, 4},
  {0, 6, 1, 3, 4, 2, 5, 7}
};

int list[40960] = { 0 };
int begin = 0;
int end = 0;
char kind[40960] = { 0 };
int from[40960] = { 0 };

char path[40960] = { 0 };
int count;

int hash(int square[])
{
  int i, j;

  int hash;
  int count;
  int use[12] = { 0 };

  hash = 0;
  for (i = 0; i < 8; i++)
  {
    count = 0;
    for (j = 1; j < square[i]; j++)
      if (use[j] == 0)
        count++;

    hash += count * table[i];

    use[j] = 1;
  }

  return hash;
}

void rehash(int square[], int hash)
{
  int i, j;

  int count;
  int use[12] = { 0 };

  for (i = 0; i < 8; i++)
  {
    count = hash / table[i];
    hash %= table[i];

    j = 0;
    do
    {
      for (j ++; use[j] == 1; j++);
      count--;
    } while (count >= 0);

    square[i] = j;

    use[j] = 1;
  }
}

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int square[8];
  int temp[8];
  int target;
  int cur;
  int next;

  int i, j;

  in = fopen("msquare.in", "rb");
  out = fopen("msquare.out", "wb");

  for (i = 0; i < 8; i++)
    fscanf(in, "%d", &square[i]);

  target = hash(square);

  for (i = 1; i < 40960; i++)
    from[i] = -1;

  list[begin++] = 0;
  while (begin != end)
  {
    cur = list[end++];
    rehash(square, cur);

    for (i = 0; i < 3; i++)
    {
      for (j = 0; j < 8; j++)
        temp[j] = square[trans[i][j]];

      next = hash(temp);

      if (from[next] == -1)
      {
        from[next] = cur;
        kind[next] = 'A' + i;

        list[begin++] = next;
      }
      if (next == target)
        break;
    }

    if (next == target)
      break;
  }

  while (next != 0)
  {
    path[count++] = kind[next];
    next = from[next];
  }

  fprintf(out, "%d\n", count);
  for (i = count - 1; i >= 0; i--)
    fprintf(out, "%c", path[i]);
  fprintf(out, "\n");

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
