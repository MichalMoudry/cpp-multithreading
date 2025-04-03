#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> vec {1, 2, 3, 4};
    std::vector<int> vec2;

    std::transform(vec.begin(), vec.end(), std::back_inserter(vec2), [](int n) {
        return n*2;
    });

    std::cout << "Input vector: ";
    for (auto v : vec) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;

    std::cout << "Output vector: ";
    for (auto v : vec2) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;
    return 0;
}