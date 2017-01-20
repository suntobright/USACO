/*
ID: suntobr1
LANG: C
TASK: beads
*/

#include <stdio.h>

int search(char bead[], int begin, int len, int type)
{
  char color;
  int sum, pos;
  color = bead[begin];
  sum = 1;
  pos = (begin + type + len) % len;
  while((color == 'w' || bead[pos] == 'w' || color == bead[pos])&&(pos != begin))
  {
    if(color == 'w')
      color = bead[pos];
    sum ++;
    pos = (pos + type + len) % len;
  }
  return sum;
}

int main(void)
{
  FILE *fin, *fout;

  fin = fopen("beads.in", "r");
  fout = fopen("beads.out", "w");

  char bead[360];
  int n, max, temp;
  int i, j;

  fscanf(fin, "%d", &n);
  fscanf(fin, "%s", bead);

  for(i = 0, max = 0; i < n - 1; i ++)
  {
    temp = search(bead, i, n, -1) + search(bead, i + 1, n, 1);
    if(max < temp)
      max = temp;
    if(max == 2 * n)
    {
      max = n;
      break;
    }
  }
  if(max == n)
    fprintf(fout, "%d\n", max);
  else
  {
    temp = search(bead, i, n, -1) + search(bead, 0, n, 1);
    if(max < temp)
      max = temp;
    fprintf(fout, "%d\n", max);
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
