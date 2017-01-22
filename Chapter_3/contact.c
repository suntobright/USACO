/*
ID: suntobr1
LANG: C
TASK: contact
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
  int count;
  char string[16];
} Record;

int counts[12][4096];
char string[200704];
Record record[8192];
int count;

int cmp(const void *a, const void *b)
{
  Record *x = (Record *)a;
  Record *y = (Record *)b;

  if (x->count != y->count)
    return y->count - x->count;
  else if (strlen(x->string) != strlen(y->string))
    return strlen(x->string) - strlen(y->string);
  else
    return strcmp(x->string, y->string);
}

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int a, b, n;

  int i, j, k;
  char temp[96];
  int len;
  int num;
  int toread;

  in = fopen("contact.in", "rb");
  out = fopen("contact.out", "wb");

  fscanf(in, "%d%d%d", &a, &b, &n);
  while (fscanf(in, "%s", temp) != EOF)
    strcat(string, temp);

  len = strlen(string);
  for (i = 0; i < len; i++)
  {
    num = 0;
    for (j = 0; j < b && i + j < len; j++)
    {
      num *= 2;
      num += string[i + j] - '0';

      counts[j][num] ++;
    }
  }

  toread = 1;
  k = 0;
  for (i = 0; i < a - 1; i++)
    toread *= 2;
  for (; i < b; i++)
  {
    toread *= 2;
    for (j = 0; j < toread; j++)
    {
      num = j;
      temp[i + 1] = '\0';
      for (k = i; k >= 0; k--)
      {
        temp[k] = num % 2 + '0';
        num /= 2;
      }

      record[count].count = counts[i][j];
      strcpy(record[count].string, temp);
      count++;
    }
  }

  qsort(record, count, sizeof(Record), cmp);

  j = -1;
  toread = 0;
  for (i = 0; i < count && record[i].count != 0; i++)
  {
    if (j == -1 || record[i].count != record[j].count)
    {
      toread++;
      if (toread > n)
        break;

      if ((k + 1) % 6 != 0)
        fprintf(out, "\n");

      fprintf(out, "%d\n", record[i].count);
      fprintf(out, "%s", record[i].string);
      j = i;
      k = 0;
    }
    else
    {
      if ((k + 1) % 6 != 0)
        fprintf(out, " ");
      fprintf(out, "%s", record[i].string);
      k++;
      if ((k + 1) % 6 == 0)
        fprintf(out, "\n");
    }
  }
  if ((k + 1) % 6 != 0)
    fprintf(out, "\n");

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
