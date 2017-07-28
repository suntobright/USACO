/*
ID: suntobr1
LANG: C
TASK: charrec
*/

#include <stdio.h>

char chars[] = " abcdefghijklmnopqrstuvwxyz";
int fontLines[27][20];

int textLineCount;
int textLines[1201];

int minCorruptions[1201];
int bestCharLineCounts[1201];

int minCharCorruptions[1201][3];
char bestChars[1201][3];

int lineCorruptions[1201][27][20];

char text[64];
int textLength;

int binaryStrToInt(const char* str) {
  int result = 0;
  while (*str) {
    result <<= 1;
    result |= (*str ++) - '0';
  }
  return result;
}

int getOneBitCount(int value) {
  int tmp = value - ((value >> 1) & 03333333) - ((value >> 2) & 01111111);
  return ((tmp + (tmp >> 3)) & 03070707) % 63;
}

int getCorruption(int textLineNumber, int charIndex, int fontLineIndex) {
  if (lineCorruptions[textLineNumber][charIndex][fontLineIndex] != -1) {
    return lineCorruptions[textLineNumber][charIndex][fontLineIndex];
  }

  lineCorruptions[textLineNumber][charIndex][fontLineIndex] = getOneBitCount(
      textLines[textLineNumber] ^ fontLines[charIndex][fontLineIndex]
  );
  return lineCorruptions[textLineNumber][charIndex][fontLineIndex];
}

void pickBestChar(int textLineNumber, int charLineCount) {
  int minCorruption = 0x7FFFFFFF;
  char bestChar = '?';

  int charIndex = 0;
  int pickedLine = 0;

  int i;
  int j;

  if (bestChars[textLineNumber][charLineCount - 19] != '?') {
    return;
  }

  for (charIndex = 0; charIndex < 27; charIndex ++) {
    if (charLineCount == 19) {
      for (pickedLine = 0; pickedLine < 20; pickedLine ++) {
        int corruption = 0;
        for (i = 0, j = 0; i < 20; i ++) {
          if (i == pickedLine) {
            continue;
          }
          corruption += getCorruption(textLineNumber + j, charIndex, i);
          j ++;
        }
        if (minCorruption > corruption && corruption <= charLineCount * 6) {
          minCorruption = corruption;
          bestChar = chars[charIndex];
        }
      }
    } else if (charLineCount == 20) {
      int corruption = 0;
      for (i = 0; i < 20; i ++) {
        corruption += getCorruption(textLineNumber + i, charIndex, i);
      }
      if (minCorruption > corruption && corruption <= charLineCount * 6) {
        minCorruption = corruption;
        bestChar = chars[charIndex];
      }
    } else if (charLineCount == 21) {
      for (pickedLine = 0; pickedLine < 20; pickedLine ++) {
        int corruption = 0;
        for (i = 0, j = 0; i < 20; i ++, j ++) {
          corruption += getCorruption(textLineNumber + j, charIndex, i);
          if (i == pickedLine) {
            j ++;
            corruption += getCorruption(textLineNumber + j, charIndex, i);
          }
        }
        if (minCorruption > corruption && corruption <= charLineCount * 6) {
          minCorruption = corruption;
          bestChar = chars[charIndex];
        }
      }
    }
  }

  minCharCorruptions[textLineNumber][charLineCount - 19] = minCorruption;
  bestChars[textLineNumber][charLineCount - 19] = bestChar;
}

void getMinCorruption(int textLineNumber) {
  int charLineCount = 0;
  int minCorruption = 0x7FFFFFFF;

  if (minCorruptions[textLineNumber] != -1) {
    return;
  }

  for (charLineCount = 19;
      charLineCount <= 21 && charLineCount <= textLineNumber;
      charLineCount ++) {
    int prevTextLineNumber = textLineNumber - charLineCount;
    getMinCorruption(prevTextLineNumber);
    if (prevTextLineNumber == 0
        || bestCharLineCounts[prevTextLineNumber] != 0) {
      pickBestChar(prevTextLineNumber, charLineCount);
      if (bestChars[prevTextLineNumber][charLineCount - 19] != '?') {
        int corruption = minCorruptions[prevTextLineNumber]
            + minCharCorruptions[prevTextLineNumber][charLineCount - 19];

        if (minCorruption > corruption) {
          minCorruption = corruption;
          bestCharLineCounts[textLineNumber] = charLineCount;
        }
      }
    }
  }

  minCorruptions[textLineNumber] = minCorruption;
}

int main(void)
{
  FILE* fin = fopen("charrec.in", "rb");
  FILE* fout = fopen("charrec.out", "wb");

  FILE* ffont = fopen("font.in", "rb");

  char buffer[21];

  int i;
  int j;
  int k;

  fscanf(ffont, "%s", buffer);
  for (i = 0; i < 27; i ++) {
    for (j = 0; j < 20; j ++) {
      fscanf(ffont, "%s", buffer);
      fontLines[i][j] = binaryStrToInt(buffer);
    }
  }

  fclose(ffont);

  fscanf(fin, "%d", &textLineCount);
  for (i = 0; i < textLineCount; i ++) {
    fscanf(fin, "%s", buffer);
    textLines[i] = binaryStrToInt(buffer);
  }

  for (i = 0; i <= textLineCount; i ++) {
    minCorruptions[i] = -1;
    for (j = 0; j < 3; j ++) {
      bestChars[i][j] = '?';
    }
    for (j = 0; j < 27; j ++) {
      for (k = 0; k < 20; k ++) {
        lineCorruptions[i][j][k] = -1;
      }
    }
  }
  minCorruptions[0] = 0;

  getMinCorruption(textLineCount);

  if (bestCharLineCounts[textLineCount]) {
    for (i = textLineCount; i > 0;) {
      int charLineCount = bestCharLineCounts[i];
      text[textLength ++] = bestChars[i - charLineCount][charLineCount - 19];
      i -= charLineCount;
    }
    for (i = textLength - 1; i >= 0; i --) {
      fprintf(fout, "%c", text[i]);
    }
    fprintf(fout, "\n");
  } else {
    fprintf(stderr, "Oops!\n");
  }

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
