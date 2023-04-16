#include <iostream>

bool BinarySearch(const int *begin, const int *end, int target) {
  if (begin >= end) {
    return false;
  }

  const int *mid_element = begin + (end - begin) / 2;
  if (*mid_element == target) {
    return true;
  } else if (*mid_element < target) {
    return BinarySearch(mid_element + 1, end, target);
  } else if (*mid_element > target) {
    return BinarySearch(begin, mid_element, target);
  }
  return false;
}

int main() {
  unsigned int size, iterations;
  int begin, end;
  int target;
  std::cin >> size;
  int *elems = new int[size];
  for (size_t i = 0; i < size; i++) {
    std::cin >> elems[i];
  }

  std::cin >> iterations;

  for (size_t i = 0; i < iterations; i++) {
    std::cin >> begin;
    std::cin >> end;
    std::cin >> target;

    if (BinarySearch(elems + begin, elems + end, target)) {
      std::cout << "YES" << '\n';
    } else {
      std::cout << "NO" << '\n';
    }
  }
  delete[] elems;

  return 0;
}