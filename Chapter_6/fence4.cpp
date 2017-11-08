/*
ID: suntobr1
LANG: C
TASK: fence4
*/

#include <stdio.h>

typedef struct
{
  double x;
  double y;
} Point;

int check(Point node)
{
  if (node.x >= -1e-10 && node.x <= (1 + 1e-10) && node.y >= -1e-10 && node.y <= (1 + 1e-10))
    return 1;
  return 0;
}

int join(Point a, Point b, Point c, Point d, Point *node)
{
  double a11 = b.x - a.x;
  double a12 = c.x - d.x;
  double a13 = c.x - a.x;
  double a21 = b.y - a.y;
  double a22 = c.y - d.y;
  double a23 = c.y - a.y;

  node->x = (a13 * a22 - a12 * a23) / (a11 * a22 - a12 * a21);
  node->y = (a11 * a23 - a13 * a21) / (a11 * a22 - a12 * a21);

  return check(*node);
}

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  int n;
  Point stand;
  Point points[200];
  int segment[200][2];
  int count = 0;
  Point min, max;
  Point node, node1, node2;

  int i, j;

  in = fopen("fence4.in", "rb");
  out = fopen("fence4.out", "wb");

  fscanf(in, "%d", &n);
  fscanf(in, "%lf%lf", &stand.x, &stand.y);
  for (i = 0; i < n; i++)
    fscanf(in, "%lf%lf", &points[i].x, &points[i].y);

  for (i = 0; i < n; i++)
  {
    for (j = (i + 2) % n; (j + 1) % n != i; j = (j + 1) % n)
      if (join(points[i], points[(i + 1) % n], points[j], points[(j + 1) % n], &node) == 1)
        break;

    if ((j + 1) % n != i)
      break;
  }

  if (i < n)
  {
    fprintf(out, "NOFENCE\n");

    fflush(out);
    fclose(in);
    fclose(out);

    return 0;
  }

  for (i = 0; i < n; i++)
  {
    min = points[i];
    max = points[(i + 1) % n];

    for (j = (i + 1) % n; j != i; j = (j + 1) % n)
    {
      join(stand, min, points[j], points[(j + 1) % n], &node1);
      join(stand, max, points[j], points[(j + 1) % n], &node2);

      if (check(node1) == 1 && check(node2) == 1)
        break;

      if (check(node1) == 1)
      {
        join(stand, points[j], min, max, &node);
        if (node.x > 1 && node.y >= 0 && node.y <= 1)
        {
          min.x += node.y * (max.x - min.x);
          min.y += node.y * (max.y - min.y);
        }
        join(stand, points[(j + 1) % n], min, max, &node);
        if (node.x > 1 && node.y >= 0 && node.y <= 1)
        {
          min.x += node.y * (max.x - min.x);
          min.y += node.y * (max.y - min.y);
        }
      }

      if (check(node2) == 1)
      {
        join(stand, points[j], min, max, &node);
        if (node.x > 1 && node.y >= 0 && node.y <= 1)
        {
          max.x -= (1 - node.y) * (max.x - min.x);
          max.y -= (1 - node.y) * (max.y - min.y);
        }
        join(stand, points[(j + 1) % n], min, max, &node);
        if (node.x > 1 && node.y >= 0 && node.y <= 1)
        {
          max.x -= (1 - node.y) * (max.x - min.x);
          max.y -= (1 - node.y) * (max.y - min.y);
        }
      }
    }

    if (i == j && i != n - 1)
    {
      segment[count][0] = i;
      segment[count][1] = (i + 1) % n;
      count++;
    }
    else if (i == j && i == n - 1)
    {
      segment[count][0] = 0;
      segment[count][1] = i;

      if (segment[count][1] == segment[count - 1][1])
      {
        segment[count][0] = segment[count - 1][0];
        segment[count - 1][0] = 0;
      }

      count++;
    }
  }

  fprintf(out, "%d\n", count);
  for (i = 0; i < count; i++)
  {
    fprintf(out, "%.0lf %.0lf ", points[segment[i][0]].x, points[segment[i][0]].y);
    fprintf(out, "%.0lf %.0lf\n", points[segment[i][1]].x, points[segment[i][1]].y);
  }

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
