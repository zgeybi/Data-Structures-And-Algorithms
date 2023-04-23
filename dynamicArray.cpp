#include <iostream>
#include <string>

template <typename T> class Vector {
private:
  T *arr_;
  size_t size_;
  size_t capacity_;

public:
  Vector() {
    size_ = 0;
    capacity_ = 1;
    arr_ = new T[capacity_];
  }

  ~Vector() { delete[] arr_; }

  void Push(T val) {
    if (size_ == capacity_) {
      this->Resize(capacity_ * 2);
    }
    arr_[size_++] = val;

    std::cout << "ok" << '\n';
    return;
  }
  void Pop() {
    if (size_ == 0) {
      std::cout << "error" << '\n';
      return;
    }
    size_--;
    std::cout << arr_[size_] << '\n';
    if (size_ == (capacity_ / 2) && size_ > 0) {
      this->Resize(capacity_ / 2);
    }
    return;
  }
  T ElementAtIndex(size_t index) { return arr_[index]; }

  void Resize(size_t new_capacity) {
    T *new_array = new T[new_capacity];
    capacity_ = new_capacity;

    if (new_capacity < size_) {
      for (int i = 0; i < new_capacity; i++) {
        new_array[i] = arr_[i];
      }
      delete[] arr_;
      arr_ = new_array;
      return;
    } else if (new_capacity >= size_) {
      for (int i = 0; i < size_; i++) {
        new_array[i] = arr_[i];
      }
      delete[] arr_;
      arr_ = new_array;
      return;
    }
  }

  size_t Size() { return size_; }

  size_t Capacity() { return capacity_; }

  void Clear() {
    size_ = 0;
    capacity_ = 1;
    T *cleared_array = new T[capacity_];
    delete[] arr_;
    arr_ = cleared_array;
    std::cout << "ok" << '\n';
  }
};

int main() {
  Vector<int> vector;
  std::string input;
  int val = 0;
  while (1) {
    std::cin >> input;
    if (input == "push") {
      std::cin >> val;
      vector.Push(val);
      continue;
    } else if (input == "pop") {
      vector.Pop();
      continue;
    } else if (input == "at") {
      std::cin >> val;
      try {
        if (val >= vector.Size() || val < 0) {
          throw "error";
        } else {
          std::cout << vector.ElementAtIndex(val) << '\n';
        }
      } catch (const char *msg) {
        std::cout << msg << '\n';
      }
      continue;
    } else if (input == "size") {
      std::cout << vector.Size() << '\n';
      continue;
    } else if (input == "resize") {
      std::cin >> val;
      vector.Resize(val);
      std::cout << "ok" << '\n';
      continue;
    } else if (input == "capacity") {
      std::cout << vector.Capacity() << '\n';
      continue;
    } else if (input == "clear") {
      vector.Clear();
      continue;
    } else if (input == "exit") {
      std::cout << "bye" << '\n';
      return 0;
    }
  }

  return 0;
}