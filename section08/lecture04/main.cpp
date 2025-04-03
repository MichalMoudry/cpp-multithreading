#include <iostream>
#include <numeric>
#include <vector>
int main() {
    std::vector<int> vec {0, 1, 2, 3, 4, 5, 6, 7};
    std::cout << "Vector elements: ";
    for (auto v : vec) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;

    auto sum {std::accumulate(vec.begin(), vec.end(), 0)};
    std::cout << "Result of accumulate: " << sum << std::endl;

    std::vector<int> vec2 {1, 2, 3, 4};
    std::vector<int> vec3 (vec2.size());
    std::inclusive_scan(vec2.begin(), vec2.end(), vec3.begin());
    std::cout << "Vector elements: ";
    for (auto v : vec2) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;
    std::cout << "Result of partial sum: ";
    for (auto v : vec3) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;

    return 0;
}