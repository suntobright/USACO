/*
ID: suntobr1
LANG: C++11
TASK: fence8
*/

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

bool smallGoFirst(int x, int y) {
  return x < y;
}

bool bigGoFirst(int x, int y) {
  return x > y;
}

bool checkCuttable(vector<int>& rails,
    size_t curIndex,
    size_t lastCutBoard,
    vector<int>& boards,
    int curRemain,
    int maxRemain)
{
  if (curIndex == (size_t) -1) {
    return true;
  }

  size_t start = curIndex + 1 < rails.size()
          && rails[curIndex] == rails[curIndex + 1]
      ? lastCutBoard
      : 0;

  for (size_t i = start; i < boards.size(); i ++) {
    if (boards[i] >= rails[curIndex]) {
      bool isCuttable = true;

      boards[i] -= rails[curIndex];
      if (boards[i] < rails.front()) {
        curRemain += boards[i];
        if (curRemain > maxRemain) {
          isCuttable = false;
        }
      }

      isCuttable = isCuttable && checkCuttable(rails,
          curIndex - 1,
          i,
          boards,
          curRemain,
          maxRemain);
      
      if (boards[i] < rails.front()) {
        curRemain -= boards[i];
      }
      boards[i] += rails[curIndex];

      if (isCuttable) {
        return true;
      }
    }
  }

  return false;
}

int main(void)
{
  FILE* fin = fopen("fence8.in", "rb");
  FILE* fout = fopen("fence8.out", "wb");

  vector<int> boards;
  vector<int> rails;

  int n = 0;
  fscanf(fin, "%d", &n);
  for (int i = 0; i < n; i ++) {
    int board = 0;
    fscanf(fin, "%d", &board);
    boards.push_back(board);
  }
  sort(boards.begin(), boards.end(), bigGoFirst);

  fscanf(fin, "%d", &n);
  for (int i = 0; i < n; i ++) {
    int rail = 0;
    fscanf(fin, "%d", &rail);
    rails.push_back(rail);
  }
  sort(rails.begin(), rails.end(), smallGoFirst);

  while (!boards.empty() && boards.back() < rails.front()) {
    boards.pop_back();
  }

  while (!rails.empty() && (boards.empty() || rails.back() > boards.front())) {
    rails.pop_back();
  }

  int boardTotal = 0;
  for (auto board : boards) {
    boardTotal += board;
  }

  int railTotal = 0;
  for (size_t i = 0; i < rails.size(); i ++) {
    if (railTotal + rails[i] > boardTotal) {
      rails.resize(i);
      break;
    }
    railTotal += rails[i];
  }

  int maxRemain = boardTotal - railTotal;
  while (!rails.empty()) {
    if (checkCuttable(rails, rails.size() - 1, -1, boards, 0, maxRemain)) {
      break;
    }
    maxRemain += rails.back();
    rails.pop_back();
  }

  fprintf(fout, "%lu\n", rails.size());

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
