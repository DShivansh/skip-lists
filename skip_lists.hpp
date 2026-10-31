#pragma once
#include <iostream>
#include <list>
#include <optional>
#include <random>
#include <stack>
#include <vector>

inline bool flip_coin() {
  // return true in case of heads and false in case of tails
  std::random_device rd;
  std::mt19937 gen(rd());

  std::bernoulli_distribution coin(0.5);
  return coin(gen);
}

template <typename K, typename V> struct Node {
  K key;
  V value;
  std::optional<typename std::list<Node<K, V>>::iterator> down;
};

template <typename K, typename V> class skip_list {
  std::vector<std::list<Node<K, V>>> tower;

  auto get_list_iterator(K key) -> std::optional<std::pair<typename std::list<Node<K, V>>::iterator, int>> {

    std::optional<typename std::list<Node<K, V>>::iterator> start = tower.back().begin();
    // std::cout << "key is " << key << std::endl;
    int index = tower.size() - 1;
    while (start && index >= 0) {
      // std::cout << "index is " << index << " start is " << start.value()->key << std::endl;

      if (start.value()->key == key) {
        // std::cout << "got the key " << std::endl;
        return std::pair{start.value(), index};
      } else if (start.value()->key > key) {
        // std::cout << "entered here in the else if block " << std::endl;
        index--;
        // std::cout << "new index is " << index << std::endl;
        if (index >= 0) {
          start = tower[index].begin();
          // std::cout << "new start is " << start.value()->key << std::endl;
        }
      } else {
        auto nxt = std::next(start.value());
        if ((nxt->key) > key || nxt == tower[index].end()) {
          start = start.value()->down;
          index -= 1;
        } else {
          start = nxt;
        }
      }
    }
    return std::nullopt;
  }

public:
  auto insert(K key, V value) -> void; // if the value is different this will only update the value
  auto get(K key) -> std::optional<V>;
  auto erase(K key) -> void;
};

template <typename K, typename V> auto skip_list<K, V>::insert(K key, V value) -> void {
  std::stack<std::pair<typename std::list<Node<K, V>>::iterator, int>> st;

  if (tower.size() > 0) {
    std::optional<typename std::list<Node<K, V>>::iterator> t_ptr = tower.back().begin();
    int i = static_cast<int>(tower.size()) - 1;
    while (i >= 0) {
      // std::cout << "i is " << i << std::endl;
      while (true) {
        // std::cout << "t_ptr is " << t_ptr.value()->key << std::endl;
        auto t_ptr_nxt = std::next(t_ptr.value());
        if (t_ptr_nxt == tower[i].end() || t_ptr_nxt->key > key) {
          // std::cout << "entering the if block inside the while " << std::endl;
          // std::cout << "t_ptr is " << t_ptr.value()->key << std::endl;
          if (t_ptr_nxt != tower[i].end()) {
            // std::cout << "t_ptr_nxt is " << t_ptr_nxt->key << std::endl;
          }
          st.emplace(t_ptr.value(), i);
          t_ptr = t_ptr.value()->down;
          break;
        }
        t_ptr = t_ptr_nxt;
      }
      i--;
    }
  }

  // std::cout << "got out of while loop " << std::endl;
  std::optional<typename std::list<Node<K, V>>::iterator> prev = std::nullopt;

  while (st.size() > 0) {
    auto [tp, index] = st.top();
    // std::cout << "index got is " << index << std::endl;
    if (!tp->down) {
      // std::cout << "at the base " << std::endl;
      Node n{key, value, std::nullopt};
      if (tp == tower[index].end()) {
        prev = tower[index].insert(tp, n);
      } else {
        prev = tower[index].insert(std::next(tp), n);
      }
    } else {
      if (flip_coin()) {
        Node n{key, value, prev};
        if (tp == tower[index].end()) {
          prev = tower[index].insert(tp, n);
        } else {
          prev = tower[index].insert(std::next(tp), n);
        }
      } else {
        break;
      }
    }
    st.pop();
  }

  if ((st.size() == 0 && flip_coin()) || (tower.size() == 0)) {
    Node n{key, value, prev};
    std::list<Node<K, V>> l = {n};
    tower.push_back(l);
  }
  // std::cout << std::endl;
}

template <typename K, typename V> auto skip_list<K, V>::get(K key) -> std::optional<V> {
  auto iterator = get_list_iterator(key);
  if (iterator) {
    auto [it, index] = iterator.value();
    return it->value;
  }
  return std::nullopt;
}

template <typename K, typename V> auto skip_list<K, V>::erase(K key) -> void {
  auto iterator = get_list_iterator(key);
  if (iterator) {
    auto [it, index] = iterator.value();
    while (it && it->down) {
      auto nxt = it->down;
      tower[index].erase(it);
      index -= 1;
      it = nxt;
    }
  }
}

