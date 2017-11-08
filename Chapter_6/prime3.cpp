/*
ID: suntobr1
LANG: C++11
TASK: prime3
*/

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

vector<bool> primeFlags(100000, true);
vector<int> primes;

vector<int> primesWithFirstFixedAndNonZeroDigit;
vector<vector<int>> primesWithFirstFifthVaried(100);
vector<vector<int>> primesWithFirstFixedAndThirdVaried(10);
vector<vector<int>> primesWithFirstSecondFourthVaried(1000);
vector<vector<int>> primesWithFirstSecondThirdFourthVaried(10000);

vector<vector<int>> square(5, vector<int>(5, 0));

void crossOutNonPrimes() {
  primeFlags[0] = false;
  primeFlags[1] = false;
  for (int base = 2; base <= sqrt(primeFlags.size()); base ++) {
    if (primeFlags[base]) {
      for (size_t i = base << 1; i < primeFlags.size(); i += base) {
        primeFlags[i] = false;
      }
    }
  }
}

inline int getDigitSum(int prime) {
  int digitSum = 0;
  while (prime) {
    digitSum += prime % 10;
    prime /= 10;
  }
  return digitSum;
}

void crossOutPrimesIfNotMeetDigitSum(int digitSum) {
  for (size_t i = 10000; i < primeFlags.size(); i ++) {
    if (primeFlags[i] && getDigitSum(i) != digitSum) {
      primeFlags[i] = false;
    }
  }
}

void collectPrimes() {
  for (size_t i = 10000; i < primeFlags.size(); i ++) {
    if (primeFlags[i]) {
      primes.push_back(i);
    }
  }
}

void preprocessPrimes(int firstDigit) {
  for (auto prime : primes) {
    if (prime / 10000 == firstDigit
        && (prime / 1000) % 10 != 0
        && (prime / 100) % 10 != 0
        && (prime / 10) % 10 != 0
        && prime % 10 != 0)
    {
      primesWithFirstFixedAndNonZeroDigit.push_back(prime);
    }
    primesWithFirstFifthVaried[
        prime / 10000 * 10 + prime % 10].push_back(prime);
    if (prime / 10000 == firstDigit) {
      primesWithFirstFixedAndThirdVaried[prime / 100 % 10].push_back(prime);
    }
    primesWithFirstSecondFourthVaried[
        prime / 1000 * 10 + prime / 10 % 10].push_back(prime);
    primesWithFirstSecondThirdFourthVaried[prime / 10].push_back(prime);
  }
}

enum FillPart {
  FIRST_ROW,
  FIRST_COLUMN,
  COUNTER_DIAGONAL,
  DIAGONAL,
  SECOND_ROW,
  SECOND_COLUMN,
  FOURTH_ROW,
  FOURTH_COLUMN,
  THIRD_ROW,
  THIRD_COLUMN
};

void fill(FillPart fillPart, vector<string>& results) {
  switch (fillPart) {
  case FIRST_ROW:
    for (auto prime : primesWithFirstFixedAndNonZeroDigit) {
      square[0][1] = (prime / 1000) % 10;
      square[0][2] = (prime / 100) % 10;
      square[0][3] = (prime / 10) % 10;
      square[0][4] = prime % 10;

      fill(FIRST_COLUMN, results);
    }
    break;
  case FIRST_COLUMN:
    for (auto prime : primesWithFirstFixedAndNonZeroDigit) {
      square[1][0] = (prime / 1000) % 10;
      square[2][0] = (prime / 100) % 10;
      square[3][0] = (prime / 10) % 10;
      square[4][0] = prime % 10;

      fill(COUNTER_DIAGONAL, results);
    }
    break;
  case COUNTER_DIAGONAL:
    for (auto prime : primesWithFirstFifthVaried[
        square[4][0] * 10 + square[0][4]])
    {
      square[3][1] = (prime / 1000) % 10;
      square[2][2] = (prime / 100) % 10;
      square[1][3] = (prime / 10) % 10;

      fill(DIAGONAL, results);
    }
    break;
  case DIAGONAL:
    for (auto prime : primesWithFirstFixedAndThirdVaried[square[2][2]]) {
      square[1][1] = (prime / 1000) % 10;
      square[3][3] = (prime / 10) % 10;
      square[4][4] = prime % 10;

      fill(SECOND_ROW, results);
    }
    break;
  case SECOND_ROW:
    for (auto prime : primesWithFirstSecondFourthVaried[
        square[1][0] * 100 + square[1][1] * 10 + square[1][3]])
    {
      square[1][2] = (prime / 100) % 10;
      square[1][4] = prime % 10;

      fill(SECOND_COLUMN, results);
    }
    break;
  case SECOND_COLUMN:
    for (auto prime : primesWithFirstSecondFourthVaried[
        square[0][1] * 100 + square[1][1] * 10 + square[3][1]])
    {
      square[2][1] = (prime / 100) % 10;
      square[4][1] = prime % 10;

      fill(FOURTH_ROW, results);
    }
    break;
  case FOURTH_ROW:
    for (auto prime : primesWithFirstSecondFourthVaried[
        square[3][0] * 100 + square[3][1] * 10 + square[3][3]])
    {
      square[3][2] = (prime / 100) % 10;
      square[3][4] = prime % 10;

      fill(FOURTH_COLUMN, results);
    }
    break;
  case FOURTH_COLUMN:
    for (auto prime : primesWithFirstSecondFourthVaried[
        square[0][3] * 100 + square[1][3] * 10 + square[3][3]])
    {
      square[2][3] = (prime / 100) % 10;
      square[4][3] = prime % 10;

      fill(THIRD_ROW, results);
    }
    break;
  case THIRD_ROW:
    for (auto prime : primesWithFirstSecondThirdFourthVaried[
        square[2][0] * 1000
            + square[2][1] * 100
            + square[2][2] * 10
            + square[2][3]])
    {
      square[2][4] = prime % 10;

      fill(THIRD_COLUMN, results);
    }
    break;
  case THIRD_COLUMN:
    for (auto prime : primesWithFirstSecondThirdFourthVaried[
        square[0][2] * 1000
            + square[1][2] * 100
            + square[2][2] * 10
            + square[3][2]])
    {
      square[4][2] = prime % 10;

      int fifthRowNumber = 0;
      int fifthColumnNumber = 0;
      for (int i = 0; i < 5; i ++) {
        fifthRowNumber *= 10;
        fifthColumnNumber *= 10;

        fifthRowNumber += square[4][i];
        fifthColumnNumber += square[i][4];
      }

      if (primeFlags[fifthRowNumber] && primeFlags[fifthColumnNumber]) {
        string result;
        for (auto& row : square) {
          for (auto digit : row) {
            result += digit + '0';
          }
          result += '\n';
        }

        results.push_back(result);
      }
    }
    break;
  }
}

int main(void)
{
  FILE* fin = fopen("prime3.in", "rb");
  FILE* fout = fopen("prime3.out", "wb");

  int digitSum = 0;
  int firstDigit = 0;
  fscanf(fin, "%d%d", &digitSum, &firstDigit);

  crossOutNonPrimes();
  crossOutPrimesIfNotMeetDigitSum(digitSum);
  collectPrimes();
  preprocessPrimes(firstDigit);

  vector<string> results;
  square[0][0] = firstDigit;
  fill(FIRST_ROW, results);

  sort(results.begin(), results.end());

  if (results.empty()) {
    fprintf(fout, "NONE\n");
  } else {
    fprintf(fout, "%s", results.front().c_str());
    for (size_t i = 1; i < results.size(); i ++) {
      fprintf(fout, "\n%s", results[i].c_str());
    }
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
