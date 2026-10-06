#include <iostream>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BST {
private:
  TreeNode *root;

public:
  BST() : root(nullptr) {}

  void insert(int val) { root = insertRec(root, val); }

  TreeNode *insertRec(TreeNode *node, int val) {
    if (node == nullptr) {
      return new TreeNode(val);
    }

    if (val < node->val) {
      node->left = insertRec(node->left, val);
    } else if (val > node->val) {
      node->right = insertRec(node->right, val);
    }

    return node;
  }

  void inorder() { inorderRec(root); }

  void inorderRec(TreeNode *node) {
    if (node != nullptr) {
      inorderRec(node->left);
      std::cout << node->val << " ";
      inorderRec(node->right);
    }
  }
};