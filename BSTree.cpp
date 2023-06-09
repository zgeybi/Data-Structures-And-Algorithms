#include <iostream>

template<typename T>
struct Node {
  T key;
  int height;
  Node* left;
  Node* right;

  Node(T k) {
    key = k;
    height = 1;
    left = nullptr;
    right = nullptr;
  }
};

int GetHeight(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}
int GetBalanceFactor(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return GetHeight(node->left) - GetHeight(node->right);
}
void UpdateHeight(Node* node) {
  node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
}
Node* RotateRight(Node* node) {
  Node* leftchild = node->left;
  Node* rightgrand_child = leftchild->right;
  leftchild->right = node;
  node->left = rightgrand_child;
  UpdateHeight(node);
  UpdateHeight(leftchild);
  return leftchild;
}
Node* RotateLeft(Node* node) {
  Node* rightchild = node->right;
  Node* leftgrand_child = rightchild->left;
  rightchild->left = node;
  node->right = leftgrand_child;
  UpdateHeight(node);
  UpdateHeight(rightchild);
  return rightchild;
}
Node* Rebalance(Node* node, T key) {
  UpdateHeight(node);
  int balance_factor = GetBalanceFactor(node);
  if (balance_factor > 1 && key < node->left->key) {
    return RotateRight(node);
  }
  if (balance_factor < -1 && key > node->right->key) {
    return RotateLeft(node);
  }
  if (balance_factor > 1 && key > node->left->key) {
    node->left = RotateLeft(node->left);
    return RotateRight(node);
  }
  if (balance_factor < -1 && key < node->right->key) {
    node->right = RotateRight(node->right);
    return RotateLeft(node);
  }
  return node;
}
Node* Insert(Node* node, T key) {
  if (node == nullptr) {
    return new Node(key);
  }
  if (key < node->key) {
    node->left = Insert(node->left, key);
  } else if (key > node->key) {
    node->right = Insert(node->right, key);
  } else {
    return node;
  }
  return Rebalance(node, key);
}
int FindMin(Node* node) {
  if (node == nullptr) {
    return -1;
  }
  Node* current = node;
  while (current->left != nullptr) {
    current = current->left;
  }
  return current->key;
}
T FindNext(Node* node, int k) {
  if (node == nullptr) {
    return -1;
  }

  T result = -1;
  while (node != nullptr) {
    if (node->key >= k) {
      result = node->key;
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return result;
}

void DeleteTree(Node* node) {
  if (node == nullptr) {
    return;
  }
  DeleteTree(node->left);
  DeleteTree(node->right);
  delete node;
}

int main() {
  int n;
  std::cin >> n;
  Node<int>* root = nullptr;
  char prev_op = ' ';
  int prev_result = 0;
  for (int i = 0; i < n; i++) {
    char op;
    int num;
    std::cin >> op >> num;
    if (op == '+' && prev_op != '?') {
      root = Insert(root, num);
      prev_op = '+';
    } else if (op == '+' && prev_op == '?') {
      root = Insert(root, (num + prev_result) % 1000000000);
      prev_op = '+';
    } else if (op == '?') {
      int result = FindNext(root, num);
      std::cout << result << std::endl;
      prev_op = '?';
      prev_result = result;
    }
  }

  DeleteTree(root);
  return 0;
}
