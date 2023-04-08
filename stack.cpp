#include <iostream>
#include <string>
#include <vector>

template <typename T>
class Stack {
 private:
  std::vector<T> vec;
  T top_;

 public:
  Stack() { top_ = -1; }

  bool IsEmpty() { return top_ == -1; }

  void Push(int val) {
    vec.push_back(val);
    top_++;
  }

  void Pop() {
    std::cout << vec.at(top_--) << '\n';
    vec.pop_back();
    return;
  }

  int Back() { return vec.at(top_); }
  int Size() { return vec.size(); }
  void Clear() {
    vec.clear();
    top_ = -1;
  }
};

int main() {
  Stack<int> stack;
  int n;
  std::string input;
  while (true) {
    std::cin >> input;
    if (input == "push") {
      std::cin >> n;
      stack.Push(n);
      std::cout << "ok" << '\n';
    } else if (input == "pop") {
      if (stack.IsEmpty()) {
        std::cout << "error" << '\n';
        continue;
      } else {
        stack.Pop();
      }
    } else if (input == "back") {
      if (stack.IsEmpty()) {
        std::cout << "error" << std::endl;
        continue;
      } else {
        std::cout << stack.Back() << '\n';
      }
    } else if (input == "size") {
      std::cout << stack.Size() << '\n';
    } else if (input == "clear") {
      stack.Clear();
      std::cout << "ok" << '\n';
    } else if (input == "exit") {
      std::cout << "bye" << '\n';
      break;
    }
  }

  return 0;
}