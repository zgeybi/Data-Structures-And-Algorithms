#include <iostream>
#include <utility>
#include <vector>

template <typename T>
long BinarySearch(std::vector<T>& arr, long left, long right, T key) {
  if (right <= left) {
    return (key > arr[left]) ? (left + 1) : left;
  }
  long mid = (left + right) / 2;
  if (key == arr[mid]) {
    return mid + 1;
  } else if (key > arr[mid]) {
    return BinarySearch<T>(arr, mid + 1, right, key);
  } else {
    return BinarySearch<T>(arr, left, mid - 1, key);
  }
}

template <typename T>
void InsertionSort(std::vector<T>& arr, long n, long offset) {
  for (long i = offset + 1; i < offset + n; i++) {
    T key = arr[i];
    long j = i - 1;
    long index = BinarySearch<T>(arr, offset, j, key);
    for (long k = i - 1; k >= index; k--) {
      arr[k + 1] = arr[k];
    }
    arr[index] = key;
  }
}

template <typename T>
long Partition(std::vector<T>& v, long start, long end, T pivot) {
  long left = start, right = end;
  while (left <= right) {
    while (v[left] < pivot) {
      left++;
    }
    while (v[right] > pivot) {
      right--;
    }
    if (left <= right) {
      std::swap(v[left], v[right]);
      left++;
      right--;
    }
  }
  std::swap(v[start], v[left - 1]);
  return left - 1;
}

template <typename T>
T MedianOfMedians(std::vector<T>& v, long start, long end, long k) {
  while (true) {
    if (start == end) {
      return v[start];
    }
    long n = end - start + 1;
    long numGroups = n / 5;
    if (n % 5 != 0) {
      numGroups++;
    }
    std::vector<T> medians;
    for (long i = 0; i < numGroups; i++) {
      long group_start = start + i * 5;
      long group_end = std::min(group_start + 4, end);
      InsertionSort<T>(v, group_end - group_start + 1, group_start);
      long medianIndex = group_start + (group_end - group_start) / 2;
      medians.push_back(v[medianIndex]);
    }
    T medianOfMedians =
        MedianOfMedians<T>(medians, 0, medians.size() - 1, medians.size() / 2);
    long pivotIndex = Partition<T>(v, start, end, medianOfMedians);
    long rank = pivotIndex - start + 1;
    if (k == rank) {
      return v[pivotIndex];
    } else if (k < rank) {
      end = pivotIndex - 1;
    } else {
      start = pivotIndex + 1;
      k -= rank;
    }
  }
}

template <typename T>
void QuickSort(std::vector<T>& arr, long start, long end) {
  if (end - start <= 0) {
    return;
  }
  if (end - start + 1 <= 256) {
    InsertionSort<T>(arr, end - start + 1, start);
    return;
  }
  std::vector<std::pair<long, long>> temporary_vector;
  temporary_vector.push_back(std::make_pair(start, end));
  while (!temporary_vector.empty()) {
    std::pair<long, long> current = temporary_vector.back();
    temporary_vector.pop_back();
    start = current.first;
    end = current.second;
    if (end - start + 1 <= 256) {
      InsertionSort<T>(arr, end - start + 1, start);
    }
    long pivot = MedianOfMedians<T>(arr, start, end, (start + end) / 2);
    long pivot_index = Partition<T>(arr, start, end, pivot);
    if (pivot_index - 1 - start <= 256) {
      InsertionSort<T>(arr, pivot_index - start - 1, start);
    } else {
      temporary_vector.push_back(std::make_pair(start, pivot_index - 1));
    }
    if (end - pivot_index + 1 <= 256) {
      InsertionSort<T>(arr, end - pivot_index + 1, pivot_index + 1);
    } else {
      temporary_vector.push_back(std::make_pair(pivot_index + 1, end));
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
  QuickSort<long long>(array, 0, size - 1);
  for (long i = 0; i < size; i++) {
    if (i != size - 1) {
      std::cout << array[i] << ' ';
      continue;
    }
    std::cout << array[i];
  }

  return 0;
}
