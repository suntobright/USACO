/*
ID: suntobr1
LANG: C++11
TASK: cowxor
*/

#include <stdio.h>

#include <vector>

using namespace std;

class XorNode {
public:
  XorNode() : children{nullptr, nullptr}, firstIndex{-1} {}

  void insert(int xorNumber, int bitPos, int index) {
    if (bitPos < 0) {
      if (firstIndex < 0) {
        firstIndex = index;
      }
    } else {
      int childIndex = (bool) (xorNumber & (1 << bitPos));
      if (!children[childIndex]) {
        children[childIndex] = new XorNode();
      }
      children[childIndex]->insert(xorNumber, bitPos - 1, index);
    }
  }

  int findComplement(int xorNumber, int bitPos) {
    if (bitPos < 0) {
      return firstIndex;
    } else {
      int childIndex = !(xorNumber & (1 << bitPos));
      if (!children[childIndex]) {
        childIndex = !childIndex;
      }
      return children[childIndex]->findComplement(xorNumber, bitPos - 1);
    }
  }

private:
  XorNode* children[2];
  int firstIndex;
};

int main(void)
{
  FILE* fin = fopen("cowxor.in", "rb");
  FILE* fout = fopen("cowxor.out", "wb");

  int count = 0;
  int currentXor = 0;
  vector<int> xors;
  XorNode xorTree;
  fscanf(fin, "%d", &count);
  for (int i = 0; i < count; i ++) {
    int number = 0;
    fscanf(fin, "%d", &number);
    currentXor ^= number;
    xors.push_back(currentXor);
    xorTree.insert(currentXor, 19, i);
  }

  int begin = 0;
  int end = xorTree.findComplement(0, 19);
  int maxValue = xors[end];
  for (int i = 0; i < count - 1; i ++) {
    int index = xorTree.findComplement(xors[i], 19);
    if (index > i) {
      int value = xors[index] ^ xors[i];
      if (value > maxValue || (value == maxValue && index <= end)) {
        maxValue = value;
        begin = i + 1;
        end = index;
      }
    }
  }

  fprintf(fout, "%d %d %d\n", maxValue, begin + 1, end + 1);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
