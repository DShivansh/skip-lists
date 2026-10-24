#include <list>
#include <optional>

template <typename K, typename V> struct Node {
  K key;
  V value;
  std::list<Node<K, V>>::iterator down;
};

template <typename K, typename V> class skip_list {
public:
  skip_list();
  auto insert(K key, V value)
      -> void; // if the value is different this will only update the value
  auto get(K key) -> std::optional<V>;
  auto erase(K key) -> void;
};

template <typename K, typename V>
auto skip_list<K, V>::insert(K key, V value) -> void {}

template <typename K, typename V>
auto skip_list<K, V>::get(K key) -> std::optional<V> {
  return std::nullopt;
}

template <typename K, typename V> auto skip_list<K, V>::erase(K key) -> void {}
