/*
ID: suntobr1
LANG: C
TASK: transform
*/

#include <stdio.h>
#include <string.h>

void trans1(int n, char before[][11], char temp[][11])
{
  int i, j;
  for(i = 0; i < n; i ++)
  {
    for(j = 0; j < n; j ++)
    {
      temp[j][n - i - 1] = before[i][j];
    }
  }
}

int trans2(int n, char before[][11], char temp[][11])
{
  int i, j;
  for(i = 0; i < n; i ++)
  {
    for(j = 0; j < n; j ++)
    {
      temp[i][n -j -1] = before[i][j];
    }
  }
}

int equal(int n, char after[][11], char temp[][11])
{
  int flag;
  int i;
  for(i = 0, flag = 0; i < n && flag == 0; i ++)
  {
    flag = strcmp(after[i], temp[i]);
  }
  return flag;
}

int main()
{
  FILE *fin, *fout;

  int n;
  char before[10][11] = {0};
  char after[10][11] = {0};
  char temp1[10][11] = {0};
  char temp2[10][11] = {0};
  int i, j;

  fin = fopen("transform.in", "r");
  fout = fopen("transform.out", "w");

  fscanf(fin, "%d", &n);
  for(i = 0; i < n; i ++)
  {
    fscanf(fin, "%s", before[i]);
  }
  for(i = 0; i < n; i ++)
  {
    fscanf(fin, "%s", after[i]);
  }

  trans1(n, before, temp1);
  if(equal(n, after, temp1) == 0)
    fprintf(fout, "1\n");
  else
  {
    trans1(n, temp1, temp2);
    if(equal(n, after, temp2) == 0)
      fprintf(fout, "2\n");
    else
    {
      trans1(n, temp2, temp1);
      if(equal(n, after, temp1) == 0)
        fprintf(fout, "3\n");
      else
      {
        trans2(n, before, temp1);
        if(equal(n, after, temp1) == 0)
          fprintf(fout, "4\n");
        else
        {
          for(i = 0; i < 3; i ++)
          {
            trans1(n, temp1, temp2);
            if(equal(n, after, temp2) == 0)
            {
              fprintf(fout, "5\n");
              break;
            }
            else
            {
              for(j = 0; j < n; j ++)
                strcpy(temp1[j], temp2[j]);
            }
          }
          if(i == 3)
          {
            if(equal(n, after, before) == 0)
              fprintf(fout, "6\n");
            else
              fprintf(fout, "7\n");
          }
        }
      }
    }
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
