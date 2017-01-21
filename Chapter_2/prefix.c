/*
ID: suntobr1
LANG: C
TASK: prefix
*/

#include <stdio.h>
#include <string.h>

int main()
{
  FILE *fin, *fout;

  int query[200002] = {0};
  char string[200002] = "";
  char prefix[200][15] = {0};
  char temp[100];
  int count, len, pos, i, j;

  fin = fopen("prefix.in", "r");
  fout = fopen("prefix.out", "w");

  count = 0;
  while(1)
  {
    fscanf(fin, "%s", temp);
    if(strcmp(temp, ".") == 0)
      break;
    else
      strcpy(prefix[count ++], temp);
  }
  while(fscanf(fin, "%s", temp) != EOF)
  {
    strcat(string, temp);
  }

  len = strlen(string);
  query[0] = 1;
  for(i = 1; i <= len; i ++)
  {
    for(j = 0; j < count; j ++)
    {
      pos = i - strlen(prefix[j]);
      if(pos >= 0 && query[pos] == 1 && strncmp(string + pos, prefix[j], i - pos) == 0)
      {
        query[i] = 1;
        break;
      }
    }
  }

  while(query[-- i] == 0);

  fprintf(fout, "%d\n", i);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
