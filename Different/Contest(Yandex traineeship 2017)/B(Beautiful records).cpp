#include <vector>
#include <string>
#include <iostream>

using namespace std;
int main() {
  string text;
  string result;
  getline(cin, text);
  int size = text.size();
  bool isnewsent = true;
  bool isstart = true;
  int res_size = 0;

  for (int i = 0; i < size; ++i) {
    char c = tolower(text[i]);
    if (c != ' ') {
      if (c != '.') {
        if (isstart) {
          c = toupper(c);
          result += c;
          isstart = false;
          isnewsent = false;
          ++res_size;
          continue;
        }
        if (isnewsent) {
          c = toupper(c);
          isnewsent = false;
          result += ' ';
          ++res_size;
        }
        result += c;
        ++res_size;
      } else {
        if (isstart || result[res_size - 1] == '.') {
          cout << -1;
          return 0;
        }
        else {
          if (result[res_size - 1] == ' ')
            result[res_size - 1] = '.';
          else {
            ++res_size;
            result += '.';
          }
          isnewsent = true;
        }
      }
    } else { // Пробел.
      if (isstart || isnewsent)
        continue;
      if (result[res_size - 1] != ' ') {
        ++res_size;
        result += ' ';
      }
    }
  }
  if (result[res_size - 1] != '.') {
    cout << -1;
    return 0;
  }

  cout << result;
  return 0;
}