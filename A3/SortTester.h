#ifndef SORTTESTER_H
#define SORTTESTER_H

#include <vector>
#include <string>
#include <chrono>
#include "ArrayGenerator.h"

class SortTester {
private:
  GeneratorArray gen;

public:
  long long testStandardQuickSort(const std::vector<int>& v, int num_runs = 5);

  long long testHybridIntrosort(const std::vector<int>& v, int num_runs = 5);

};

#endif // SORTTESTER_H