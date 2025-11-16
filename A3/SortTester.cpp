#include "SortTester.h"
#include <vector>
#include <chrono>

extern void quickSort(std::vector<int>& arr, int low, int high);
extern void introsort(std::vector<int>& arr);

long long SortTester::testStandardQuickSort(const std::vector<int>& v, int num_runs) {
  long long total_time = 0;

  for (int i = 0; i < num_runs; i++) {
    std::vector<int> arr_copy = v;

    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr_copy, 0, arr_copy.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();

    total_time += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  }

  return total_time / num_runs;
}

long long SortTester::testHybridIntrosort(const std::vector<int>& v, int num_runs) {
  long long total_time = 0;

  for (int i = 0; i < num_runs; i++) {
    std::vector<int> arr_copy = v;

    auto start = std::chrono::high_resolution_clock::now();
    introsort(arr_copy);
    auto end = std::chrono::high_resolution_clock::now();

    total_time += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  }

  return total_time / num_runs;
}