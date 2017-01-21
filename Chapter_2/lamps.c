/*
ID: suntobr1
LANG: C
TASK: lamps
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
  char *aa = (char *)a;
  char *bb = (char *)b;
  return strcmp(aa, bb);
}

int main()
{
  FILE *fin, *fout;

  int code[4][10] = {{0, -1}, {1, 2, 4, 6, -1}, {0, 2, 3, 4, 5, 6, 7, -1}, {0, 1, 2, 3, 4, 5, 6, 7, -1}};
  int para[3][2] = {0, 3, 1, 2, 0, 2};
  char lamp[7] = {0};
  char query[7] = {0};
  char record[7][7] = {0};

  int n, c, i, j, k, temp, count;

  fin = fopen("lamps.in", "r");
  fout = fopen("lamps.out", "w");

  fscanf(fin, "%d", &n);
  fscanf(fin, "%d", &c);

  while(1)
  {
    fscanf(fin, "%d", &temp);
    if(temp == -1)
      break;
    else
      query[(temp - 1) % 6] = '1';
  }
  while(1)
  {
    fscanf(fin, "%d", &temp);
    if(temp == -1)
      break;
    else
      query[(temp - 1) % 6] = '0';
  }
  c = (c < 3) ? c : 3;
  for(i = 0, count = 0; code[c][i] != -1; i ++)
  {
    for(j = 0; j < 6; j ++)
    {
      lamp[j] = '1';
    }
    for(j = 0, temp = code[c][i]; j < 3; j ++)
    {
      if(temp & 0x1)
      {
        for(k = para[j][0]; k < 6; k += para[j][1])
        {
          if(lamp[k] == '1')
            lamp[k] = '0';
          else
            lamp[k] = '1';
        }
      }
      temp = temp >> 1;
    }
    for(j = 0; j < 6; j ++)
    {
      if(query[j] != 0 && query[j] != lamp[j])
        break;
    }
    if(j == 6)
    {
      strcpy(record[count ++], lamp);
    }
  }
  qsort(record, count, sizeof(char) * 7, cmp);
  if(count == 0)
    fprintf(fout, "IMPOSSIBLE\n");
  else
  {
    for(i = 0; i < count; i ++)
    {
      for(j = 0; j < n; j ++)
      {
        fprintf(fout, "%c", record[i][j % 6]);
      }
      fprintf(fout, "\n");
    }
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
