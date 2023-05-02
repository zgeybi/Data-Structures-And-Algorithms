#include <iostream>
#include <vector>

template <typename T>
int BinarySearch(std::vector<T>& arr, int left, int right, T key) {
  if (right <= left) {
    return (key > arr[left]) ? (left + 1) : left;
  }
  int mid = (left + right) / 2;
  if (key == arr[mid]) {
    return mid + 1;
  } else if (key > arr[mid]) {
    return BinarySearch(arr, mid + 1, right, key);
  } else {
    return BinarySearch(arr, left, mid - 1, key);
  }
}

template <typename T>
void InsertionSort(std::vector<T>& arr, int n, int offset) {
  for (int i = 1; i + offset < n && i < n; i++) {
    T key = arr[i + offset];
    int j = i - 1;
    int index = BinarySearch<T>(arr, 0, j + offset, key);
    for (int k = i - 1; k >= index; k--) {
      arr[k + 1 + offset] = arr[k + offset];
    }
    arr[index + offset] = key;
  }
}

template <typename T>
int Partition(std::vector<T>& v, int start, int end, T pivot) {
  int left = start, right = end;
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
T MedianOfMedians(std::vector<T>& v, int start, int end, int k) {
  while (true) {
    if (start == end) {
      return v[start];
    }
    int n = end - start + 1;
    int numGroups = n / 5;
    if (n % 5 != 0) {
      numGroups++;
    }
    std::vector<T> medians;
    for (int i = 0; i < numGroups; i++) {
      int group_start = start + i * 5;
      int group_end = std::min(group_start + 4, end);
      InsertionSort<T>(v, group_end - group_start + 1, group_start);
      int medianIndex = group_start + (group_end - group_start) / 2;
      medians.push_back(v[medianIndex]);
    }
    T medianOfMedians =
        MedianOfMedians<T>(medians, 0, medians.size() - 1, medians.size() / 2);
    int pivotIndex = Partition(v, start, end, medianOfMedians);
    int rank = pivotIndex - start + 1;
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
void QuickSort(std::vector<T>& arr, int start, int end) {
  if (end - start <= 0) {
    return;
  }
  if (end - start + 1 <= 256) {
    InsertionSort<T>(arr, end - start + 1, start);
    return;
  }
  std::vector<std::pair<T, T>> temporary_vector;
  temporary_vector.push_back(std::make_pair(start, end));
  while (!temporary_vector.empty()) {
    std::pair<T, T> current = temporary_vector.back();
    temporary_vector.pop_back();
    start = current.first;
    end = current.second;
    if (end - start + 1 <= 256) {
      InsertionSort<T>(arr, end - start + 1, start);
      return;
    }
    int pivot = MedianOfMedians(arr, start, end, (start + end) / 2);
    int pivot_index = Partition<T>(arr, start, end, pivot);
    if (pivot_index - 1 - start <= 256) {
      InsertionSort(arr, pivot_index - start - 1, start);
    } else {
      temporary_vector.push_back(std::make_pair(start, pivot_index - 1));
    }
    if (end - pivot_index + 1 <= 256) {
      InsertionSort(arr, end - pivot_index + 1, pivot_index + 1);
    } else {
      temporary_vector.push_back(std::make_pair(pivot_index + 1, end));
    }
  }
}

int main() {
  int size;
  long long place_holder;
  std::cin >> size;
  std::vector<long long> array;
  for (int i = 0; i < size; i++) {
    std::cin >> place_holder;
    array.push_back(place_holder);
  }
  QuickSort(array, 0, size - 1);

  for (int i = 0; i < size; i++) {
    if (i != size - 1) {
      std::cout << array[i] << ' ';
      continue;
    }
    std::cout << array[i];
  }

  return 0;
}