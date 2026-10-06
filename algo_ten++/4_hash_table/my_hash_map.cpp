#include <iostream>
#include <vector>

struct Point {
  int x;
  int y;

  Point(int x, int y) : x(x), y(y) {}

  bool operator==(const Point &other) const {
    return x == other.x && y == other.y;
  }
};

template <typename K, typename V> class Node {
public:
  K key;
  V val;
  Node *next;

  Node(K key, V val) : key(key), val(val), next(nullptr) {}
};

template <typename K, typename V> class LinkedList {
public:
  Node<K, V> *head;
  LinkedList() : head(nullptr) {}

  void add(K key, V val) {
    Node<K, V> *current = head;

    while (current != nullptr) {
      if (current->key == key) {
        current->val = val;
        return;
      }
      current = current->next;
    }

    Node<K, V> *new_node = new Node<K, V>(key, val);
    new_node->next = head;
    head = new_node;
  }

  // Возвращает указатель на значение (чтобы можно было вернуть nullptr, если не
  // найдено)
  V *get(K key) {
    Node<K, V> *current = head;
    while (current != nullptr) {
      if (current->key == key) {
        return &(current->val);
      }
      current = current->next;
    }
    return nullptr;
  }
};

// Шаблонная хеш-мапа
template <typename K, typename V> class HashMap {
private:
  std::vector<LinkedList<K, V>> table;
  int size;

public:
  HashMap(int size) : size(size) { table.resize(size); }

  int hash(K key) {
    return key % size; // Подразумевается, что ключ поддерживает оператор %
                       // (например, int)
  }

  void remove(K key) {
    int index = hash(key);
    LinkedList<K, V> &list = table[index];
    Node<K, V> *current = list.head;
    Node<K, V> *prev = nullptr;

    while (current != nullptr) {
      if (current->key == key) {
        if (prev == nullptr) {
          list.head = current->next;
        } else {
          prev->next = current->next;
        }
        delete current;
        return;
      }
      prev = current;
      current = current->next;
    }
  }

  void put(K key, V value) {
    int index = hash(key);
    table[index].add(key, value);
  }

  V *get(K key) {
    int index = hash(key);
    return table[index].get(key);
  }
};

int main() {
  // Создаем мапу, где ключ это int, а значение - объект Point
  HashMap<int, Point> hashMap(10);

  for (int i = 0; i < 100; ++i) {
    Point p(i, i * 2);
    hashMap.put(p.x, p); // Кладём саму точку p по ключу p.x
  }

  for (int i = 0; i < 10; ++i) {
    Point *p = hashMap.get(i);
    if (p != nullptr) {
      std::cout << "Key: " << i << ", Point Value: (" << p->x << ", " << p->y
                << ")" << std::endl;
    }
  }

  return 0;
}