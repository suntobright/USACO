/*
ID: suntobr1
LANG: C++11
TASK: cowcycle
*/

#include <algorithm>
#include <cfloat>
#include <cstdio>
#include <vector>

using namespace std;

void evaluate(vector<int>& fronts,
    vector<int>& rears,
    vector<int>& bestFronts,
    vector<int>& bestRears,
    double& minVariance)
{
  if (fronts.front() * rears.front() * 3 > fronts.back() * rears.back()) {
    return;
  }

  vector<double> values;
  values.reserve(fronts.size() * rears.size());
  for (auto front : fronts) {
    for (auto rear : rears) {
      values.push_back(((double) front) / rear);
    }
  }
  sort(values.begin(), values.end());
  for (size_t i = 0; i < values.size() - 1; i ++) {
    values[i] -= values[i + 1];
  }
  values.pop_back();

  double valueAvg = 0;
  double valueSquareAvg = 0;
  for (auto value : values) {
    valueAvg += value;
    valueSquareAvg += value * value;
  }
  valueAvg /= values.size();
  valueSquareAvg /= values.size();

  double variance = valueSquareAvg - valueAvg * valueAvg;
  if (minVariance > variance) {
    bestFronts = fronts;
    bestRears = rears;
    minVariance = variance;
  }
}

void pick(vector<int>& fronts,
    size_t frontCount,
    int frontBegin,
    int frontEnd,
    vector<int>& rears,
    size_t rearCount,
    int rearBegin,
    int rearEnd,
    vector<int>& bestFronts,
    vector<int>& bestRears,
    double& minVariance)
{
  if (fronts.size() == frontCount && rears.size() == rearCount) {
    evaluate(fronts, rears, bestFronts, bestRears, minVariance);
  } else if (fronts.size() == frontCount) {
    for (int cur = rearBegin;
        cur <= (int) (rearEnd - rearCount + rears.size() + 1);
        cur ++)
    {
      rears.push_back(cur);
      pick(fronts,
          frontCount,
          frontBegin,
          frontEnd,
          rears,
          rearCount,
          cur + 1,
          rearEnd,
          bestFronts,
          bestRears,
          minVariance);
      rears.pop_back();
    }
  } else {
    for (int cur = frontBegin;
        cur <= (int) (frontEnd - frontCount + fronts.size() + 1);
        cur ++)
    {
      fronts.push_back(cur);
      pick(fronts,
          frontCount,
          cur + 1,
          frontEnd,
          rears,
          rearCount,
          rearBegin,
          rearEnd,
          bestFronts,
          bestRears,
          minVariance);
      fronts.pop_back();
    }
  }
}

int main(void)
{
  FILE* fin = fopen("cowcycle.in", "rb");
  FILE* fout = fopen("cowcycle.out", "wb");

  size_t frontCount = 0;
  size_t rearCount = 0;
  int frontBegin = 0;
  int frontEnd = 0;
  int rearBegin = 0;
  int rearEnd = 0;

  fscanf(fin, "%lu%lu", &frontCount, &rearCount);
  fscanf(fin, "%d%d%d%d", &frontBegin, &frontEnd, &rearBegin, &rearEnd);

  vector<int> fronts;
  vector<int> rears;

  vector<int> bestFronts;
  vector<int> bestRears;
  double minVariance = DBL_MAX;

  pick(fronts,
      frontCount,
      frontBegin,
      frontEnd,
      rears,
      rearCount,
      rearBegin,
      rearEnd,
      bestFronts,
      bestRears,
      minVariance);

  fprintf(fout, "%d", bestFronts.front());
  for (size_t i = 1; i < bestFronts.size(); i ++) {
    fprintf(fout, " %d", bestFronts[i]);
  }
  fprintf(fout, "\n");
  fprintf(fout, "%d", bestRears.front());
  for (size_t i = 1; i < bestRears.size(); i ++) {
    fprintf(fout, " %d", bestRears[i]);
  }
  fprintf(fout, "\n");

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
