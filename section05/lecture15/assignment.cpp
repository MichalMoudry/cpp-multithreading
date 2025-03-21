#include <mutex>
#include <string>
#include <thread>
#include <iostream>

using namespace std::literals;

int x{0};

std::mutex mut;

void func(const std::string& thread_name) {
    mut.lock();
    std::cout << '\n' << thread_name << std::endl;
    while (x == 0) {
        std::cout << "X is: " << x << std::endl;
        x = 1 - x;
        std::cout << "X is: " << x << std::endl;
    }
    mut.unlock();
}

int main() {
    std::thread thr1{ func, "thr1" };
    std::thread thr2{ func, "thr2" };
    thr1.join(); thr2.join();
}