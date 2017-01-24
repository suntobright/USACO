/*
ID: suntobr1
LANG: C
TASK: lgame
*/

#include <stdio.h>
#include <string.h>

int letterValues[26] = {
    2, 5, 4, 4, 1, 6, 5,
    5, 1, 7, 6, 3, 5, 2,
    3, 5, 7, 2, 1, 2,
    4, 6, 6, 7, 5, 7
};

int n;
char words[40001][8];
int wordValues[40000];
unsigned int wordLetterCounts[40000][4];

char letters[8];
unsigned int letterCounts[4];

int maxValue;
int answerCount;
char answers[40320][9];

int deleteLetters(int pos) {
  letterCounts[0] -= wordLetterCounts[pos][0];
  letterCounts[1] -= wordLetterCounts[pos][1];
  letterCounts[2] -= wordLetterCounts[pos][2];
  letterCounts[3] -= wordLetterCounts[pos][3];
  return ((letterCounts[0] & 0x88888888)
      | (letterCounts[1] & 0x88888888)
      | (letterCounts[2] & 0x88888888)
      | (letterCounts[3] & 0x88888888));
}

void addLetters(int pos) {
  letterCounts[0] += wordLetterCounts[pos][0];
  letterCounts[1] += wordLetterCounts[pos][1];
  letterCounts[2] += wordLetterCounts[pos][2];
  letterCounts[3] += wordLetterCounts[pos][3];
}

int main(void)
{
  FILE* fin = fopen("lgame.in", "rb");
  FILE* fout = fopen("lgame.out", "wb");
  FILE* fdict = fopen("lgame.dict", "rb");

  int i = 0;
  int j = 0;

  while (1) {
    fscanf(fdict, "%s", words[n]);
    if (strcmp(words[n], ".") == 0) {
      break;
    }

    for (i = 0; words[n][i] != '\0'; i++) {
      wordValues[n] += letterValues[words[n][i] - 'a'];
      wordLetterCounts[n][(words[n][i] - 'a') / 8] +=
          1 << (((words[n][i] - 'a') % 8) * 4);
    }
    n++;
  }

  fscanf(fin, "%s", letters);
  for (i = 0; letters[i] != '\0'; i++) {
    letterCounts[(letters[i] - 'a') / 8] +=
        1 << (((letters[i] - 'a') % 8) * 4);
  }

  for (i = 0; i < n; i++) {
    if (deleteLetters(i) == 0) {
      for (j = i; j < n; j++) {
        if (deleteLetters(j) == 0) {
          if (wordValues[i] + wordValues[j] > maxValue) {
            maxValue = wordValues[i] + wordValues[j];
            answerCount = 0;
            strcpy(answers[answerCount], words[i]);
            strcat(answers[answerCount], " ");
            strcat(answers[answerCount], words[j]);
            answerCount++;
          } else if (wordValues[i] + wordValues[j] == maxValue) {
            strcpy(answers[answerCount], words[i]);
            strcat(answers[answerCount], " ");
            strcat(answers[answerCount], words[j]);
            answerCount++;
          }
        }
        addLetters(j);
      }
      if (wordValues[i] > maxValue) {
        maxValue = wordValues[i];
        answerCount = 0;
        strcpy(answers[answerCount++], words[i]);
      } else if (wordValues[i] == maxValue) {
        strcpy(answers[answerCount++], words[i]);
      }
    }
    addLetters(i);
  }

  fprintf(fout, "%d\n", maxValue);
  for (i = 0; i < answerCount; i++) {
    fprintf(fout, "%s\n", answers[i]);
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);
  fclose(fdict);

  return 0;
}
