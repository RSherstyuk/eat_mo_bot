#include <iostream>
#include <queue>
#include <stack>

class TreeNode {
public:
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BTree {
private:
  TreeNode *root;

public:
  BTree() : root(nullptr) {}

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
  void dfs_stack() {
    if (root == nullptr) {
      return;
    }

    std::stack<TreeNode *> s;
    s.push(root);

    while (!s.empty()) {
      TreeNode *node = s.top();
      s.pop();
      std::cout << node->val << " ";

      if (node->right != nullptr) {
        s.push(node->right);
      }
      if (node->left != nullptr) {
        s.push(node->left);
      }
    }
  }

  void dfs(TreeNode *node) {
    if (node == nullptr) {
      return;
    }

    dfs(node->left);
    std::cout << node->val << " ";
    dfs(node->right);
  }

  void printDFS() { dfs(root); }

  void bfs() {
    if (root == nullptr) {
      return;
    }

    std::queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
      TreeNode *node = q.front();
      q.pop();
      std::cout << node->val << " ";

      if (node->left != nullptr) {
        q.push(node->left);
      }
      if (node->right != nullptr) {
        q.push(node->right);
      }
    }
  }
};

int main() {
  BTree tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(7);
  tree.insert(2);
  tree.insert(4);
  tree.insert(6);
  tree.insert(8);

  std::cout << "DFS (In-order): ";
  tree.printDFS();
  std::cout << std::endl;

  std::cout << "DFS (Using Stack): ";
  tree.dfs_stack();
  std::cout << std::endl;

  std::cout << "BFS: ";
  tree.bfs();
  std::cout << std::endl;

  return 0;
}