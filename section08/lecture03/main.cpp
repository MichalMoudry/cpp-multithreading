#include <algorithm>
#include <vector>
#include <exception>
#include <iostream>

int main() {
    std::vector<int> vec {3, 1, 4, 1, 5, 9};
    try {
        std::sort(vec.begin(), vec.end(), [](int a, int b) {
            throw std::out_of_range("err");
            return true;
        });
    }
    catch (std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    for (auto v : vec) {
        std::cout << v << '\n';
    }
    std::cout << std::endl;

    return 0;
}