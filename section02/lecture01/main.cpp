#include <iostream>
#include <string>
#include <chrono>
#include <vector>

namespace sc = std::chrono;

void func(int i) {
    std::cout << "func(int) called\n";
}

void func(int* i) {
    std::cout << "func(int*) called\n";
}

int main() {
    int x {7};
    std::string str {"Let us begin"};

    std::cout << "x = " << x << std::endl;
    std::cout << "str = " << str << std::endl;

    //int y = 7.7;
    //int y {7.7}; => err
    int y {7};
    std::cout << "y = " << y << std::endl;

    func(nullptr);

    sc::seconds {2}; // 2 sec interval
    sc::milliseconds {20};
    sc::microseconds {50};

    std::vector<int> ints {1, 2, 3};
    for (auto item : ints) {
        std::cout << item << std::endl;
    }
}
