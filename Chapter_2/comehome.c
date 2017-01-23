/*
ID: suntobr1
LANG: C
TASK: comehome
*/

#include <stdio.h>

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int n;
  int path[64][64];
  int has[64] = { 0 };

  int dist[64] = { 0 };
  int visit[64] = { 0 };
  int cur;
  int min;

  char from[4], to[4];
  int length;

  int i, j;

  in = fopen("comehome.in", "rb");
  out = fopen("comehome.out", "wb");

  for (i = 0; i < 64; i++)
  {
    path[i][i] = 0;
    for (j = i + 1; j < 64; j++)
      path[i][j] = path[j][i] = 0x70000000;
  }

  fscanf(in, "%d", &n);
  for (i = 0; i < n; i++)
  {
    fscanf(in, "%s%s%d", from, to, &length);

    if (from[0] >= 'A' && from[0] <= 'Z')
    {
      from[0] = from[0] - 'A' + 26;
      has[from[0]] = 1;
    }
    else
      from[0] -= 'a';
    if (to[0] >= 'A' && to[0] <= 'Z')
    {
      to[0] = to[0] - 'A' + 26;
      has[to[0]] = 1;
    }
    else
      to[0] -= 'a';
    if (path[from[0]][to[0]] > length)
      path[from[0]][to[0]] = path[to[0]][from[0]] = length;
  }

  has[51] = 0;
  visit[51] = 1;
  for (i = 0; i < 64; i++)
    dist[i] = path[51][i];
  cur = 51;

  while (has[cur] == 0)
  {
    min = 0x70000000;
    for (i = 0; i < 64; i++)
      if (visit[i] == 0 && min > dist[i])
      {
        min = dist[i];
        cur = i;
      }

    visit[cur] = 1;
    for (i = 0; i < 64; i++)
      if (dist[i] > dist[cur] + path[cur][i])
        dist[i] = dist[cur] + path[cur][i];
  }

  fprintf(out, "%c %d\n", cur - 26 + 'A', dist[cur]);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
