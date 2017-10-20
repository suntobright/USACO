/*
ID: suntobr1
LANG: C++11
TASK: vans
*/

#include <cstdio>

#include <string>
#include <vector>

using namespace std;

class BigInteger {
public:
  BigInteger() {}

  BigInteger(int intValue) {
    string temp = to_string(intValue);
    for (auto it = temp.rbegin(); it != temp.rend(); it ++) {
      value.push_back(*it);
    }
  }

  BigInteger operator +(BigInteger& b) {
    BigInteger result;

    auto ait = value.begin();
    auto bit = b.value.begin();
    bool carry = false;

    while (ait != value.end() && bit != b.value.end()) {
      char temp = *ait++ - '0' + *bit++ + carry;
      carry = temp > '9';
      temp -= carry ? 10 : 0;
      result.value.push_back(temp);
    }

    while (ait != value.end()) {
      char temp = *ait++ + carry;
      carry = temp > '9';
      temp -= carry ? 10 : 0;
      result.value.push_back(temp);
    }

    while (bit != b.value.end()) {
      char temp = *bit++ + carry;
      carry = temp > '9';
      temp -= carry ? 10 : 0;
      result.value.push_back(temp);
    }

    if (carry) {
      result.value.push_back('1');
    }

    return result;
  }

  BigInteger operator -(BigInteger& b) {
    BigInteger result;

    auto ait = value.begin();
    auto bit = b.value.begin();
    bool carry = false;

    while (bit != b.value.end()) {
      char temp = *ait++ - (*bit++ - '0') - carry;
      carry = temp < '0';
      temp += carry ? 10 : 0;
      result.value.push_back(temp);
    }

    while (ait != value.end()) {
      char temp = *ait++ - carry;
      carry = temp < '0';
      temp += carry ? 10 : 0;
      result.value.push_back(temp);
    }

    while (result.value.back() == '0') {
      result.value.pop_back();
    }

    return result;
  }

  string toString() {
    string str;
    for (auto it = value.rbegin(); it != value.rend(); it ++) {
      str.push_back(*it);
    }
    return str;
  }

private:
  string value;
};

int main(void)
{
  FILE* fin = fopen("vans.in", "rb");
  FILE* fout = fopen("vans.out", "wb");

  int n = 0;
  fscanf(fin, "%d", &n);

  vector<BigInteger> f(n > 2 ? n + 1 : 3);
  vector<BigInteger> g(n > 2 ? n + 1 : 3);
  f = {0, 0, 2};
  g = {0, 2, 2};
  for (int i = 3; i < n + 1; i ++) {
    f[i] = f[i - 1] + g[i - 1];
    g[i] = f[i - 1] + f[i - 1] + g[i - 1] + g[i - 2] - g[i - 3];
  }

  fprintf(fout, "%s\n", f[n].toString().c_str());

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
