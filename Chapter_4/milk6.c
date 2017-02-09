/*
ID: suntobr1
LANG: C
TASK: milk6
*/

#include <stdio.h>
#include <stdlib.h>

int n;
int routeCount;
int costs[32][32];
int routes[1000][3];

int sortedRoutes[1000];
int isPicked[1000];

int totalCost;
int keyRoutes[1000];
int keyRouteCount;

int cmp1(const void* a, const void* b) {
  int x = *((const int *) a);
  int y = *((const int *) b);
  return routes[y][2] - routes[x][2];
}

int cmp2(const void* a, const void* b) {
  int x = *((const int *) a);
  int y = *((const int *) b);
  return x - y;
}

int min(int a, int b) {
  return a < b ? a : b;
}

int getMaxFlow() {
  int maxFlow = 0;
  int paths[32][32] = {{0}};

  int i = 0;
  int j = 0;

  for (i = 0; i < n; i ++) {
    for (j = 0; j < n; j ++) {
      paths[i][j] = costs[i][j];
    }
  }

  while (1) {
    int visited[32] = {0};
    int values[32] = {0};
    int pres[32] = {0};
    int current = 0;

    visited[0] = 1;
    pres[0] = -1;
    for (i = 0; i < n; i ++) {
      values[i] = paths[0][i];
    }

    while (visited[n - 1] == 0) {
      int maxPos = -1;
      int maxValue = 0;
      for (i = 0; i < n; i ++) {
        if (visited[i] == 0 && maxValue < values[i]) {
          maxPos = i;
          maxValue = values[i];
        }
      }

      if (maxPos == -1) {
        break;
      }

      visited[maxPos] = 1;
      for (i = 0; i < n; i ++) {
        if (visited[i] == 0 && values[i] < min(maxValue, paths[maxPos][i])) {
          values[i] = min(maxValue, paths[maxPos][i]);
          pres[i] = maxPos;
        }
      }
    }

    if (visited[n - 1] == 0) {
      break;
    }

    maxFlow += values[n - 1];
    for (current = n - 1; current != 0; current = pres[current]) {
      paths[pres[current]][current] -= values[n - 1];
      paths[current][pres[current]] += values[n - 1];
    }
  }

  return maxFlow;
}

void getKeyRoutes(int maxFlow) {
  int i = 0;

  if (maxFlow == 0) {
    return;
  }

  for (i = 0; i < routeCount; i ++) {
    if (isPicked[i] == 0) {
      int currentMaxFlow = 0;

      costs[routes[sortedRoutes[i]][0]][routes[sortedRoutes[i]][1]] -= routes[sortedRoutes[i]][2];
      currentMaxFlow = getMaxFlow();
      if (currentMaxFlow + routes[sortedRoutes[i]][2] == maxFlow) {
        totalCost += routes[sortedRoutes[i]][2];
        keyRoutes[keyRouteCount ++] = sortedRoutes[i];
        isPicked[i] = 1;
        return getKeyRoutes(currentMaxFlow);
      } else {
        costs[routes[sortedRoutes[i]][0]][routes[sortedRoutes[i]][1]] += routes[sortedRoutes[i]][2];
      }
    }
  }
}

int main(void)
{
  FILE* fin = fopen("milk6.in", "rb");
  FILE* fout = fopen("milk6.out", "wb");

  int i = 0;

  fscanf(fin, "%d%d", &n, &routeCount);
  for (i = 0; i < routeCount; i ++) {
    fscanf(fin, "%d%d%d", &routes[i][0], &routes[i][1], &routes[i][2]);
    routes[i][0] -= 1;
    routes[i][1] -= 1;
    costs[routes[i][0]][routes[i][1]] += routes[i][2];
  }

  for (i = 0; i < routeCount; i ++) {
    sortedRoutes[i] = i;
  }
  qsort(sortedRoutes, routeCount, sizeof(int), cmp1);

  getKeyRoutes(getMaxFlow());

  qsort(keyRoutes, keyRouteCount, sizeof(int), cmp2);

  fprintf(fout, "%d %d\n", totalCost, keyRouteCount);
  for (i = 0; i < keyRouteCount; i ++) {
    fprintf(fout, "%d\n", keyRoutes[i] + 1);
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
