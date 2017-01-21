/*
ID: suntobr1
LANG: C
TASK: milk3
*/

typedef struct
{
  int has;
  int full;
} Bottle;

#include <stdio.h>
#include <stdlib.h>

Bottle bottle[3];
int query[9300];
int record[21];
int count;

int cmp(const void *a, const void *b)
{
  return *((int *)a) - *((int *)b);
}

int hash()
{
  int sum, i;
  for(i = 0, sum = 0; i < 3; i ++)
  {
    sum *= 21;
    sum += bottle[i].has;
  }
  return sum;
}

int perform(int send, int recv, int size)
{
  int temp;
  if(size == -1)
  {
    temp = bottle[recv].full - bottle[recv].has;
    size = bottle[send].has < temp ? bottle[send].has : temp;
  }
  bottle[send].has -= size;
  bottle[recv].has += size;
  return size;
}

void search(int state)
{
  int i, j, size;
  if(query[state] == 0)
  {
    query[state] = 1;
    if(bottle[0].has == 0)
      record[count ++] = bottle[2].has;
    for(i = 0; i < 3; i ++)
    {
      for(j = 0; j < 3; j ++)
      {
        if(i != j)
        {
          size = perform(i, j, -1);
          search(hash());
          perform(j, i, size);
        }
      }
    }
  }
}

int main()
{
  FILE *fin, *fout;
  int i, flag;

  fin = fopen("milk3.in", "r");
  fout = fopen("milk3.out", "w");

  for(i = 0; i < 3; i ++)
  {
    fscanf(fin, "%d", &bottle[i].full);
  }
  bottle[2].has = bottle[2].full;

  search(hash());

  qsort(record, count, sizeof(int), cmp);

  for(i = 0, flag = 0; i < count; i ++)
  {
    if(flag == 0)
    {
      fprintf(fout, "%d", record[i]);
      flag ++;
    }
    else
      fprintf(fout, " %d", record[i]);
  }
  fprintf(fout, "\n");

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
