//
// Created by mac on 11.11.2025.
//

#ifndef ARRAYGENERATOR_H
#define ARRAYGENERATOR_H



#pragma once
#include <random>
#include <vector>
#include <string>

class GeneratorArray {
private:
  int max_size = 100000;
  int min_value = 0;
  int max_value = 6000;

  std::mt19937 rng;

public:
  GeneratorArray();
  std::vector<int> generateRandomArray(int size);
  std::vector<int> generateReverseSortedArray(int size);
  std::vector<int> generateAlmostSortedArray(int size, int num_swaps = 10);
  std::vector<int> getTestArray(const std::string& type, int size);
};




#endif //ARRAYGENERATOR_H
