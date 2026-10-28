#include <list>
#include <optional>
#include <random>
#include <stack>
#include <vector>

bool flip_coin() {
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

public:
  skip_list();
  auto insert(K key, V value)
      -> void; // if the value is different this will only update the value
  auto get(K key) -> std::optional<V>;
  auto erase(K key) -> void;
};

template <typename K, typename V>
auto skip_list<K, V>::insert(K key, V value) -> void {
  std::stack<std::pair<typename std::list<Node<K, V>>::iterator, int>> st;

  for (int i = static_cast<int>(tower.size()) - 1; i >= 0; i--) {
    auto t_ptr = tower[i].begin(); // list pointer
    while (t_ptr != tower[i].end()) {
      auto t_ptr_nxt = std::next(t_ptr);
      if (t_ptr_nxt->key > key) {
        break;
      }
      t_ptr++;
    }
    st.emplace(t_ptr, i);
  }

  auto prev = st.top();
  while (st.size() > 0) {
    auto [tp, index] = st.top();
    if (!tp->down) {
      Node n{key, value, std::nullopt};
      prev = tower[index].insert(tp, n);
    } else {
      if (flip_coin()) {
        st.pop();
        Node n{key, value, prev};
        prev = tower[index].insert(tp, n);
      } else {
        break;
      }
    }
  }

  if (st.size() == 0 && flip_coin()) {
    Node n{key, value, prev};
    std::list<typename Node<K, V>::iterator> l = {n};
    tower.push_back(l);
  }

}

template <typename K, typename V>
auto skip_list<K, V>::get(K key) -> std::optional<V> {
  return std::nullopt;
}

template <typename K, typename V> auto skip_list<K, V>::erase(K key) -> void {}
