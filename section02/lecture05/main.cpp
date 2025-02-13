#include <iostream>
#include <memory>
#include <random>

struct Point {
    int x;
    int y;
};

int main() {
    std::mt19937 mt;
    std::cout << "5 random ints between 0 and 100:\n";
    std::uniform_int_distribution<int> uid(0, 100);
    for (int i = 0; i < 5; i++) {
        std::cout << uid(mt) << ", ";
    }
    std::cout << std::endl;

    std::cout << "5 random floats between 0 and 1:\n";
    std::uniform_real_distribution<double> did(0, 1);
    for (int i = 0; i < 5; i++) {
        std::cout << did(mt) << ", ";
    }
    std::cout << std::endl;

    auto test = std::make_unique<Point>(Point {3, 6});
    std::cout << test->x << ", " << test->y << '\n';
}