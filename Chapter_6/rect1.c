/*
ID: suntobr1
LANG: C
TASK: rect1
*/

#include <stdio.h>
#include <stdlib.h>

short sheet[2048][2048];
short color[1024][5];
int count[1024];
short xlist[2048];
short ylist[2048];
short xcount;
short ycount;

int cmp(const void *a, const void *b)
{
  return *((short *)a) - *((short *)b);
}

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int a, b, n;

  int i, j, k;
  int x1, y1, x2, y2;

  in = fopen("rect1.in", "rb");
  out = fopen("rect1.out", "wb");

  fscanf(in, "%d%d%d", &a, &b, &n);
  for (i = 0; i < n; i++)
    for (j = 0; j < 5; j++)
      fscanf(in, "%hd", &color[i][j]);

  for (i = 0; i < 2048; i++)
    for (j = 0; j < 2048; j++)
      sheet[i][j] = 1;

  for (i = 0; i < n; i++)
  {
    xlist[xcount++] = color[i][0];
    ylist[ycount++] = color[i][1];
    xlist[xcount++] = color[i][2];
    ylist[ycount++] = color[i][3];
  }

  xlist[xcount++] = 0;
  ylist[ycount++] = 0;
  xlist[xcount++] = a;
  ylist[ycount++] = b;

  qsort(xlist, xcount, sizeof(short), cmp);
  qsort(ylist, ycount, sizeof(short), cmp);

  j = 0;
  for (i = 1; i < xcount; i++)
    if (xlist[i] != xlist[j])
      xlist[++j] = xlist[i];
  xcount = j + 1;

  j = 0;
  for (i = 1; i < ycount; i++)
    if (ylist[i] != ylist[j])
      ylist[++j] = ylist[i];
  ycount = j + 1;

  for (i = 0; i < n; i++)
  {
    x1 = (short *)bsearch(&color[i][0], xlist, xcount, sizeof(short), cmp) - xlist;
    y1 = (short *)bsearch(&color[i][1], ylist, ycount, sizeof(short), cmp) - ylist;

    x2 = (short *)bsearch(&color[i][2], xlist, xcount, sizeof(short), cmp) - xlist;
    y2 = (short *)bsearch(&color[i][3], ylist, ycount, sizeof(short), cmp) - ylist;

    for (j = x1; j < x2; j++)
      for (k = y1; k < y2; k++)
        sheet[j][k] = color[i][4];
  }

  for (i = 0; i < xcount - 1; i++)
    for (j = 0; j < ycount - 1; j++)
      count[sheet[i][j]] += (xlist[i + 1] - xlist[i]) * (ylist[j + 1] - ylist[j]);

  for (i = 1; i < 1024; i++)
    if (count[i] != 0)
      fprintf(out, "%d %d\n", i, count[i]);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
