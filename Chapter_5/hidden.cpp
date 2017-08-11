/*
ID: suntobr1
LANG: C++11
TASK: hidden
*/

#include <stdio.h>

#include <string>
#include <vector>

using namespace std;

int equal(vector<int>& rank, int x, int y, int length) {
  return rank[x] == rank[y] && rank[x + length] == rank[y + length];
}

int main(void)
{
  FILE* fin = fopen("hidden.in", "rb");
  FILE* fout = fopen("hidden.out", "wb");

  int length = 0;
  string content;

  char buffer[80];

  fscanf(fin, "%d", &length);
  while (fscanf(fin, "%s", buffer) != EOF) {
    content += buffer;
  }

  content += content;
  content += 'z' + 1;

  vector<int> rank(content.length());
  int rank_count = 27;
  vector<int> count(content.length(), 0);
  count.reserve(rank_count);
  vector<int> suffix(content.length());
  for (int i = 0; i < content.length(); i ++) {
    rank[i] = content[i] - 'a';
    count[rank[i]] ++;
  }
  for (int i = 1; i < rank_count; i ++) {
    count[i] += count[i - 1];
  }
  for (auto i = content.length(); i > 0; i --) {
    suffix[-- count[rank[i - 1]]] = i - 1;
  }

  int curLen = 1;
  vector<int> suffix_second(content.length());
  vector<int> rank_first(content.length());
  do {
    int pos = 0;
    for (auto i = content.length() - curLen; i < content.length(); i ++) {
      suffix_second[pos ++] = i;
    }
    for (int i = 0; i < content.length(); i ++) {
      if (suffix[i] >= curLen) {
        suffix_second[pos ++] = suffix[i] - curLen;
      }
    }

    for (int i = 0; i < rank_count; i ++) {
      count[i] = 0;
    }

    for (int i = 0; i < content.length(); i ++) {
      rank_first[i] = rank[suffix_second[i]];
      count[rank_first[i]] ++;
    }
    for (int i = 1; i < rank_count; i ++) {
      count[i] += count[i - 1];
    }
    for (auto i = content.length(); i > 0; i --) {
      suffix[-- count[rank_first[i - 1]]] = suffix_second[i - 1];
    }

    rank.swap(suffix_second);
    rank[suffix[0]] = 0;
    if (!equal(suffix_second, suffix[0], suffix[1], curLen)) {
      break;
    }
    rank_count = 1;
    for (int i = 1; i < content.size(); i ++) {
      if (equal(suffix_second, suffix[i - 1], suffix[i], curLen)) {
        rank[suffix[i]] = rank_count - 1;
      } else {
        rank[suffix[i]] = rank_count ++;
      }
    }

    curLen *= 2;
  } while (rank_count < content.length());

  fprintf(fout, "%d\n", suffix[0]);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
