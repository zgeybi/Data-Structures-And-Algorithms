#include <iostream>
#include <stack>
#include <utility>
#include <vector>

const int kNumberOfSubElements = 5;
template <typename T>
int BinarySearch(std::vector<T>& arr, int start, int end, T key) {
  if (end <= start) {
    return (arr[start] > key) ? start : start + 1;
  }
  int mid = (end + start) / 2;
  if (arr[mid] == key) {
    return mid + 1;
  } else if (arr[mid] < key) {
    return BinarySearch(arr, mid + 1, end, key);
  } else {
    return BinarySearch(arr, start, mid, key);
  }
}

template <typename T>
void InsertionSort(std::vector<T>& arr, int start, int end) {
  for (int i = start + 1; i < end; i++) {
    T key = arr[i];
    int j = i - 1;
    int pos = BinarySearch<T>(arr, start, j, key);
    for (; j >= pos; j--) {
      arr[j + 1] = arr[j];
    }
    arr[pos] = key;
  }
}

template <typename T>
T MedianOfMedians(std::vector<T>& arr, int left, int right) {
  if (right - left + 1 <= 5) {
    InsertionSort(arr, left, right + 1);
    return arr.at((left + right) / 2);
  }
  std::vector<T> medians;
  for (int i = left; i <= right; i += 5) {
    if (i + 5 > right) {
      InsertionSort(arr, i, right + 1);
      medians.push_back(arr.at((i + right) / 2));
      break;
    }
    InsertionSort(arr, i, i + 5);
    medians.push_back(arr.at(i + 2));
  }
  return MedianOfMedians(medians, 0, medians.size() - 1);
}

template <typename T>
int Pivot(std::vector<T>& arr, int left, int right, T median) {
  while (left <= right) {
    for (; arr.at(left) < median; ++left) {
      ;
    }
    for (; arr.at(right) > median; --right) {
      ;
    }
    if (left >= right) {
      break;
    }
    std::swap(arr.at(left++), arr.at(right--));
  }
  return right;
}

template <typename T>
T KthOrder(std::vector<T>& arr, int k) {
  int size = arr.size();
  int left = 0;
  int right = size - 1;
  int order = k;
  int pivot;
  while (true) {
    if (right <= left) {
      return arr[left];
    }
    T median = MedianOfMedians(arr, left, right);
    int piv = Pivot(arr, left, right, median);
    int length = piv - left + 1;
    if (order < length) {
      right = piv;
      continue;
    } else if (order > length) {
      left = piv + 1;
      order = order - length;
      continue;
    } else {
      pivot = piv;
      break;
    }
  }
  return arr[pivot];
}

int main() {
  int n, k;
  int A0, A1, temp;
  std::vector<int> terms;

  std::cin >> n >> k;
  std::cin >> A0;
  if (n != 1) {
    std::cin >> A1;
    terms.push_back(A0);
    terms.push_back(A1);
  } else {
    terms.push_back(A0);
    std::cout << A0 << '\n';
    return 0;
  }
  for (int i = 2; i < n; i++) {
    temp = ((terms[i - 1] * 123) + (terms[i - 2] * 45)) % (10000000 + 4321);
    terms.push_back(temp);
  }

  std::cout << KthOrder<int>(terms, k) << '\n';
  return 0;
}