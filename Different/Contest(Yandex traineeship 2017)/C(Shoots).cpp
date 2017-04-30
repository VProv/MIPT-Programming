#include <iostream>
#include <iomanip>

using namespace std;
int main() {
  double n;
  double m, k;
  cin >> n >> m >> k;
  double total = n * m;
  double p = 1 / (n * m);
  double q = 1 - 1 / (n * m);
  double mult = 1;
  for (int i = 0; i < k; ++i) {
    mult *= q;
  }
  double result = total - total * mult;
  cout << setprecision(13) << result;
  return 0;
}