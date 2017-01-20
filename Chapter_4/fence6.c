/*
ID: b8flowe1
LANG: C
TASK: fence6
*/
#include <stdio.h>

int count;
int segment_length[100];
int next_segment_count[100][2];
int next_segment_pos[100][2][8];
int next_segment_end[100][2][8];
int min_length;
int used[100][2];

void find_min_length(int start, int pos, int end, int current_length)
{
  int i, j;
  int next_count;
  int next_pos;
  int next_end;

  if (min_length <= current_length)
    return;

  next_count = next_segment_count[pos][end];
  for (i = 0; i < next_count; i ++)
  {
    next_pos = next_segment_pos[pos][end][i];
    if (next_pos >= start)
    {
      next_end = next_segment_end[pos][end][i] == 1 ? 0 : 1;

      if (used[next_pos][next_end] == 0)
      {
        used[next_pos][next_end] = 1;
        for (j = 0; j < next_segment_count[next_pos][next_end]; j ++)
          used[next_segment_pos[next_pos][next_end][j]][next_segment_end[next_pos][next_end][j]] = 1;
        find_min_length(start, next_pos, next_end, current_length + segment_length[next_pos]);
        used[next_pos][next_end] = 0;
        for (j = 0; j < next_segment_count[next_pos][next_end]; j ++)
          used[next_segment_pos[next_pos][next_end][j]][next_segment_end[next_pos][next_end][j]] = 0;
      }
      else if (used[next_pos][next_end] == -1)
      {
        if (min_length > current_length + segment_length[next_pos])
          min_length = current_length + segment_length[next_pos];
      }
    }
  }
}

int main(void)
{
  FILE* fin = fopen("fence6.in", "rb");
  FILE* fout = fopen("fence6.out", "wb");

  int i, j, k, l;
  int pos;
  int next_count;
  int next_pos;
  int next_end;
  int end;

  fscanf(fin, "%d", &count);
  for (i = 0; i < count; i ++)
  {
    fscanf(fin, "%d", &pos);
    pos --;
    fscanf(fin, "%d%d%d", &segment_length[pos], &next_segment_count[pos][0],
        &next_segment_count[pos][1]);
    for (j = 0; j < 2; j ++)
      for (k = 0; k < next_segment_count[pos][j]; k ++)
      {
        fscanf(fin, "%d", &next_segment_pos[pos][j][k]);
        next_segment_pos[pos][j][k] --;
      }
  }

  for (i = 0; i < count; i ++)
    for (j = 0; j < 2; j ++)
    {
      next_count = next_segment_count[i][j];
      for (k = 0; k < next_count; k ++)
      {
        next_pos = next_segment_pos[i][j][k];
        if (next_pos > i)
        {
          for (end = 0; end < 2; end ++)
          {
            for (l = 0; l < next_segment_count[next_pos][end]; l ++)
              if (i == next_segment_pos[next_pos][end][l])
                break;
            if (l < next_segment_count[next_pos][end])
              break;
          }
          next_segment_end[i][j][k] = end;
          next_segment_end[next_pos][end][l] = j;
        }
      }
    }

  min_length = 0;
  for (i = 0; i < count; i ++)
    min_length += segment_length[i];

  for (i = 0; i < count; i ++)
  {
    used[i][0] = -1;
    next_count = next_segment_count[i][0];
    for (j = 0; j < next_count; j ++)
    {
      next_pos = next_segment_pos[i][0][j];
      next_end = next_segment_end[i][0][j];
      used[next_pos][next_end] = -1;
    }
    used[i][1] = 1;
    next_count = next_segment_count[i][1];
    for (j = 0; j < next_count; j ++)
    {
      next_pos = next_segment_pos[i][1][j];
      next_end = next_segment_end[i][1][j];
      used[next_pos][next_end] = 1;
    }

    find_min_length(i, i, 1, segment_length[i]);

    for (j = 0; j < 2; j ++)
    {
      used[i][j] = 0;
      next_count = next_segment_count[i][j];
      for (k = 0; k < next_count; k ++)
      {
        next_pos = next_segment_pos[i][j][k];
        next_end = next_segment_end[i][j][k];
        used[next_pos][next_end] = 0;
      }
    }
  }

  fprintf(fout, "%d\n", min_length);

  fclose(fin);
  fclose(fout);

  return 0;
}
