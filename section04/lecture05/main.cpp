#include <iostream>
#include <thread>
#include <string>

void print(const std::string str) noexcept {
    for (const auto& ch : str) {
        std::cout << ch;
    }
}

int main() {
    std::thread thr1(print, "abc");
    std::thread thr2(print, "def");
    std::thread thr3(print, "xyz");

    thr1.join();
    thr2.join();
    thr3.join();
    return 0;
}