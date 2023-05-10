#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

using std::swap;
const int kNumberOfSubElements = 5;

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
long Partition(std::vector<T>& a, long left, long right, T pivot_value) {
  long start = left;
  while (left <= right) {
    for (; a[left] < pivot_value; ++left)
      ;
    for (; pivot_value < a[right]; --right)
      ;
    if (left >= right) {
      break;
    }
    swap(a[left++], a[right--]);
  }
  return start + right;
}

template <typename T>
long Pivot(std::vector<T>& vec, T pivot, long start, long end) {
  long left = start, right = end - 1;
  while (left < right) {
    while (vec.at(left) < pivot && left <= right) left++;
    while (vec.at(right) > pivot && right >= left) right--;
    if (left >= right)
      break;
    else if (vec.at(left) == vec.at(right)) {
      left++;
      continue;
    }
    swap(vec.at(left), vec.at(right));
  }
  return right;
}

template <typename T>
T MedianOfMedians(std::vector<T>& vec, long k, long start, long end) {
  if (end - start < 10) {
    InsertionSort(vec, start, end);
    return vec.at(k);
  }
  std::vector<T> medians;
  for (long i = start; i < end; i += 5) {
    if (end - i < 10) {
      InsertionSort(vec, i, end);
      medians.push_back(vec.at((i + end) / 2));
    } else {
      InsertionSort(vec, i, i + 5);
      medians.push_back(vec.at(i + 2));
    }
  }
  T median = MedianOfMedians(medians, medians.size() / 2, 0, medians.size());
  long piv = Pivot(vec, median, start, end);
  long length = piv - start + 1;

  if (k < length) {
    return MedianOfMedians(vec, k, start, piv);
  } else if (k > length) {
    return MedianOfMedians(vec, k - length, piv + 1, end);
  } else
    return vec[k];
}

template <typename T>
void QuickSort(std::vector<T>& a) {
  long size = a.size();
  if (size <= 256) {
    InsertionSort<T>(a, 0, size);
    return;
  }
  std::stack<std::pair<long, long>> index_states;
  index_states.emplace(std::make_pair(0, size));
  while (!index_states.empty()) {
    long left = index_states.top().first;
    long right = index_states.top().second;
    index_states.pop();
    if (right <= left) {
      continue;
    } else if (right - left + 1 <= 256) {
      InsertionSort<T>(a, left, right);
      continue;
    }
    T pivot = MedianOfMedians<T>(a, (right - left) / 2, left, right);
    long pivot_new_index = Partition<T>(a, left, right, pivot);
    if (pivot_new_index - left + 1 <= 256) {
      InsertionSort(a, left, pivot_new_index + 1);
    } else {
      index_states.emplace(std::make_pair(left, pivot_new_index + 1));
    }
    if (right - pivot_new_index + 1 <= 256) {
      InsertionSort(a, pivot_new_index + 1, right);
    } else {
      index_states.emplace(std::make_pair(pivot_new_index + 1, right));
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
  // InsertionSort<long long>(array, 0, size);
  for (long i = 0; i < size; i++) {
    if (i != size - 1) {
      std::cout << array[i] << ' ';
      continue;
    }
    std::cout << array[i] << '\n';
  }

  for (long i = 1; i < size; i++) {
    if (array[i] < array[i - 1]) {
      std::cout << array[i] << " at " << i << '\n';
      continue;
    }
  }
  return 0;
}
