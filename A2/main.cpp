#include <fstream>
#include <iostream>
#include <vector>
#include "ArrayGenerator.h"
#include "SortTester.h"
#include <chrono>

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

void mergeSort(std::vector<int> &v, int l, int r) {
  if (l >= r) {
    return;
  }
  if (r - l + 1 <= 15) {
    insertionSort(v, l, r);
    return;
  }

  int mid = l + (r - l) / 2;
  mergeSort(v, l, mid);
  mergeSort(v, mid + 1, r);

  std::vector<int> tmp(r - l + 1);
  int i = l, j = mid + 1;
  int k = 0;
  while (i <= mid && j <= r) {
    if (v[i] <= v[j]) {
      tmp[k] = v[i];
      i++;
    } else {
      tmp[k] = v[j];
      j++;
    }
    k++;
  }

  while (i <= mid) {
    tmp[k] = v[i];
    i++;
    k++;
  }
  while (j <= r) {
    tmp[k] = v[j];
    j++;
    k++;
  }

  for (int ind = 0; ind < tmp.size(); ind++) {
    v[ind + l] = tmp[ind];
  }
}

void standartMerge(std::vector<int> &v, int l, int r) {
  if (l >= r) {
    return;
  }

  int mid = l + (r - l) / 2;
  standartMerge(v, l, mid);
  standartMerge(v, mid + 1, r);

  std::vector<int> tmp(r - l + 1);
  int i = l, j = mid + 1;
  int k = 0;
  while (i <= mid && j <= r) {
    if (v[i] <= v[j]) {
      tmp[k] = v[i];
      i++;
    } else {
      tmp[k] = v[j];
      j++;
    }
    k++;
  }

  while (i <= mid) {
    tmp[k] = v[i];
    i++;
    k++;
  }
  while (j <= r) {
    tmp[k] = v[j];
    j++;
    k++;
  }

  for (int ind = 0; ind < tmp.size(); ind++) {
    v[ind + l] = tmp[ind];
  }
}

int main() {
  GeneratorArray gen;
  SortTester tester;
  std::vector<int> sizes;
  for (int size = 500; size <= 100000; size += 100) {
    sizes.push_back(size);
  }

  std::cout << "Измерение времени стандартного Merge Sort" << std::endl;
  std::cout << "Начало измерения алгоритма с массивами со случайными часлами:" << std::endl;
  std::ofstream file1("random-1.csv");
  file1 << "size,time_micros\n";

  for (int size : sizes) {
    std::vector<int> test_array = gen.getTestArray("random", size);
    long long avg_time = tester.testStandardMergeSort(test_array, 3);
    file1 << size << "," << avg_time << "\n";

    if (size % 20000 == 500) {
      std::cout << "  Size: " << size << " - Time: " << avg_time << " μs\n";
    }
  }
  file1.close();
  std::cout << "Конец измерения" << std::endl;

  std::cout << "Начало измерения алгоритма с обратно отсортированными массивами:" << std::endl;

  std::ofstream file2("reverse_sorted-1.csv");
  file2 << "size,time_micros\n";

  for (int size : sizes) {
    std::vector<int>  test_array = gen.getTestArray("reverse_sorted", size);
    long long avg_time = tester.testStandardMergeSort(test_array, 3);
    file2 << size << "," << avg_time << "\n";

    if (size % 20000 == 500) {
      std::cout << "  Size: " << size << " - Time: " << avg_time << " μs\n";
    }
  }
  file2.close();
  std::cout << "Конец измерения" << std::endl;

  std::cout << "Начало измерения алгоритма с почти отсортированными массивами:" << std::endl;
  std::ofstream file3("almost_sorted-1.csv");
  file3 << "size,time_micros\n";

  for (int size : sizes) {
    std::vector<int>  test_array = gen.getTestArray("almost_sorted", size);
    long long avg_time = tester.testStandardMergeSort(test_array, 3);
    file3 << size << "," << avg_time << "\n";

    if (size % 20000 == 500) {
      std::cout << "  Size: " << size << " - Time: " << avg_time << " μs\n";
    }
  }
  file3.close();
  std::cout << "Конец измерения" << std::endl;

  std::cout << "Измерение времени  Merge Sort c Insertion Sort" << std::endl;

  std::cout << "Начало измерения алгоритма с массивами со случайными часлами:" << std::endl;

  std::ofstream file4("random-2.csv");
  file4 << "size,time_micros\n";
  for (int size : sizes) {
    std::vector<int> test_array = gen.getTestArray("random", size);
    long long avg_time = tester.testHybridMergeSort(test_array, 3);
    file4 << size << "," << avg_time << "\n";
    if (size % 20000 == 500) {
      std::cout << "  Size: " << size << " - Time: " << avg_time << " μs\n";
    }
  }
  file4.close();
  std::cout << "Конец измерения" << std::endl;

  std::cout << "Начало измерения алгоритма с обратно отсортированными массивами:" << std::endl;

  std::ofstream file5("reverse_sorted-2.csv");
  file5 << "size,time_micros\n";
  for (int size : sizes) {
    std::vector<int> test_array = gen.getTestArray("reverse_sorted", size);
    long long avg_time = tester.testHybridMergeSort(test_array, 3);
    file5 << size << "," << avg_time << "\n";
    if (size % 20000 == 500) {
      std::cout << "  Size: " << size << " - Time: " << avg_time << " μs\n";
    }
  }
  file5.close();
  std::cout << "Конец измерения" << std::endl;

  std::cout << "Начало измерения алгоритма с почти отсортированными массивами:" << std::endl;

  std::ofstream file6("almost_sorted-2.csv");
  file6 << "size,time_micros\n";
  for (int size : sizes) {
    std::vector<int> test_array = gen.getTestArray("almost_sorted", size);
    long long avg_time = tester.testHybridMergeSort(test_array, 3);
    file6 << size << "," << avg_time << "\n";
    if (size % 20000 == 500) {
      std::cout << "  Size: " << size << " - Time: " << avg_time << " μs\n";
    }
  }
  file6.close();
  std::cout << "Конец измерения" << std::endl;

  return 0;
}
