#include "ArrayGenerator.h"
#include <vector>
#include <random>
#include <algorithm>
#include <functional>


GeneratorArray:: GeneratorArray() {}

std::vector<int> GeneratorArray::generateRandomArray(int size) {
    std::uniform_int_distribution<int> dist(min_value, max_value);
    std::vector<int> arr(size);

    for (int i = 0; i < size; i++) {
        arr[i] = dist(rng);
    }
    return arr;
}

std::vector<int> GeneratorArray::generateReverseSortedArray(int size) {
    std::vector<int> arr = generateRandomArray(size);
    std::sort(arr.begin(), arr.end(), std::greater<int>());
    return arr;
}

std::vector<int> GeneratorArray::generateAlmostSortedArray(int size, int num_swaps) {
    std::vector<int> arr = generateRandomArray(size);
    std::sort(arr.begin(), arr.end());

    std::uniform_int_distribution<int> index_dist(0, size - 1);

    for (int i = 0; i < num_swaps; i++) {
        int ind1 = index_dist(rng);
        int ind2 = index_dist(rng);
        std::swap(arr[ind1], arr[ind2]);
    }
    return arr;
}

std::vector<int> GeneratorArray::getTestArray(const std::string& type, int size) {
    std::vector<int> arr;

    if (type == "random") {
        arr = generateRandomArray(max_size);
    } else if (type == "reverse_sorted") {
        arr = generateReverseSortedArray(max_size);
    } else if (type == "almost_sorted") {
        arr = generateAlmostSortedArray(max_size);
    }

    return std::vector<int>(arr.begin(), arr.begin() + size);
}