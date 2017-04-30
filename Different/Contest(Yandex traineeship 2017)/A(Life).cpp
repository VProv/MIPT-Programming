#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::cin;

class Lifer {
public:
  Lifer(int n, int m, int k)
      : n_(n + 2), m_(m + 2), k_(k), 
      field_(n + 2, vector<char>(m + 2)), 
      new_field_(n + 2, vector<char>(m + 2)),
      changes_(n + 2, vector<char>(m + 2, 0)) {
    int c;
    for (char i = 0; i < n + 2; ++i)
      for (char j = 0; j < m + 2; ++j) {
        if (i == 0 || j == 0 || i == n + 1 || j == m + 1) {
          field_[i][j] = 0;
        }
        else {
           cin >> c;
           field_[i][j] = c;
        }
      }
  }
  
  void Turn() {
    char st = 0;
    char nst = 0;
    for (char i = 1; i < n_ - 1; ++i)
      for (char j = 1; j < m_ - 1; ++j) {
        st = 0;
        nst = 0;

        if (field_[i][j - 1] == 2) {
          ++st;
        }
        else if (field_[i][j - 1] == 3) {
          ++nst;
        }

        if (field_[i][j + 1] == 2) {
          ++st;
        } else if (field_[i][j + 1] == 3) {
          ++nst;
        }

        if (field_[i + 1][j] == 2) {
          ++st;
        } else if (field_[i + 1][j] == 3) {
          ++nst;
        }

        if (field_[i - 1][j] == 2) {
          ++st;
        } else if (field_[i - 1][j] == 3) {
          ++nst;
        }

        if (st >= 2) {
          if (field_[i][j] != 2)
            ++changes_[i][j];
          new_field_[i][j] = 2;
        }
        else if (st > 0 || nst > 0) {
          if (field_[i][j] != 3)
            ++changes_[i][j];
          new_field_[i][j] = 3;
        }
        else {
          if (field_[i][j] != 1)
            ++changes_[i][j];
          new_field_[i][j] = 1;
        }
      }
    field_.swap(new_field_);
  }

  void Game() {
    for (char i = 0; i < k_; ++i)
      Turn();
    for (char i = 1; i < n_ - 1; ++i) {
      for (char j = 1; j < m_ - 1; ++j) {
        cout << int(changes_[i][j]) << ' ';
      }
      cout << std::endl;
    }
  }

  int n_;
  int m_;
  int k_;
  vector< vector<char> > field_;
  vector< vector<char> > new_field_;
  vector< vector<char> > changes_;
};

int main() {

  int n, m, k;
  cin >> n >> m >> k;
  Lifer solver(n, m, k);
  solver.Game();

  return 0;
}