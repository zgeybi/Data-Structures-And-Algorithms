#include <iostream>
#include <string>
#include <vector>

class Stack {
private:
  std::vector<int> vec[10070];
  int top;

public:
  Stack() { top = -1; }

  bool IsEmpty() { return top == -1; }

  void Push(int val) {
    vec->push_back(val);
    top++;
    std::cout << "ok" << '\n';
  }

  void Pop() {
    if (IsEmpty()) {
      std::cout << "error" << '\n';
      return;
    }
    std::cout << vec->at(top--) << '\n';
    vec->pop_back();
    return;
  }

  int Back() {
    if (IsEmpty()) {
      std::cout << "error" << std::endl;
      return -1;
    }
    return vec->at(top);
  }
  int Size() { return vec->size(); }
  void Clear() {
    vec->clear();
    top = -1;
    std::cout << "ok" << '\n';
  }
};

int main() {
  Stack stack;
  int n;
  std::string input;
  while (true) {
    std::cin >> input;
    if (input == "push") {
      std::cin >> n;
      stack.Push(n);
    } else if (input == "pop") {
      stack.Pop();
    } else if (input == "back") {
      if (stack.Back() == -1) {
        continue;
      }
      std::cout << stack.Back() << '\n';
    } else if (input == "size") {
      std::cout << stack.Size() << '\n';
    } else if (input == "clear") {
      stack.Clear();
    } else if (input == "exit") {
      std::cout << "bye" << '\n';
      break;
    }
  }

  return 0;
}