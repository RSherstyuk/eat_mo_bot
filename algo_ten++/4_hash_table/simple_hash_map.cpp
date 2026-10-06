#include <vector>

struct Node {
  int key;
  int value;
  Node *next;

  Node(int k, int v) : key(k), value(v), next(nullptr) {}
};

struct LinkedList {
  Node *head;

  LinkedList() : head(nullptr) {}

  void add(int key, int value) {
    Node *current = head;

    while (current != nullptr) {
      if (current->key == key) {
        current->value = value;
        return;
      }
      current = current->next;
    }

    Node *new_node = new Node(key, value);
    new_node->next = head;
    head = new_node;
  }

  int *get(int key) {
    Node *current = head;
    while (current != nullptr) {
      if (current->key == key) {
        return &(current->value);
      }
      current = current->next;
    }
    return nullptr;
  }

  Node *removeMiddleNode(Node *head) {
    if (head == nullptr || head->next == nullptr) {
      delete head;
      return nullptr;
    }

    Node *slow = head;
    Node *fast = head;
    Node *prev = nullptr;

    while (fast != nullptr && fast->next != nullptr) {
      fast = fast->next->next;
      prev = slow;
      slow = slow->next;
    }

    prev->next = slow->next;
    delete slow;

    return head;
  }

  Node *reverseList(Node *head) {
    Node *prev = nullptr;
    Node *current = head;
    Node *next = nullptr;

    while (current != nullptr) {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
    }

    return prev;
  }
};

class HashMap {
private:
  std::vector<LinkedList> table;
  int size;

public:
  HashMap(int size) : size(size) { table.resize(size); }

  int hash(int key) { return key % size; }

  void remove(int key) {
    int index = hash(key);
    LinkedList &list = table[index];
    Node *current = list.head;
    Node *prev = nullptr;

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

  void put(int key, int value) {
    int index = hash(key);
    LinkedList &list = table[index];
    list.add(key, value);
  }

  int *get(int key) {
    int index = hash(key);
    LinkedList &list = table[index];
    return list.get(key);
  }
};