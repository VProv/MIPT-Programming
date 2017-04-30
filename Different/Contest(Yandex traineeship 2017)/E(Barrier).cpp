#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
using std::vector;

// В каждой вершине ее время.
class Solver {
public:
  Solver(int size) 
      :data_(size, 0) {}
  // В дате храним время окончания блокировки.
  // In fact this is disjunction.
  bool sum(int vertex, int l_segment, int r_segment, int left, int right, int time) {
    // На нее стоит блокировка.
    if (left > right) {
      return false;
    }
    if (left == l_segment && right == r_segment) {
      if (data_[vertex] > time)
        // Мы закрыты.
        return true;
      else {
        // Открыты.
        return false;
      }
    }
    if (l_segment <= left && r_segment >= right && data_[vertex] > time)
      return true;
    int middle = (l_segment + r_segment) / 2;
    return sum(vertex * 2, l_segment, middle, left, std::min<int>(right, middle), time) ||
      sum(vertex * 2 + 1, middle + 1, r_segment, std::max<int>(left, middle + 1), right, time);
  }

  void update(int vertex, int l_segment, int r_segment, int left, int right, int time) {
    if (left > right)
      return;
    if (l_segment == left && r_segment == right) {
      data_[vertex] = std::max<int>(data_[vertex], time);
    }
    else {
      int middle = (l_segment + r_segment) / 2;
      update(vertex * 2, l_segment, middle, left, std::min<int>(middle, right), time);
      update(vertex * 2 + 1, middle + 1, r_segment, std::max<int>(left, middle + 1), right, time);
    }
  }

  vector<int> data_;
};

class Solver2 {
public:
  Solver2(int size)
    :data_(size, 0) {}
  // В дате храним время окончания блокировки.
  // In fact this is disjunction.
  bool sum(int vertex, int l_segment, int r_segment, int left, int right, int time) {
    // На нее стоит блокировка.
    if (left > right) {
      return false;
    }
    if (left == l_segment && right == r_segment) {
      if (data_[vertex] > time)
        // Мы закрыты.
        return true;
      else {
        // Открыты.
        return false;
      }
    }
    int middle = (l_segment + r_segment) / 2;
    return sum(vertex * 2, l_segment, middle, left, std::min<int>(right, middle), time) ||
      sum(vertex * 2 + 1, middle + 1, r_segment, std::max<int>(left, middle + 1), right, time);
  }

  // В каждой вершине сверху проставляем максимум.
  void update(int vertex, int l_segment, int r_segment, int left, int right, int time) {
    if (left > right)
      return;
    data_[vertex] = std::max<int>(data_[vertex], time);
    if (l_segment == left && r_segment == right) {
      data_[vertex] = std::max<int>(data_[vertex], time);
    } else {
      int middle = (l_segment + r_segment) / 2;
      update(vertex * 2, l_segment, middle, left, std::min<int>(middle, right), time);
      update(vertex * 2 + 1, middle + 1, r_segment, std::max<int>(left, middle + 1), right, time);
    }
  }

  vector<int> data_;
};

using std::cin;
using std::cout;
using std::endl;

int main() {
  int n, m;
  cin >> n >> m;
  Solver tree(n * 4);
  Solver2 tree2(n * 4);
  unsigned int two_power = 1;
  while (two_power < n) {
    two_power *= 2;
  }
  unsigned int s, l, r, d;
  for (int i = 0; i < m; ++i) {
    cin >> s >> l >> r >> d;
    --l;
    --r;
    // s - current time.
    // Disable blocks

    if (!tree.sum(1, 0, two_power - 1, l, r, s) && !tree2.sum(1, 0, two_power - 1, l, r, s)) {
      cout << "Yes" << endl;
      tree.update(1, 0, two_power - 1, l, r, s + d);
      tree2.update(1, 0, two_power - 1, l, r, s + d);
    } else {
      cout << "No" << endl;
    }
  }

  return 0;
}