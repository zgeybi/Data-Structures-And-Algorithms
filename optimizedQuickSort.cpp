#include <iostream>
#include <stack>
#include <vector>

template <typename T>
long BinarySearch(std::vector<T>& arr, long start, long end, T key) {
  if (end <= start) {
    return (arr[start] > key) ? start : start + 1;
  }
  long mid = (end + start) / 2;
  if (arr[mid] == key) {
    return mid + 1;
  } else if (arr[mid] < key) {
    return BinarySearch(arr, mid + 1, end, key);
  } else {
    return BinarySearch(arr, start, mid, key);
  }
}

template <typename T>
void InsertionSort(std::vector<T>& arr, long start, long end) {
  for (long i = start + 1; i < end; i++) {
    T key = arr[i];
    long j = i - 1;
    long pos = BinarySearch<T>(arr, start, j, key);
    for (; j >= pos; j--) {
      arr[j + 1] = arr[j];
    }
    arr[pos] = key;
  }
}

template <typename T>
T SubsOfFive(std::vector<T> arr, long left, long right) {
  if (right - left + 1 <= 5) {
    InsertionSort(arr, left, right + 1);
    return arr.at((right + left) / 2);
  }
  std::vector<T> medians;
  for (long i = left; i <= right; i += 5) {
    if (i + 5 > right) {
      InsertionSort(arr, i, right + 1);
      medians.push_back(arr.at((i + right) / 2));
      break;
    }
    InsertionSort(arr, i, i + 5);
    medians.push_back(arr.at((i + i + 4) / 2));
  }
  return SubsOfFive(medians, 0, medians.size() - 1);
}

template <typename T>
long PivotProccessor(std::vector<T>& arr, long left, long right, T median) {
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
void QuickSort(std::vector<T>& a) {
  long size = a.size();
  if (size <= 256) {
    InsertionSort(a, 0, size);
    return;
  }
  std::stack<std::pair<long, long>> index_states;
  index_states.emplace(0, size - 1);
  while (!index_states.empty()) {
    long left = index_states.top().first;
    long right = index_states.top().second;
    index_states.pop();
    if (right <= left) {
      continue;
    }
    T pivot = SubsOfFive(a, left, right);
    long pivot_index = PivotProccessor(a, left, right, pivot);
    if (pivot_index - left + 1 <= 100) {
      InsertionSort(a, left, pivot_index + 1);
    } else {
      index_states.emplace(left, pivot_index + 1);
    }
    if (right - pivot_index + 1 <= 100) {
      InsertionSort(a, pivot_index + 1, right + 1);
    } else {
      index_states.emplace(pivot_index + 1, right);
    }
  }
}

int main() {
  long size;
  long long place_holder;
  std::cin >> size;
  std::vector<long long> array;
  for (long i = 0; i < size; i++) {
    std::cin >> place_holder;
    array.push_back(place_holder);
  }
  QuickSort<long long>(array);
  for (long i = 0; i < size; i++) {
    if (i != size - 1) {
      std::cout << array[i] << ' ';
      continue;
    }
    std::cout << array[i] << '\n';
  }
  return 0;
}
