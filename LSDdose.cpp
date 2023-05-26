#include <iostream>
#include <vector>

void CountingSort(std::vector<long long>& arr, int byte_index) {
  const int kRadix = 256;
  int size = arr.size();

  std::vector<long long> count(kRadix, 0);
  std::vector<long long> output(size);

  for (int i = 0; i < size; ++i) {
    ++count[(arr[i] >> (byte_index * 8)) & 0xFF];
  }

  for (int i = 1; i < kRadix; ++i) {
    count[i] += count[i - 1];
  }

  for (int i = size - 1; i >= 0; --i) {
    output[count[(arr[i] >> (byte_index * 8)) & 0xFF] - 1] = arr[i];
    --count[(arr[i] >> (byte_index * 8)) & 0xFF];
  }

  for (int i = 0; i < size; ++i) {
    arr[i] = output[i];
  }
}

void RadixSort(std::vector<long long>& arr) {
  const int kByteCount = sizeof(long long);

  for (int byte_index = 0; byte_index < kByteCount; ++byte_index) {
    CountingSort(arr, byte_index);
  }
}

int main() {
  int n;
  long long place_holder;
  std::vector<long long> arr;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> place_holder;
    arr.push_back(place_holder);
  }

  RadixSort(arr);

  for (long long num : arr) {
    std::cout << num << " ";
  }
  std::cout << '\n';

  return 0;
}

