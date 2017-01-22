/*
ID: suntobr1
LANG: C
TASK: heritage
*/

#include <stdio.h>
#include <string.h>

char inorder[32];
char preorder[32];

void findroot(int inpos, int prepos, int len, FILE *out)
{
  int i;

  if (len == 0)
    return;

  for (i = 0; i < len; i ++)
    if (inorder[inpos + i] == preorder[prepos])
      break;

  findroot(inpos, prepos + 1, i, out);
  findroot(inpos + i + 1, prepos + i + 1, len - i - 1, out);

  fprintf(out, "%c", preorder[prepos]);
}

int main()
{
  FILE *in = NULL;
  FILE *out = NULL;

  in = fopen("heritage.in", "rb");
  out = fopen("heritage.out", "wb");

  fscanf(in, "%s", inorder);
  fscanf(in, "%s", preorder);

  findroot(0, 0, strlen(inorder), out);

  fprintf(out, "\n");

  fflush(out);
  fclose(in);
  fclose(out);

  return 0;
}
