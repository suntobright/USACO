/*
ID: suntobr1
LANG: C
TASK: telecow
*/

#include <stdio.h>

int nodeCount;
int pathCount;
int paths[200][200];

int src;
int dst;

int temp[200][200];
int prev[200];
int visited[200];

int queue[200];
int begin;
int end;

int removed[100];
int count;

int getFlow() {
  int flow = 0;

  int i = 0;
  int j = 0;

  for (i = 0; i < nodeCount * 2; i ++) {
    for (j = 0; j < nodeCount * 2; j ++) {
      temp[i][j] = paths[i][j];
    }
  }

  while (1) {
    for (i = 0; i < nodeCount * 2; i ++) {
      prev[i] = -1;
      visited[i] = 0;
    }

    begin = end = 0;
    queue[begin ++] = src * 2 + 1;
    visited[src * 2 + 1] = 1;
    while (begin != end) {
      int cur = queue[end ++];

      if (cur == dst * 2) {
        break;
      }

      for (i = 0; i < nodeCount * 2; i ++) {
        if (visited[i] == 0 && temp[cur][i] == 1) {
          queue[begin ++] = i;
          visited[i] = 1;
          prev[i] = cur;
        }
      }
    }

    if (visited[dst * 2] == 0) {
      break;
    }

    flow ++;
    for (i = dst * 2; i != src * 2 + 1; i = prev[i]) {
      temp[prev[i]][i] --;
      temp[i][prev[i]] ++;
    }
  }

  return flow;
}

void removeNode(int flow) {
  int i = 0;
  int currentFlow;

  if (flow == 0) {
    return;
  }

  for (i = 0; i < nodeCount; i ++) {
    if (i != src && i != dst && paths[i * 2][i * 2 + 1]) {
      paths[i * 2][i * 2 + 1] = 0;
      currentFlow = getFlow();
      if (currentFlow + 1 == flow) {
        removeNode(currentFlow);
        break;
      }
      paths[i * 2][i * 2 + 1] = 1;
    }
  }
}

int main(void)
{
  FILE* fin = fopen("telecow.in", "rb");
  FILE* fout = fopen("telecow.out", "wb");

  int i = 0;

  int x = 0;
  int y = 0;

  fscanf(fin, "%d%d%d%d", &nodeCount, &pathCount, &src, &dst);
  src --;
  dst --;
  for (i = 0; i < pathCount; i ++) {
    fscanf(fin, "%d%d", &x, &y);
    x --;
    y --;
    paths[x * 2 + 1][y * 2] = paths[y * 2 + 1][x * 2] = 1;
  }
  for (i = 0; i < nodeCount; i ++) {
    paths[i * 2][i * 2 + 1] = 1;
  }

  removeNode(getFlow());

  count = 0;
  for (i = 0; i < nodeCount; i ++) {
    if (paths[i * 2][i * 2 + 1] == 0) {
      removed[count ++] = i + 1;
    }
  }

  fprintf(fout, "%d\n", count);
  fprintf(fout, "%d", removed[0]);
  for (i = 1; i < count; i ++) {
    fprintf(fout, " %d", removed[i]);
  }
  fprintf(fout, "\n");

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
