/*
ID: suntobr1
LANG: C
TASK: calfflac
*/

#include<stdio.h>
#include<string.h>

int isletter(char temp)
{
  if(temp >= 'A' && temp <= 'Z')
    return 1;
  else if(temp >= 'a' && temp <= 'z')
    return 1;
  else
    return 0;
}

int main()
{
  FILE *fin, *fout;

  char text[21000];
  char temp[101];
  int i, j, k, max, begin, end, pb, pe, len, type;

  fin = fopen("calfflac.in", "r");
  fout = fopen("calfflac.out", "w");

  strcpy(text, "");
  while(fgets(temp, 100, fin) != NULL)
  {
    strcat(text, temp);
  }

  for(i = 0, max = 0; text[i] != '\0'; i ++)
  {
    for(type = 0; type < 2; type ++)
    {
      if(type == 1 && isletter(text[i]) == 0)
        continue;
      j = i - 1;
      k = i + type;
      len = 0;
      while(1)
      {
        for(; j >= 0 && isletter(text[j]) == 0; j --);
        for(; text[k] != '\0' && isletter(text[k]) == 0; k ++);
        if(j == -1 || text[k] == '\0')
          break;
        else if(text[j] == text[k] || text[j] == text[k] + 'A' - 'a' || text[j] == text[k] - 'A' + 'a')
        {
          pb = j; pe = k;
          j --; k ++; len ++;
        }
        else
          break;
      }
      if(max < len + len + type)
      {
        max = len + len + type;
        begin = pb;
        end = pe;
      }
    }
  }

  fprintf(fout, "%d\n", max);
  for(i = begin; i <= end; i ++)
  {
    fprintf(fout, "%c", text[i]);
  }
  fprintf(fout, "\n");

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
