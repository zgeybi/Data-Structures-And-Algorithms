#include <iostream>
#include <string>

template <typename T>
struct Pair {
  T val;
  T min;
};

template <typename T>
class StackIn {
 private:
  Pair<T> *in_stack_;
  T front_;
  size_t size_;
  size_t capacity_;

 public:
  StackIn() {
    size_ = 0;
    capacity_ = 1;
    front_ = 0;
    in_stack_ = new Pair<T>[capacity_];
  }

  ~StackIn() { delete[] in_stack_; }

  void Enqueue(T val) {
    if (size_ == capacity_) {
      Resize(capacity_ * 2);
    }
    if (size_ == 0) {
      in_stack_->val = val;
      in_stack_->min = val;
      size_++;
      return;
    }
    (in_stack_ + size_)->val = val;
    if ((in_stack_ + size_ - 1)->min > val) {
      (in_stack_ + size_)->min = val;
      size_++;
    } else {
      (in_stack_ + size_)->min = (in_stack_ + size_ - 1)->min;
      size_++;
    }
    return;
  }

  T PopBack() {
    if (size_ == 0) {
      throw "error";
    }
    if (size_ == capacity_ / 2) {
      Resize(capacity_ / 2);
    }
    return in_stack_[size_-- - 1].val;
  }

  T GetMin() {
    if (size_ == 0) {
      throw "error";
    }
    return in_stack_[(size_ - 1)].min;
  }

  T Front() {
    if (size_ == 0) {
      throw "error";
    }
    return in_stack_[0].val;
  }

  void Resize(size_t new_capacity) {
    Pair<T> *new_array = new Pair<T>[new_capacity];
    capacity_ = new_capacity;

    if (new_capacity < size_) {
      for (int i = 0; i < new_capacity; i++) {
        new_array[i] = in_stack_[i];
      }
      delete[] in_stack_;
      in_stack_ = new_array;
      return;
    } else if (new_capacity >= size_) {
      for (int i = 0; i < size_; i++) {
        new_array[i] = in_stack_[i];
      }
      delete[] in_stack_;
      in_stack_ = new_array;
      return;
    }
  }

  size_t Size() { return size_; }

  void Clear() {
    size_ = 0;
    capacity_ = 1;
    Pair<T> *cleared_array = new Pair<T>[capacity_];
    delete[] in_stack_;
    in_stack_ = cleared_array;
  }

  Pair<T> *GetArray() { return in_stack_; }
};

template <typename T>
class StackOut {
 private:
  Pair<T> *out_stack_;
  size_t size_;
  size_t capacity_;

 public:
  StackOut() {
    size_ = 0;
    capacity_ = 1;
    out_stack_ = new Pair<T>[capacity_];
  }
  ~StackOut() { delete[] out_stack_; }

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

  T Front() {
    if (size_ == 0) {
      throw "error";
    }
    return out_stack_[size_ - 1].val;
  }

  size_t Size() { return size_; }
  void Clear() {
    size_ = 0;
    capacity_ = 1;
    Pair<T> *cleared_array = new Pair<T>[capacity_];
    delete[] out_stack_;
    out_stack_ = cleared_array;
  }
  void CopyStack(StackIn<T> *stack1) {
    size_t size = stack1->Size();
    for (int i = 0; i < size; i++) {
      Enqueue(stack1->PopBack());
    }
    stack1->Clear();
  }
};

int main() {
  int n;
  StackIn<long long> *stack_in = new StackIn<long long>();
  StackOut<long long> *stack_out = new StackOut<long long>();
  std::cin >> n;
  std::string input;
  for (int i = 0; i < n; i++) {
    std::cin >> input;
    if (input == "enqueue") {
      long long val;
      std::cin >> val;
      stack_in->Enqueue(val);
      std::cout << "ok" << '\n';
      continue;
    } else if (input == "dequeue") {
      try {
        long long value = stack_out->PopBack();
        std::cout << value << '\n';
      } catch (const char *msg) {
        if (stack_in->Size() == 0) {
          std::cout << msg << '\n';
        } else {
          stack_out->CopyStack(stack_in);
          std::cout << stack_out->PopBack() << '\n';
        }
      }
      continue;
    } else if (input == "front") {
      try {
        long long value = stack_out->Front();
        std::cout << value << '\n';
      } catch (const char *msg) {
        if (stack_in->Size() == 0) {
          std::cout << msg << '\n';
        } else {
          std::cout << stack_in->Front() << '\n';
        }
      }
      continue;
    } else if (input == "size") {
      std::cout << stack_in->Size() + stack_out->Size() << '\n';
      continue;
    } else if (input == "clear") {
      stack_in->Clear();
      stack_out->Clear();
      std::cout << "ok" << '\n';
      continue;
    } else if (input == "min") {
      try {
        long long value = stack_out->GetMin();
        long long value2 = stack_in->GetMin();
        if (value < value2) {
          std::cout << value << '\n';
        } else {
          std::cout << value2 << '\n';
        }

      } catch (const char *msg) {
        if (stack_in->Size() == 0 && stack_out->Size() == 0) {
          std::cout << msg << '\n';
        } else if (stack_in->Size() == 0) {
          std::cout << stack_out->GetMin() << '\n';
        } else {
          std::cout << stack_in->GetMin() << '\n';
        }
      }
      continue;
    }
  }

  delete stack_in;
  delete stack_out;
  return 0;
}