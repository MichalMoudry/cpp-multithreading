#include <iostream>
#include <utility>
#include <vector>

void print_vector(const std::vector<int>& vec) {
    for (const auto& item : vec) {
        std::cout << item;
        if (item != vec.back()) {
            std::cout << ',';
        }
    }
    std::cout << std::endl;
}

int partition(std::vector<int>& vec, int leftIndex, int rightIndex) {
    auto pivot = vec[leftIndex];
    auto i = leftIndex;

    for(auto j = leftIndex + 1; j < rightIndex; j++) {
        if(vec[j] <= pivot) {
            i += 1;
            std::swap(vec[i], vec[j]);
        }
    }

    std::swap(vec[i], vec[leftIndex]);
    return i;
}

void quick_sort(std::vector<int>& vec, int leftIndex, int rightIndex) {
    if (vec.size() == 0) {
        return;
    }

    int pivot;
    if (leftIndex < rightIndex) {
        pivot = partition(vec, leftIndex, rightIndex);
        quick_sort(vec, leftIndex, pivot);
        quick_sort(vec, pivot + 1, rightIndex);
    }
}

//https://stackoverflow.com/questions/22504837/how-to-implement-quick-sort-algorithm-in-c
int main() {
    auto vec = std::vector<int>{52, 96, 67, 71, 42, 38, 39, 40, 14};
    print_vector(vec);

    quick_sort(vec, 0, vec.size());

    print_vector(vec);
    return 0;
}
