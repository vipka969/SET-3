#ifndef SORTTESTER_H
#define SORTTESTER_H

#pragma once
#include <vector>
#include "ArrayGenerator.h"

void mergeSort(std::vector<int> &v, int l, int r);
void standartMerge(std::vector<int> &v, int l, int r);

class SortTester {
  private:
  GeneratorArray gen;
public:
  long long testStandardMergeSort(const std::vector<int>& original_arr, int num_runs = 3);

  long long testHybridMergeSort(const std::vector<int>& original_arr, int threshold = 15, int num_runs = 3);
};

#endif //SORTTESTER_H
