#include <list>

template <typename K, typename V> struct Node {
  K key;
  V value;
  std::list<Node<K, V>>::iterator down;
};

template <typename K, typename V> class skip_list {
public:
  skip_list();
  auto insert(K key)
      -> void; // if the value is different this will only update the value
  auto get(K key) -> V;
  auto erase(K key) -> void;
};

template <typename K, typename V> auto skip_list<K, V>::insert(K key) -> void {}
