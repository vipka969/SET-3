#include <vector>
#include <string>
#include <chrono>
#include "SortTester.h"


long long SortTester::testStandardMergeSort(const std::vector<int>& original_arr, int num_runs) {
  long long total_time = 0;

  for (int i = 0; i < num_runs; i++) {
    std::vector<int> arr_copy = original_arr;

    auto start = std::chrono::high_resolution_clock::now();
    standartMerge(arr_copy, 0, arr_copy.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();

    total_time += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  }

  return total_time / num_runs;
}

long long SortTester::testHybridMergeSort(const std::vector<int>& original_arr, int threshold, int num_runs) {
  long long total_time = 0;

  for (int i = 0; i < num_runs; i++) {
    std::vector<int> arr_copy = original_arr;

    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(arr_copy, 0, arr_copy.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();

    total_time += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  }

  return total_time / num_runs;
}
