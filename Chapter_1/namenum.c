/*
ID: suntobr1
LANG: C
TASK: namenum
*/

typedef struct
{
  char name[15];
  char num[15];
} Item;

#include <stdio.h>
#include <string.h>

char map[] = "22233344455566670778889990";
Item dict[5000];

void trans(char num[], char name[])
{
  int i;
  for(i = 0; name[i] != '\0'; i ++)
    num[i] = map[name[i] - 'A'];
  num[i] = '\0';
}

int main()
{
  FILE *fin, *fout, *fdict;

  int n, flag;
  char index[15];
  int i;

  fin = fopen("namenum.in", "r");
  fout = fopen("namenum.out", "w");
  fdict = fopen("dict.txt", "r");

  n = 0;
  while(fscanf(fdict, "%s", dict[n].name) != EOF)
  {
    trans(dict[n].num, dict[n].name);
    n ++;
  }
  fclose(fdict);

  fscanf(fin, "%s", index);

  flag = 0;
  for(i = 0; i < n; i ++)
  {
    if(strcmp(index, dict[i].num) == 0)
    {
      flag = 1;
      fprintf(fout, "%s\n", dict[i].name);
    }
  }
  if(flag == 0)
    fprintf(fout, "NONE\n");

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
