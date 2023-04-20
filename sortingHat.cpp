#include <algorithm>
#include <iostream>
#include <string>

template <typename T>
struct Pair {
  T val;
  T min;
};

template <typename T>
struct IsLess {
  bool operator()(const T &l, const T &r) const { return l <= r; }
};

template <typename T, class TLess = IsLess<T>>
class Stack {
 private:
  Pair<T> *out_stack_;
  size_t size_;
  size_t capacity_;

 public:
  Stack(TLess comparator = TLess()) {
    size_ = 0;
    capacity_ = 1;
    out_stack_ = new Pair<T>[capacity_];
  }
  //~Stack() { delete[] out_stack_; }

  void Enqueue(T val) {
    if (size_ == capacity_) {
      Resize(capacity_ * 2);
    }
    if (size_ == 0) {
      out_stack_->val = val;
      out_stack_->min = val;
      size_++;
      return;
    }
    (out_stack_ + size_)->val = val;
    if ((out_stack_ + size_ - 1)->min > val) {
      (out_stack_ + size_)->min = val;
    } else {
      (out_stack_ + size_)->min = (out_stack_ + size_ - 1)->min;
    }
    size_++;
    return;
  }
  void Resize(size_t new_capacity) {
    Pair<T> *new_array = new Pair<T>[new_capacity];
    capacity_ = new_capacity;

    if (new_capacity < size_) {
      for (int i = 0; i < new_capacity; i++) {
        new_array[i] = out_stack_[i];
      }
      delete[] out_stack_;
      out_stack_ = new_array;
      return;
    } else if (new_capacity >= size_) {
      for (int i = 0; i < size_; i++) {
        new_array[i] = out_stack_[i];
      }
      delete[] out_stack_;
      out_stack_ = new_array;
      return;
    }
  }
  T PopBack() {
    if (size_ == 0) {
      throw "error";
    }
    if (size_ == capacity_ / 2) {
      Resize(capacity_ / 2);
    }
    return out_stack_[size_-- - 1].val;
  }

  T GetMin() {
    if (size_ == 0) {
      throw "error";
    }
    return (out_stack_ + (size_ - 1))->min;
  }

  T Front(bool in_or_out) {
    if (size_ == 0) {
      throw "error";
    }
    if (in_or_out) {
      return out_stack_[0].val;
    } else {
      return out_stack_[size_ - 1].val;
    }
  }

  size_t Size() { return size_; }
  void Clear() {
    size_ = 0;
    capacity_ = 1;
    Pair<T> *cleared_array = new Pair<T>[capacity_];
    delete[] out_stack_;
    out_stack_ = cleared_array;
  }
  void CopyStack(Stack<T> *stack1) {
    size_t size = stack1->Size();
    for (int i = 0; i < size; i++) {
      Enqueue(stack1->PopBack());
    }
    stack1->Clear();
  }
};

template <typename T, class TLess = IsLess<T>>
class MinQueue {
 private:
  Stack<T> in_stack_;
  Stack<T> out_stack_;

 public:
  MinQueue(TLess comparator = TLess()) {
    in_stack_ = Stack<T>();
    out_stack_ = Stack<T>();
  }
  void Enqueue(T val) { in_stack_.Enqueue(val); }

  T PopBack() {
    if (out_stack_.Size() == 0) {
      if (in_stack_.Size() == 0) {
        throw "error";
        return -1;
      }
      out_stack_.CopyStack(&in_stack_);
    }
    return out_stack_.PopBack();
  }

  T Front() {
    if (out_stack_.Size() == 0) {
      if (in_stack_.Size() == 0) {
        throw "error";
        return -1;
      }
      return in_stack_.Front(true);
    }
    return out_stack_.Front(false);
  }

  T GetMin() {
    if (out_stack_.Size() == 0 && in_stack_.Size() == 0) {
      throw "error";
    } else if (out_stack_.Size() == 0) {
      return in_stack_.GetMin();
    } else if (in_stack_.Size() == 0) {
      return out_stack_.GetMin();
    }
    return std::min(in_stack_.GetMin(), out_stack_.GetMin());
  }

  size_t Size() { return in_stack_.Size() + out_stack_.Size(); }
  void Clear() {
    in_stack_.Clear();
    out_stack_.Clear();
  }
};

int main() {
  int n;
  MinQueue<long long> *Queue = new MinQueue<long long>();
  std::cin >> n;
  std::string input;
  for (int i = 0; i < n; i++) {
    std::cin >> input;
    if (input == "enqueue") {
      long long val;
      std::cin >> val;
      Queue->Enqueue(val);
      std::cout << "ok" << '\n';
      continue;
    } else if (input == "dequeue") {
      try {
        long long value = Queue->PopBack();
        std::cout << value << '\n';
      } catch (const char *msg) {
        std::cout << msg << '\n';
      }
      continue;
    } else if (input == "front") {
      try {
        long long value = Queue->Front();
        std::cout << value << '\n';
      } catch (const char *msg) {
        std::cout << msg << '\n';
      }
      continue;
    } else if (input == "size") {
      std::cout << Queue->Size() << '\n';
      continue;
    } else if (input == "clear") {
      Queue->Clear();
      std::cout << "ok" << '\n';
      continue;
    } else if (input == "min") {
      try {
        long long value = Queue->GetMin();
        std::cout << value << '\n';
      } catch (const char *msg) {
        std::cout << msg << '\n';
      }
    }
    continue;
  }

  delete Queue;
  return 0;
}