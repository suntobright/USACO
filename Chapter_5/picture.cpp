/*
ID: suntobr1
LANG: C++11
TASK: picture
*/

#include <stdio.h>

#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

class Rect {
  public:
    Rect(short x1, short y1, short x2, short y2)
        : x1(x1), y1(y1), x2(x2), y2(y2) {}

    short x1, y1;
    short x2, y2;
};

class Segment {
  public:
    Segment()
        : begin(0), end(0), depth(0), rectId(-1) {}
    Segment(short begin, short end, short depth, short rectId)
        : begin(begin), end(end), depth(depth), rectId(rectId) {}

    short begin, end;
    short depth;
    short rectId;
};

class SegmentComparator {
  public:
    bool operator() (Segment& a, Segment& b) {
      return a.depth < b.depth;
    }
};

class Point {
  public:
    Point(short value, bool isBegin, bool isTop)
        : value(value), isBegin(isBegin), isTop(isTop) {}

    short value;
    bool isBegin;
    bool isTop;
};

class PointComparator {
  public:
    bool operator() (Point& a, Point& b) {
      return a.value < b.value;
    }
};

int getPointsLength(vector<Point>& points) {
  sort(points.begin(), points.end(), PointComparator());

  int length = 0;
  int curCounts[2] = {0};
  int curStart = 0;
  for (auto it = points.begin(); it != points.end(); it ++) {
    if ((curCounts[0] == 0) ^ (curCounts[1] == 0)) {
      length += it->value - curStart;
    }
    curCounts[it->isTop ? 1 : 0] += it->isBegin ? 1 : -1;
    if ((curCounts[0] == 0) ^ (curCounts[1] == 0)) {
      curStart = it->value;
    }
  }

  return length;
}

int getSegmentsLength(vector<Segment>& segments) {
  sort(segments.begin(), segments.end(), SegmentComparator());

  int length = 0;
  int depth = segments[0].depth;
  vector<Point> points;
  vector<Segment> bottomSegments;
  unordered_map<int, Segment> segmentMap;
  for (auto it = segments.begin(); it != segments.end();) {
    bool isTop = segmentMap.erase(it->rectId) > 0;
    points.push_back(Point(it->begin, true, isTop));
    points.push_back(Point(it->end, false, isTop));
    if (!isTop) {
      bottomSegments.push_back(*it);
    }

    it ++;
    if (it == segments.end() || depth != it->depth) {
      for (auto& pair : segmentMap) {
        points.push_back(Point(pair.second.begin, true, false));
        points.push_back(Point(pair.second.end, false, false));
        points.push_back(Point(pair.second.begin, true, true));
        points.push_back(Point(pair.second.end, false, true));
      }
      length += getPointsLength(points);
      points.clear();
      for (auto& segment : bottomSegments) {
        segmentMap[segment.rectId] = segment;
      }
      bottomSegments.clear();
      depth = it->depth;
    }
  }

  return length;
}

int main(void)
{
  FILE* fin = fopen("picture.in", "rb");
  FILE* fout = fopen("picture.out", "wb");

  int count = 0;
  fscanf(fin, "%d", &count);

  vector<Rect> rects;
  for (int i = 0; i < count; i ++) {
    short x1, y1, x2, y2;
    fscanf(fin, "%hd%hd%hd%hd", &x1, &y1, &x2, &y2);
    rects.push_back(Rect(x1, y1, x2, y2));
  }

  vector<Segment> segments;
  for (vector<Rect>::size_type i = 0; i < rects.size(); i ++) {
    segments.push_back(Segment(rects[i].x1, rects[i].x2, rects[i].y1, i));
    segments.push_back(Segment(rects[i].x1, rects[i].x2, rects[i].y2, i));
  }

  int length = getSegmentsLength(segments);

  segments.clear();
  for (vector<Rect>::size_type i = 0; i < rects.size(); i ++) {
    segments.push_back(Segment(rects[i].y1, rects[i].y2, rects[i].x1, i));
    segments.push_back(Segment(rects[i].y1, rects[i].y2, rects[i].x2, i));
  }

  length += getSegmentsLength(segments);

  fprintf(fout, "%d\n", length);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
