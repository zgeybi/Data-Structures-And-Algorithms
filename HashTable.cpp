#include <iostream>

struct Node {
  int data;
  Node* left;
  Node* right;

  Node(int value) : data(value), left(nullptr), right(nullptr) {}
};
class Set {
 private:
  Node* root_;
  Node* InsertNode(Node* root, int value) {
    if (root == nullptr) {
      return new Node(value);
    }
    if (value < root->data) {
      root->left = InsertNode(root->left, value);
    } else if (value > root->data) {
      root->right = InsertNode(root->right, value);
    }

    return root;
  }

  void Clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    Clear(node->left);
    Clear(node->right);
    delete node;
    node = nullptr;
  }

  bool SearchNode(Node* root, int value) {
    if (root == nullptr) {
      return false;
    }
    if (value == root->data) {
      return true;
    }
    if (value < root->data) {
      return SearchNode(root->left, value);
    }
    return SearchNode(root->right, value);
  }

 public:
  Set() : root_(nullptr) {}
  ~Set() { Clear(root_); }

  void Add(int value) { root_ = InsertNode(root_, value); }

  void Remove(int value) { root_ = RemoveNode(root_, value); }

  bool Contains(int value) { return SearchNode(root_, value); }

 private:
  Node* FindMinNode(Node* node) {
    if (node->left == nullptr) {
      return node;
    }

    return FindMinNode(node->left);
  }

  Node* RemoveNode(Node* root, int value) {
    if (root == nullptr) {
      return nullptr;
    }

    if (value < root->data) {
      root->left = RemoveNode(root->left, value);
    } else if (value > root->data) {
      root->right = RemoveNode(root->right, value);
    } else {
      if (root->left == nullptr && root->right == nullptr) {
        delete root;
        root = nullptr;
      } else if (root->left == nullptr) {
        Node* temp = root;
        root = root->right;
        delete temp;
      } else if (root->right == nullptr) {
        Node* temp = root;
        root = root->left;
        delete temp;
      } else {
        Node* min_node = FindMinNode(root->right);
        root->data = min_node->data;
        root->right = RemoveNode(root->right, min_node->data);
      }
    }
    return root;
  }
};

int main() {
  int num_queries;
  std::cin >> num_queries;

  Set my_set;

  for (int i = 0; i < num_queries; ++i) {
    char query;
    int num;
    std::cin >> query >> num;

    if (query == '+') {
      my_set.Add(num);
    } else if (query == '-') {
      my_set.Remove(num);
    } else if (query == '?') {
      if (my_set.Contains(num)) {
        std::cout << "YES" << '\n';
      } else {
        std::cout << "NO" << '\n';
      }
    }
  }

  return 0;
}
