#include <iostream>
#include <string>
#include <vector>

template <typename T>
class Stack {
 private:
  std::vector<T> vector_;
  T top_;

 public:
  Stack() { top_ = -1; }

  bool IsEmpty() { return top_ == -1; }

  void Push(int val) {
    vector_.push_back(val);
    top_++;
  }

  void Pop() {
    std::cout << vector_.at(top_--) << '\n';
    vector_.pop_back();
    return;
  }

  int Back() { return vector_.at(top_); }
  int Size() { return vector_.size(); }
  void Clear() {
    vector_.clear();
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