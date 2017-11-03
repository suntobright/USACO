/*
ID: suntobr1
LANG: C++11
TASK: cryptcow
*/

#include <cstdio>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

bool mayDecrypt(string& encrypted, string& decrypted, string& keyChars) {
  size_t firstKeyCharIndex = encrypted.find_first_of(keyChars);
  if (firstKeyCharIndex == string::npos
      || encrypted[firstKeyCharIndex] != keyChars.front())
  {
    return false;
  }

  size_t lastKeyCharIndex = encrypted.find_last_of(keyChars);
  if (lastKeyCharIndex == string::npos
      || encrypted[lastKeyCharIndex] != keyChars.back())
  {
    return false;
  }

  size_t begin = encrypted.find_first_not_of(keyChars);
  size_t end = encrypted.find_first_of(keyChars, begin);
  while (begin != string::npos && end != string::npos)
  {
    if (decrypted.find(encrypted.substr(begin, end - begin)) == string::npos) {
      return false;
    }

    begin = encrypted.find_first_not_of(keyChars, end);
    end = encrypted.find_first_of(keyChars, begin);
  }
  if (begin != string::npos
      && decrypted.find(encrypted.substr(begin)) == string::npos)
  {
    return false;
  }

  return true;
}

int tryToDecrypt(string& encrypted,
    string& decrypted,
    string& keyChars,
    vector<size_t>& indexes,
    unordered_set<string>& cannotDecryptSet)
{
  if (keyChars.size() == indexes.size()) {
    string current;
    current.reserve(encrypted.size() - keyChars.size());
    current.append(encrypted, 0, indexes[0]);
    current.append(encrypted, indexes[1] + 1, indexes[2] - indexes[1] - 1);
    current.append(encrypted, indexes[0] + 1, indexes[1] - indexes[0] - 1);
    current.append(encrypted, indexes[2] + 1, string::npos);
    if (cannotDecryptSet.find(current) != cannotDecryptSet.end()) {
      return 0;
    }

    if (current == decrypted) {
      return 1;
    } else if (mayDecrypt(current, decrypted, keyChars)) {
      vector<size_t> indexes;
      int encryptTimes = tryToDecrypt(current,
          decrypted,
          keyChars,
          indexes,
          cannotDecryptSet);
      if (encryptTimes > 0) {
        return encryptTimes + 1;
      } else {
        cannotDecryptSet.insert(current);
      }
    }

    return 0;
  } else {
    for (size_t index = encrypted.find_first_of(keyChars[indexes.size()],
            indexes.empty() ? 0 : indexes.back());
        index != string::npos;
        index = encrypted.find_first_of(keyChars[indexes.size()], index + 1))
    {
      indexes.push_back(index);
      int encryptTimes = tryToDecrypt(encrypted,
          decrypted,
          keyChars,
          indexes,
          cannotDecryptSet);
      if (encryptTimes > 0) {
        return encryptTimes;
      }
      indexes.pop_back();
    }

    return 0;
  }
}

int main(void)
{
  FILE* fin = fopen("cryptcow.in", "rb");
  FILE* fout = fopen("cryptcow.out", "wb");

  string decrypted{"Begin the Escape execution at the Break of Dawn"};

  char stringBuffer[80];
  fgets(stringBuffer, sizeof(stringBuffer), fin);
  string encrypted{stringBuffer};
  encrypted.pop_back();

  string keyChars{"COW"};

  bool couldDecrypt = false;
  int encryptTimes = 0;
  unordered_set<string> cannotDecryptSet;
  if (encrypted == decrypted) {
    couldDecrypt = true;
  } else {
    vector<size_t> indexes;
    encryptTimes = tryToDecrypt(encrypted,
        decrypted,
        keyChars,
        indexes,
        cannotDecryptSet);
    couldDecrypt = encryptTimes != 0;
  }

  fprintf(fout, "%d %d\n", (int) (couldDecrypt), encryptTimes);

  fclose(fin);
  fflush(fout);
  fclose(fout);

  return 0;
}
