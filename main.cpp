#include "skip_lists.hpp"
#include <cassert>
#include <iostream>

int main() {
  skip_list<int, int> sl;
  int range = 100;
  for (int i = 0; i < range; i++) {
    // std::cout << "inserting key " << i << std::endl;
    sl.insert(i, i + 1);
  }

  // std::cout << "insertion done " << std::endl;

  for (int i = 0; i < range; i++) {
    // std::cout << "getting the value for key " << i << std::endl;
    auto out = sl.get(i).value();
    // std::cout << "the value got is " << out << std::endl;
    assert(out == i + 1);
  }

  return 0;
}
