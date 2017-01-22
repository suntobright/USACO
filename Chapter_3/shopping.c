/*
ID: suntobr1
LANG: C
TASK: shopping
*/

#include <stdio.h>

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int s;
  int offer[128][2] = { 0 };
  int need[128][5] = { 0 };
  int pair[128][5][2] = { 0 };
  int b;
  int buy[5] = { 0 };
  int price[5] = { 0 };
  int map[1024] = { 0 };
  int dp[6][6][6][6][6] = { 0 };
  int sum;

  int i, j, k, l, m, n;
  int temp;

  in = fopen("shopping.in", "rb");
  out = fopen("shopping.out", "wb");

  for (i = 0; i < 1024; i++)
    map[i] = -1;

  fscanf(in, "%d", &s);
  for (i = 0; i < s; i++)
  {
    fscanf(in, "%d", &offer[i][0]);
    for (j = 0; j < offer[i][0]; j++)
      fscanf(in, "%d%d", &pair[i][j][0], &pair[i][j][1]);
    fscanf(in, "%d", &offer[i][1]);
  }
  fscanf(in, "%d", &b);
  for (i = 0; i < b; i++)
  {
    fscanf(in, "%d%d%d", &temp, &buy[i], &price[i]);
    map[temp] = i;
  }

  k = 0;
  for (i = 0; i < s; i++)
  {
    for (j = 0; j < offer[i][0]; j++)
      if (map[pair[i][j][0]] == -1)
        break;

    if (j == offer[i][0])
    {
      offer[k][0] = offer[i][0];

      sum = 0;
      for (j = 0; j < offer[i][0]; j++)
      {
        need[k][map[pair[i][j][0]]] = pair[i][j][1];
        sum += pair[i][j][1] * price[map[pair[i][j][0]]];
      }
      offer[k][1] = sum - offer[i][1];

      k++;
    }
  }
  s = k;

  sum = 0;
  for (i = 0; i <= buy[0]; i++)
    for (j = 0; j <= buy[1]; j++)
      for (k = 0; k <= buy[2]; k++)
        for (l = 0; l <= buy[3]; l++)
          for (m = 0; m <= buy[4]; m++)
          {
            sum = 0;
            for (n = 0; n < s; n++)
              if (i >= need[n][0] && j >= need[n][1] && k >= need[n][2] && l >= need[n][3] && m >= need[n][4])
                if (sum < dp[i - need[n][0]][j - need[n][1]][k - need[n][2]][l - need[n][3]][m - need[n][4]] + offer[n][1])
                  sum = dp[i - need[n][0]][j - need[n][1]][k - need[n][2]][l - need[n][3]][m - need[n][4]] + offer[n][1];

            dp[i][j][k][l][m] = sum;
          }

  sum = 0;
  for (i = 0; i < b; i++)
    sum += buy[i] * price[i];

  fprintf(out, "%d\n", sum - dp[buy[0]][buy[1]][buy[2]][buy[3]][buy[4]]);

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
