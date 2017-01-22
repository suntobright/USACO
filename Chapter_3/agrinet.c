/*
ID: suntobr1
LANG: C
TASK: agrinet
*/

#include <stdio.h>

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int n;
  int grid[128][128];
  int dist[128] = { 0 };
  int intree[128] = { 0 };
  int treesize = 0;
  int treecost = 0;

  int i, j;
  int mindist;
  int minnode;

  in = fopen("agrinet.in", "rb");
  out = fopen("agrinet.out", "wb");

  fscanf(in, "%d", &n);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      fscanf(in, "%d", &grid[i][j]);

  intree[0] = 1;
  treesize = 1;
  for (i = 0; i < n; i++)
    dist[i] = grid[0][i];

  while (treesize < n)
  {
    mindist = 0x7fffffff;
    minnode = -1;
    for (i = 0; i < n; i ++)
      if (intree[i] == 0 && mindist > dist[i])
      {
        mindist = dist[i];
        minnode = i;
      }

    intree[minnode] = 1;
    treesize++;
    treecost += mindist;

    for (i = 0; i < n; i++)
      if (dist[i] > grid[minnode][i])
        dist[i] = grid[minnode][i];
  }

  fprintf(out, "%d\n", treecost);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
