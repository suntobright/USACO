/*
ID: suntobr1
LANG: C
TASK: nuggets
*/

#include <stdio.h>

int n;
int nums[16];
int status[65536];

void check(int num) {
  int i = 0;

  for (i = 0; i < n; i++) {
    if (num - nums[i] >= 0) {
      if (status[num - nums[i]] == 0) {
        check(num - nums[i]);
      }
      if (status[num - nums[i]] == 1) {
        status[num] = 1;
        break;
      }
    }
  }

  if (i == n) {
    status[num] = -1;
  }
}

int main(void)
{
  FILE* fin = fopen("nuggets.in", "rb");
  FILE* fout = fopen("nuggets.out", "wb");

  int i = 0;

  fscanf(fin, "%d", &n);
  status[0] = 1;
  for (i = 0; i < n; i++) {
    fscanf(fin, "%d", &nums[i]);
    status[nums[i]] = 1;
  }

  for (i = 65535; i > 0; i--) {
    if (status[i] == 0) {
      check(i);
    }

    if (status[i] == -1) {
      break;
    }
  }

  if (i == 0 || i + 256 > 65535) {
    fprintf(fout, "0\n");
  } else {
    fprintf(fout, "%d\n", i);
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
