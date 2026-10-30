#include "skip_lists.hpp"
#include <cassert>

int main() {
  skip_list<int, int> sl;
  for (int i = 0; i < 100; i++) {
    sl.insert(i, i + 1);
  }

  for (int i = 0; i < 100; i++) {
    auto out = sl.get(i);
    assert(out == i + 1);
  }

  return 0;
}
