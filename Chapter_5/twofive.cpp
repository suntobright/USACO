/*
ID: suntobr1
LANG: C++11
TASK: twofive
*/

#include <stdio.h>

#include <unordered_map>

using namespace std;

unordered_map<int, int> countMap;

int getKey(int* positions) {
  int key = 0;
  for (int i = 0; i < 5; i ++) {
    key <<= 3;
    key |= positions[i];
  }
  return key;
}

int getCountByPositions(int* positions) {
  int key = getKey(positions);

  if (countMap.count(key) != 0) {
    return countMap[key];
  }

  int count = 0;
  if (key == 055555) {
    count = 1;
  } else {
    for (int i = 0; i < 5; i ++) {
      if (positions[i] < (i == 0 ? 5 : positions[i - 1])) {
        positions[i] ++;
        count += getCountByPositions(positions);
        positions[i] --;
      }
    }
  }

  countMap[key] = count;
  return count;
}

int getCountByWord(char* word, int wordLength, char curChar, int* positions) {
  int count = 0;
  for (int i = 0; i < 5; i ++) {
    if (positions[i] < (i == 0 ? 5 : positions[i - 1])) {
      int charPos = 5 * i + positions[i];
      if (charPos >= wordLength || word[charPos] == curChar) {
        positions[i] ++;
        if (charPos >= wordLength) {
          count += getCountByWord(word, wordLength, curChar + 1, positions);
        } else {
          int length = positions[0];
          for (int j = 1; j < 5 && positions[j - 1] == 5; j ++) {
            length += positions[j];
          }
          if (length >= wordLength) {
            count += getCountByPositions(positions);
          } else {
            count += getCountByWord(word, wordLength, curChar + 1, positions);
          }
        }
        positions[i] --;
      }
    }
  }

  return count;
}

int main(void)
{
  FILE* fin = fopen("twofive.in", "rb");
  FILE* fout = fopen("twofive.out", "wb");

  char command = 0;
  fscanf(fin, "%c\n", &command);
  if (command == 'N') {
    int number = 0;
    fscanf(fin, "%d", &number);

    char word[26] = {0};
    bool used[25] = {false};
    for (int i = 0; i < 25; i ++) {
      for (int j = 0; j < 25; j ++) {
        if (!used[j]) {
          used[j] = true;
          word[i] = 'A' + j;

          int positions[5] = {0};
          int count = getCountByWord(word, i + 1, 'A', positions);
          if (number <= count) {
            break;
          }
          number -= count;

          used[j] = false;
        }
      }
    }

    fprintf(fout, "%s\n", word);
  } else if (command == 'W') {
    char targetWord[26] = {0};
    fscanf(fin, "%s", targetWord);

    int number = 1;
    char word[26] = {0};
    bool used[25] = {false};
    for (int i = 0; i < 25; i ++) {
      for (int j = 0; j < targetWord[i] - 'A'; j ++) {
        if (!used[j]) {
          used[j] = true;
          word[i] = 'A' + j;

          int positions[5] = {0};
          number += getCountByWord(word, i + 1, 'A', positions);

          used[j] = false;
        }
      }
      word[i] = targetWord[i];
      used[targetWord[i] - 'A'] = true;
    }
    fprintf(fout, "%d\n", number);
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
