/*
ID: suntobr1
LANG: C++
TASK: window
*/

#include <stdio.h>

#include <algorithm>
#include <list>

using namespace std;

class Rect {
public:
  Rect() : x1(0), y1(0), x2(0), y2(0) {}
  Rect(int x1, int y1, int x2, int y2)
      : x1(x1), y1(y1), x2(x2), y2(y2) {}

  int area() {
    return (x2 - x1) * (y2 - y1);
  }

  list<Rect> getVisible(Rect& top) {
    list<Rect> visibles;

    if (top.x1 > x1) {
      visibles.push_back(Rect(x1, y1, min(top.x1, x2), y2));
    }
    if (top.x2 < x2) {
      visibles.push_back(Rect(max(top.x2, x1), y1, x2, y2));
    }
    int left = max(top.x1, x1);
    int right = min(top.x2, x2);
    if (left < right) {
      if (top.y1 > y1) {
        visibles.push_back(Rect(left, y1, right, min(top.y1, y2)));
      }
      if (top.y2 < y2) {
        visibles.push_back(Rect(left, max(top.y2, y1), right, y2));
      }
    }

    return visibles;
  }

private:
  int x1, y1;
  int x2, y2;
};

class Window {
public:
  Window(char id, Rect rect)
      : id(id),
        rect(rect)
  {}

  char getId() {
    return id;
  }

  Rect& getRect() {
    return rect;
  }

private:
  char id;
  Rect rect;
};

FILE* fin;
FILE* fout;

list<Window> windows;
list<Rect> rects;

void create() {
  char id;
  int x1, y1, x2, y2;
  fscanf(fin, "(%c,%d,%d,%d,%d)\n", &id, &x1, &y1, &x2, &y2);

  windows.push_back(
      Window(id, Rect(min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2))));
}

void top() {
  char id;
  fscanf(fin, "(%c)\n", &id);

  list<Window>::iterator iter = windows.begin();
  while (iter->getId() != id) {
    iter ++;
  }

  windows.push_back(*iter);
  windows.erase(iter);
}

void bottom() {
  char id;
  fscanf(fin, "(%c)\n", &id);

  list<Window>::iterator iter = windows.begin();
  while (iter->getId() != id) {
    iter ++;
  }

  windows.push_front(*iter);
  windows.erase(iter);
}

void destroy() {
  char id;
  fscanf(fin, "(%c)\n", &id);

  list<Window>::iterator iter = windows.begin();
  while (iter->getId() != id) {
    iter ++;
  }
  windows.erase(iter);
}

void cover(Rect& top) {
  int size = rects.size();
  for (int i = 0; i < size; i ++) {
    Rect rect = rects.front();
    rects.pop_front();

    list<Rect> visibles = rect.getVisible(top);

    for (list<Rect>::iterator iter = visibles.begin();
        iter != visibles.end();
        iter ++) {
      rects.push_back(*iter);
    }
  }
}

void show() {
  char id;
  fscanf(fin, "(%c)\n", &id);

  list<Window>::iterator iter = windows.begin();
  while (iter->getId() != id) {
    iter ++;
  }

  int originArea = iter->getRect().area();

  rects.push_back(iter->getRect());
  iter ++;

  while (iter != windows.end()) {
    cover(iter->getRect());
    iter ++;
  }

  int visibleArea = 0;
  for (list<Rect>::iterator it = rects.begin(); it != rects.end(); it ++) {
    visibleArea += it->area();
  }
  rects.clear();

  fprintf(fout, "%.3lf\n", ((double) visibleArea) / originArea * 100);
}

int main(void)
{
  char op;

  fin = fopen("window.in", "rb");
  fout = fopen("window.out", "wb");

  while (fscanf(fin, "%c", &op) != EOF) {
    switch (op) {
      case 'w':
        create();
        break;
      case 't':
        top();
        break;
      case 'b':
        bottom();
        break;
      case 'd':
        destroy();
        break;
      case 's':
        show();
        break;
    }
  }

  windows.clear();

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
