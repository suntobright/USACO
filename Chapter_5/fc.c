/*
ID: suntobr1
LANG: C
TASK: fc
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265

int n;
double midx;
double midy;
double points[10000][2];

int picked[10000];
int pickStart;
int pickStop;

double length;

int cmp(const void* a, const void* b) {
  const double* p1 = (const double *) a;
  const double* p2 = (const double *) b;

  double angle1 = atan2(p1[1] - midy, p1[0] - midx);
  double angle2 = atan2(p2[1] - midy, p2[0] - midx);

  return angle1 < angle2 ? -1 : 1;
}

double getLength(double x, double y) {
  return sqrt(x * x + y * y);
}

int main(void)
{
  FILE* fin = fopen("fc.in", "rb");
  FILE* fout = fopen("fc.out", "wb");

  int i = 0;

  fscanf(fin, "%d", &n);
  for (i = 0; i < n; i ++) {
    fscanf(fin, "%lf%lf", &points[i][0], &points[i][1]);
    midx += points[i][0] / n;
    midy += points[i][1] / n;
  }

  qsort(points, n, sizeof(double) * 2, cmp);

  picked[pickStop ++] = 0;
  picked[pickStop ++] = 1;
  for (i = 2; i < n; i ++) {
    while (1) {
      double angle1 = atan2(
          points[picked[pickStop - 1]][1] - points[picked[pickStop - 2]][1],
          points[picked[pickStop - 1]][0] - points[picked[pickStop - 2]][0]);
      double angle2 = atan2(
          points[i][1] - points[picked[pickStop - 1]][1],
          points[i][0] - points[picked[pickStop - 1]][0]);

      if ((angle1 > 0 && angle2 < angle1 && angle2 > angle1 - PI)
          || (angle1 < 0 && (angle2 < angle1 || angle2 > angle1 + PI))) {
        pickStop --;
      } else {
        break;
      }
    }

    picked[pickStop ++] = i;
  }

  while (1) {
    double angle1 = 0;
    double angle2 = 0;

    angle1 = atan2(
        points[picked[pickStop - 1]][1] - points[picked[pickStop - 2]][1],
        points[picked[pickStop - 1]][0] - points[picked[pickStop - 2]][0]);
    angle2 = atan2(
        points[picked[pickStart]][1] - points[picked[pickStop - 1]][1],
        points[picked[pickStart]][0] - points[picked[pickStop - 1]][0]);
    if ((angle1 > 0 && angle2 < angle1 && angle2 > angle1 - PI)
        || (angle1 < 0 && (angle2 < angle1 || angle2 > angle1 + PI))) {
      pickStop --;
      continue;
    }

    angle1 = angle2;
    angle2 = atan2(
        points[picked[pickStart + 1]][1] - points[picked[pickStart]][1],
        points[picked[pickStart + 1]][0] - points[picked[pickStart]][0]);
    if ((angle1 > 0 && angle2 < angle1 && angle2 > angle1 - PI)
        || (angle1 < 0 && (angle2 < angle1 || angle2 > angle1 + PI))) {
      pickStart ++;
      continue;
    }

    break;
  }

  for (i = pickStart; i < pickStop - 1; i ++) {
    length += getLength(points[picked[i]][0] - points[picked[i + 1]][0],
        points[picked[i]][1] - points[picked[i + 1]][1]);
  }
  length += getLength(points[picked[pickStart]][0] - points[picked[pickStop - 1]][0],
      points[picked[pickStart]][1] - points[picked[pickStop - 1]][1]);

  fprintf(fout, "%.2lf\n", length);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
