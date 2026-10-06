#include <string>

class TreeNode {
public:
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class TrieNode {
public:
  TrieNode *children[26];
  bool isEndOfWord;
  TrieNode() : isEndOfWord(false) {
    for (int i = 0; i < 26; ++i) {
      children[i] = nullptr;
    }
  }

  void insert(const std::string &word) {
    TrieNode *node = this;
    for (char c : word) {
      int index = c - 'a';
      if (node->children[index] == nullptr) {
        node->children[index] = new TrieNode();
      }
      node = node->children[index];
    }
    node->isEndOfWord = true;
  }

  bool search(const std::string &word) {
    TrieNode *node = this;
    for (char c : word) {
      int index = c - 'a';
      if (node->children[index] == nullptr) {
        return false;
      }
      node = node->children[index];
    }
    return node->isEndOfWord;
  }

  bool startsWith(const std::string &prefix) {
    TrieNode *node = this;
    for (char c : prefix) {
      int index = c - 'a';
      if (node->children[index] == nullptr) {
        return false;
      }
      node = node->children[index];
    }
    return true;
  }
};
