#include <iostream>
#include <vector>

class Set {
 private:
  static const int kMaxSize = 100000;
  std::vector<std::vector<int>> hash_set_;

  int Hash(int value) { return value % kMaxSize; }

 public:
  Set() { hash_set_.resize(kMaxSize); }

  void Add(int value) {
    int index = Hash(value);
    std::vector<int>& bucket = hash_set_[index];
    for (int val : bucket) {
      if (val == value) {
        return;
      }
    }
    bucket.push_back(value);
  }

  void Remove(int value) {
    int index = Hash(value);
    std::vector<int>& bucket = hash_set_[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
      if (*it == value) {
        bucket.erase(it);
        break;
      }
    }
  }

  bool Contains(int value) {
    int index = Hash(value);
    const std::vector<int>& bucket = hash_set_[index];
    for (int val : bucket) {
      if (val == value) {
        return true;
      }
    }
    return false;
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

