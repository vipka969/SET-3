#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "ArrayGenerator.h"
#include "SortTester.h"

void insertionSort(std::vector<int> &v, int l, int r) {
  for (int i = l + 1; i <= r; i++) {
    int k = v[i];
    int j = i - 1;
    while (j >= l && v[j] > k) {
      v[j + 1] = v[j];
      j--;
    }
    v[j + 1] = k;
  }
}

void heapify(std::vector<int>& v, int len, int i) {
  while (true) {
    int left = 2 * i + 1;
    int right = left + 1;
    int big = i;

    if (left < len && v[left] > v[big]) {
      big = left;
    }
    if (right < len && v[right] > v[big]) {
      big = right;
    }
    if (big == i) {
      break;
    }

    std::swap(v[i], v[big]);
    i = big;
  }
}

void heapSort(std::vector<int>& arr, int low, int high) {
  int n = high - low + 1;
  std::vector<int> temp(n);

  for (int i = 0; i < n; i++) {
    temp[i] = arr[low + i];
  }

  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(temp, n, i);
  }

  for (int i = n - 1; i > 0; i--) {
    std::swap(temp[0], temp[i]);
    heapify(temp, i, 0);
  }

  for (int i = 0; i < n; i++) {
    arr[low + i] = temp[i];
  }
}

int partition(std::vector<int>& arr, int low, int high) {
  int ind = low + rand() % (high - low + 1);
  std::swap(arr[ind], arr[high]);

  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (arr[j] <= pivot) {
      i++;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[high]);
  return i + 1;
}

void introsortUtil(std::vector<int>& arr, int low, int high, int limit) {
  int len = high - low + 1;

  if (len < 16) {
    insertionSort(arr, low, high);
    return;
  }

  if (limit == 0) {
    heapSort(arr, low, high);
    return;
  }

  int pivot = partition(arr, low, high);

  introsortUtil(arr, low, pivot - 1, limit - 1);
  introsortUtil(arr, pivot + 1, high, limit - 1);
}

void introsort(std::vector<int>& arr) {
  int n = arr.size();
  if (n <= 1) return;

  int limit = 2 * log2(n);

  introsortUtil(arr, 0, n - 1, limit);
}

void quickSort(std::vector<int>& arr, int low, int high) {
  if (low < high) {
    int pivot = partition(arr, low, high);
    quickSort(arr, low, pivot - 1);
    quickSort(arr, pivot + 1, high);
  }
}

int main() {
  GeneratorArray gen;
  SortTester tester;
  std::vector<int> sizes;

  for (int size = 500; size <= 100000; size += 100) {
      sizes.push_back(size);
  }


  std::cout << "Измерение времени стандартного Quick Sort" << std::endl;

  std::cout << "Начало измерения алгоритма с массивами со случайными числами:" << std::endl;
  std::ofstream file1("quick_random.csv");
  file1 << "size,time_micros\n";

  for (int size : sizes) {
      std::vector<int> test_array = gen.getTestArray("random", size);
      long long avg_time = tester.testStandardQuickSort(test_array, 3);
      file1 << size << "," << avg_time << "\n";

      if (size % 20000 == 500) {
          std::cout << "  Size: " << size << " - Time: " << avg_time << " μs\n";
      }
  }
  file1.close();
  std::cout << "Конец измерения" << std::endl;

  std::cout << "Начало измерения алгоритма с обратно отсортированными массивами:" << std::endl;
  std::ofstream file2("quick_reverse_sorted.csv");
  file2 << "size,time_micros\n";

  for (int size : sizes) {
      std::vector<int> test_array = gen.getTestArray("reverse_sorted", size);
      long long avg_time = tester.testStandardQuickSort(test_array, 3);
      file2 << size << "," << avg_time << "\n";

      if (size % 20000 == 500) {
          std::cout << "  Size: " << size << " - Time: " << avg_time << " μs\n";
      }
  }
  file2.close();
  std::cout << "Конец измерения" << std::endl;

  std::cout << "Начало измерения алгоритма с почти отсортированными массивами:" << std::endl;
  std::ofstream file3("quick_almost_sorted.csv");
  file3 << "size,time_micros\n";

  for (int size : sizes) {
      std::vector<int> test_array = gen.getTestArray("almost_sorted", size);
      long long avg_time = tester.testStandardQuickSort(test_array, 3);
      file3 << size << "," << avg_time << "\n";

      if (size % 20000 == 500) {
          std::cout << "  Size: " << size << " - Time: " << avg_time << " μs\n";
      }
  }
  file3.close();
  std::cout << "Конец измерения" << std::endl;

  std::cout << "Измерение времени гибридного Introsort" << std::endl;

  std::cout << "Начало измерения алгоритма с массивами со случайными числами:" << std::endl;
  std::ofstream file4("intro_random.csv");
  file4 << "size,time_micros\n";

  for (int size : sizes) {
      std::vector<int> test_array = gen.getTestArray("random", size);
      long long avg_time = tester.testHybridIntrosort(test_array, 3);
      file4 << size << "," << avg_time << "\n";

      if (size % 20000 == 500) {
          std::cout << "  Size: " << size << " - Time: " << avg_time << " μs\n";
      }
  }
  file4.close();
  std::cout << "Конец измерения" << std::endl;

  std::cout << "Начало измерения алгоритма с обратно отсортированными массивами:" << std::endl;
  std::ofstream file5("intro_reverse_sorted.csv");
  file5 << "size,time_micros\n";

  for (int size : sizes) {
      std::vector<int> test_array = gen.getTestArray("reverse_sorted", size);
      long long avg_time = tester.testHybridIntrosort(test_array, 3);
      file5 << size << "," << avg_time << "\n";

      if (size % 20000 == 500) {
          std::cout << "  Size: " << size << " - Time: " << avg_time << " μs\n";
      }
  }
  file5.close();
  std::cout << "Конец измерения" << std::endl;

  std::cout << "Начало измерения алгоритма с почти отсортированными массивами:" << std::endl;
  std::ofstream file6("intro_almost_sorted.csv");
  file6 << "size,time_micros\n";

  for (int size : sizes) {
      std::vector<int> test_array = gen.getTestArray("almost_sorted", size);
      long long avg_time = tester.testHybridIntrosort(test_array, 3);
      file6 << size << "," << avg_time << "\n";

      if (size % 20000 == 500) {
          std::cout << "  Size: " << size << " - Time: " << avg_time << " μs\n";
      }
  }
  file6.close();
  std::cout << "Конец измерения" << std::endl;

  std::cout << "Все измерения завершены. Данные сохранены в CSV файлы." << std::endl;

  return 0;
}