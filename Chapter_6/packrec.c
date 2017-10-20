/*
ID: suntobr1
LANG: C
TASK: packrec
*/

typedef struct
{
  int x, y;
}Rect;

#include<stdio.h>
#include<stdlib.h>

int max(int a, int b)
{
  return a > b ? a : b;
}

int cmp(const void *a, const void *b)
{
  return ((Rect *)a) -> x - ((Rect *)b) -> x;
}

int main()
{
  FILE *fin, *fout;

  Rect rect[4];
  Rect temp[4];
  Rect reco[1000];
  int min, pose, x, y, square;
  int order[4], stat[4] = {0};
  int i, n;

  fin = fopen("packrec.in", "r");
  fout = fopen("packrec.out", "w");

  for(i = 0; i < 4; i ++)
    fscanf(fin, "%d %d", &rect[i].x, &rect[i].y);

  min = 10001;

  for(order[0] = 0; order[0] < 4; order[0] ++)
  {
    stat[order[0]] = 1;
    for(order[1] = 0; order[1] < 4; order[1] ++)
    {
      if(stat[order[1]] == 1)
        continue;
      stat[order[1]] = 1;
      for(order[2] = 0; order[2] < 4; order[2] ++)
      {
        if(stat[order[2]] == 1)
          continue;
        stat[order[2]] = 1;
        for(order[3] = 0; order[3] < 4; order[3] ++)
        {
          if(stat[order[3]] == 1)
            continue;
          for(pose = 0; pose < 16; pose ++)
          {
            for(i = 0; i < 4; i ++)
            {
              if((pose >> i) & 1)
              {
                temp[i].x = rect[order[i]].y;
                temp[i].y = rect[order[i]].x;
              }
              else
                temp[i] = rect[order[i]];
            }

            // Layout 1
            x = temp[0].x + temp[1].x + temp[2].x + temp[3].x;
            y = max(max(temp[0].y, temp[1].y), max(temp[2].y, temp[3].y));
            square = x * y;
            if(min > square)
            {
              min = square;
              reco[0].x = x < y ? x : y;
              reco[0].y = x > y ? x : y;
              n = 1;
            }
            else if(min == square)
            {
              reco[n].x = x < y ? x : y;
              reco[n].y = x > y ? x : y;
              n ++;
            }

            // Layout 2
            x = max(temp[0].x, temp[1].x + temp[2].x + temp[3].x);
            y = temp[0].y + max(temp[1].y, max(temp[2].y, temp[3].y));
            square = x * y;
            if(min > square)
            {
              min = square;
              reco[0].x = x < y ? x : y;
              reco[0].y = x > y ? x : y;
              n = 1;
            }
            else if(min == square)
            {
              reco[n].x = x < y ? x : y;
              reco[n].y = x > y ? x : y;
              n ++;
            }

            // Layout 3
            x = max(temp[0].x, temp[1].x + temp[2].x) + temp[3].x;
            y = max(temp[0].y + max(temp[1].y, temp[2].y), temp[3].y);
            square = x * y;
            if(min > square)
            {
              min = square;
              reco[0].x = x < y ? x : y;
              reco[0].y = x > y ? x : y;
              n = 1;
            }
            else if(min == square)
            {
              reco[n].x = x < y ? x : y;
              reco[n].y = x > y ? x : y;
              n ++;
            }

            // Layout 4
            x = temp[0].x + max(temp[1].x, temp[2].x) + temp[3].x;
            y = max(temp[0].y, max(temp[1].y + temp[2].y, temp[3].y));
            square = x * y;
            if(min > square)
            {
              min = square;
              reco[0].x = x < y ? x : y;
              reco[0].y = x > y ? x : y;
              n = 1;
            }
            else if(min == square)
            {
              reco[n].x = x < y ? x : y;
              reco[n].y = x > y ? x : y;
              n ++;
            }

            // Layout 5
            x = max(temp[0].x + temp[1].x, temp[2].x + temp[3].x);
            y = max(temp[0].y + temp[3].y, temp[1].y + temp[2].y);
            if(temp[0].x + temp[2].x > x && temp[0].y + temp[2].y > y)
              x = temp[0].x + temp[2].x;
            else if(temp[1].x + temp[3].x > x && temp[1].y + temp[3].y > y)
              x = temp[1].x + temp[3].x;
            square = x * y;
            if(min > square)
            {
              min = square;
              reco[0].x = x < y ? x : y;
              reco[0].y = x > y ? x : y;
              n = 1;
            }
            else if(min == square)
            {
              reco[n].x = x < y ? x : y;
              reco[n].y = x > y ? x : y;
              n ++;
            }
          }
        }
        stat[order[2]] = 0;
      }
      stat[order[1]] = 0;
    }
    stat[order[0]] = 0;
  }

  qsort(reco, n, sizeof(Rect), cmp);

  fprintf(fout, "%d\n", min);
  for(i = 0; i < n; i ++)
  {
    if(i > 0 && reco[i].x == reco[i - 1].x)
      continue;
    fprintf(fout, "%d %d\n", reco[i].x, reco[i].y);
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
