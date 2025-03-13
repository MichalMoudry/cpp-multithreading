#include <ostream>
#include <thread>
#include <random>
#include <iostream>

thread_local std::mt19937 mt;

void func() {
    std::uniform_real_distribution<double> dist(0, 1);
    for (auto i {0}; i < 10; i++) {
        std::cout << dist(mt) << ", ";
    }
}

int main() {
    std::cout << "Thread 1's random value:\n";
    std::thread thr1(func);
    thr1.join();
    std::cout << std::endl;

    std::cout << "Thread 2's random value:\n";
    std::thread thr2(func);
    thr2.join();
    std::cout << std::endl;
    return 0;
}