/*
ID: suntobr1
LANG: C++11
TASK: fence3
*/

#include <cfloat>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

class Point;
class Scalar {
  friend double operator*(Scalar s1, Scalar s2);
  friend Scalar operator*(Scalar s, double ratio);
  friend Point operator+(Point p, Scalar s);
public:
  Scalar(double x, double y) : x(x), y(y) {}

  double length() {
    return sqrt(x * x + y * y);
  }
private:
  double x, y;
};

double operator*(Scalar s1, Scalar s2) {
  return s1.x * s2.x + s1.y * s2.y;
}

Scalar operator*(Scalar s, double ratio) {
  return Scalar(s.x * ratio, s.y * ratio);
}

class Segment;
class Point {
  friend Scalar operator-(Point p1, Point p2);
  friend Point operator+(Point p, Scalar s);
public:
  Point(double x, double y) : x(x), y(y) {}

  double distanceFrom(Segment& segment);

  double getX() {return x;}
  double getY() {return y;}
private:
  double x, y;
};

Scalar operator-(Point p1, Point p2) {
  return Scalar(p1.x - p2.x, p1.y - p2.y);
}

Point operator+(Point p, Scalar s) {
  return Point(p.x + s.x, p.y + s.y);
}

class Segment {
  friend double Point::distanceFrom(Segment& segment);
public:
  Segment(double x1, double y1, double x2, double y2)
      : p1(x1, y1),
        p2(x2, y2) {}
  Segment(Point p1, Point p2) : p1(p1), p2(p2) {}

  double length() {
    return (p2 - p1).length();
  }
private:
  Point p1, p2;
};

double Point::distanceFrom(Segment& segment) {
  double cross = (segment.p2 - segment.p1) * (*this - segment.p1);
  if (cross <= 0) {
    return Segment(segment.p1, *this).length();
  }

  double ratio = cross / pow(segment.length(), 2);
  if (ratio >= 1) {
    return Segment(segment.p2, *this).length();
  }

  return Segment(segment.p1 + (segment.p2 - segment.p1) * ratio, *this).length();
}

int main(void)
{
  FILE* fin = fopen("fence3.in", "rb");
  FILE* fout = fopen("fence3.out", "wb");

  int segmentCount = 0;
  fscanf(fin, "%d", &segmentCount);

  vector<Segment> segments;
  for (int i = 0; i < segmentCount; i ++) {
    int x1, y1, x2, y2;
    fscanf(fin, "%d%d%d%d", &x1, &y1, &x2, &y2);
    segments.push_back(Segment(x1, y1, x2, y2));
  }

  Point bestPoint(50, 50);
  double minTotal = 0;
  for (auto& segment : segments) {
    minTotal += bestPoint.distanceFrom(segment);
  }

  vector<Scalar> directions{{0.1, 0}, {-0.1, 0}, {0, 0.1}, {0, -0.1}};
  while (true) {
    size_t i = 0;
    for (i = 0; i < directions.size(); i ++) {
      Point curPoint = bestPoint + directions[i];
      double curTotal = 0;
      for (auto& segment : segments) {
        curTotal += curPoint.distanceFrom(segment);
      }

      if (minTotal > curTotal) {
        minTotal = curTotal;
        bestPoint = curPoint;
        break;
      }
    }

    if (i == directions.size()) {
      break;
    }
  }

  fprintf(fout, "%.1lf %.1lf %.1lf\n", bestPoint.getX(), bestPoint.getY(), minTotal);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
