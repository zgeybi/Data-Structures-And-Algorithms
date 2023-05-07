#include <iostream>
#include <vector>

template <typename T>
T Max(T array[], long n) {
  T max = array[0];
  for (long i = 1; i < n; i++) {
    if (array[i] > max) {
      max = array[i];
    }
  }
  return max;
}

template <typename T>
void CountingSort(T array[], long size, long place) {
  const int kMAX = 10;
  std::vector<T> output(size);
  long count[kMAX]{0};

  for (long i = 0; i < size; i++) {
    count[(array[i] / place) % 10]++;
  }

  for (long i = 1; i < kMAX; i++) {
    count[i] += count[i - 1];
  }

  for (long i = size - 1; i >= 0; i--) {
    output[count[(array[i] / place) % 10] - 1] = array[i];
    count[(array[i] / place) % 10]--;
  }

  for (long i = 0; i < size; i++) {
    array[i] = output[i];
  }
}

template <typename T>
void RadixSort(T array[], long size) {
  T max = Max(array, size);
  for (long place = 1; max / place > 0; place *= 10) {
    CountingSort(array, size, place);
  }
}

template <typename T>
void PrintArray(std::vector<T> array) {
  for (auto elem : array) {
    std::cout << elem << " ";
  }
  std::cout << '\n';
}

int main() {
  long n;
  std::cin >> n;
  std::vector<unsigned long long> array(n);

  for (long i = 0; i < n; i++) {
    std::cin >> array[i];
  }

  RadixSort<unsigned long long>(&array[0], n);
  PrintArray<unsigned long long>(array);
}