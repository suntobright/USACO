/*
ID: suntobr1
LANG: C
TASK: milk2
*/

typedef struct SEG
{
  int min, max;
  struct SEG *next;
} Segment;

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fin, *fout;

  fin = fopen("milk2.in", "r");
  fout = fopen("milk2.out", "w");

  int n, max, min;
  Segment *begin, *pre, *p;
  int i;

  fscanf(fin, "%d", &n);
  begin = (Segment *)malloc(sizeof(Segment));
  begin -> max = -1;
  begin -> next = NULL;
  for(i = 0; i < n; i ++)
  {
    fscanf(fin, "%d %d", &min, &max);
    for(pre = begin, p = begin -> next; p != NULL;)
    {
      if(p -> max < max)
      {
        if(p -> max < min)
        {
          pre = p;
          p = p -> next;
        }
        else
        {
          min = (p -> min > min)? min : p -> min;
          pre -> next = p -> next;
          free(p);
          p = pre -> next;
        }
      }
      else
        break;
    }
    if(p == NULL || p -> min > max)
    {
      pre -> next = (Segment *)malloc(sizeof(Segment));
      pre -> next -> min = min;
      pre -> next -> max = max;
      pre -> next -> next = p;
    }
    else if(p -> min > min)
    {
      p -> min = min;
    }
  }

  min = 0;
  max = 0;
  for(pre = begin, p = begin -> next; p != NULL; pre = p, p = p -> next)
  {
    if(max < p -> max - p -> min)
      max = p -> max - p -> min;
    if(pre -> max != -1 && min < p -> min - pre -> max)
      min = p -> min - pre -> max;
  }

  fprintf(fout, "%d %d\n", max, min);

  for(pre = begin, p = begin -> next; p != NULL; pre = p, p = p -> next)
  {
    free(pre);
  }
  free(pre);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
