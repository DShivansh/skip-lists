#include "skip_lists.hpp"

#include <array>
#include <iostream>
#include <optional>
#include <string_view>

namespace {

int failures = 0;

void expect(skip_list<int, int> &list, int key, std::optional<int> expected,
            std::string_view order = {}, std::string_view phase = {}) {
  const auto actual = list.get(key);
  if (actual != expected) {
    if (!order.empty()) {
      std::cerr << order << " (" << phase << "): ";
    }
    std::cerr << "get(" << key << "): expected ";
    if (expected) {
      std::cerr << *expected;
    } else {
      std::cerr << "no value";
    }
    std::cerr << ", got ";
    if (actual) {
      std::cerr << *actual;
    } else {
      std::cerr << "no value";
    }
    std::cerr << '\n';
    ++failures;
  }
}

void empty() {
  skip_list<int, int> list;
  expect(list, 0, std::nullopt);
}

void single() {
  skip_list<int, int> list;
  list.insert(7, 70);
  expect(list, 7, 70);
}

void missing() {
  skip_list<int, int> list;
  list.insert(10, 100);
  list.insert(30, 300);
  expect(list, 5, std::nullopt);
  expect(list, 20, std::nullopt);
  expect(list, 40, std::nullopt);
  expect(list, 10, 100);
  expect(list, 30, 300);
}

void check_order(std::string_view order, const std::array<int, 5> &keys) {
  skip_list<int, int> list;
  for (int key : keys) {
    list.insert(key, key + 1);
    expect(list, key, key + 1, order, "after insert");
  }
  for (int key : keys) {
    expect(list, key, key + 1, order, "final check");
  }
}

void insertion_orders() {
  check_order("ascending", std::array{10, 20, 30, 40, 50});
  check_order("descending", std::array{50, 40, 30, 20, 10});
  check_order("mixed", std::array{30, 10, 50, 20, 40});
}

void many_keys() {
  skip_list<int, int> list;
  for (int key = 0; key < 100; ++key) {
    list.insert(key, key * 3 + 1);
  }
  for (int key = 0; key < 100; ++key) {
    expect(list, key, key * 3 + 1);
  }
}

} // namespace

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Expected one test case name\n";
    return 2;
  }

  const std::string_view name = argv[1];
  if (name == "empty") {
    empty();
  } else if (name == "single") {
    single();
  } else if (name == "missing") {
    missing();
  } else if (name == "insertion_orders") {
    insertion_orders();
  } else if (name == "many_keys") {
    many_keys();
  } else {
    std::cerr << "Unknown test case: " << name << '\n';
    return 2;
  }
  return failures == 0 ? 0 : 1;
}
