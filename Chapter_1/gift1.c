/*
ID: suntobr1
LANG: C
TASK: gift1
*/

#include <stdio.h>
#include <string.h>

typedef struct
{
  char name[15];
  int change;
} Giver;

int main()
{
  FILE *fin, *fout;
  Giver giver[10];
  char name[15];
  int money;
  int n, m;
  int i, j;

  fin = fopen("gift1.in", "r");
  fout = fopen("gift1.out", "w");

  fscanf(fin, "%d", &n);
  for(i = 0; i < n; i ++)
  {
    fscanf(fin, "%s", giver[i].name);
    giver[i].change = 0;
  }
  while(fscanf(fin, "%s", name) != EOF)
  {
    for(i = 0; i < n; i ++)
    {
      if(strcmp(name, giver[i].name) == 0)
        break;
    }
    fscanf(fin, "%d %d", &money, &m);
    if(m != 0 && money != 0)
    {
      money /= m;
      giver[i].change -= money * m;
      for(i = 0; i < m; i ++)
      {
        fscanf(fin, "%s", name);
        for(j = 0; j < n; j ++)
        {
          if(strcmp(name, giver[j].name) == 0)
            break;
        }
        giver[j].change += money;
      }
    }
  }
  for(i = 0; i < n; i ++)
  {
    fprintf(fout, "%s %d\n", giver[i].name, giver[i].change);
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
