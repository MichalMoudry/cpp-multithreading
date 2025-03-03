#include <iostream>
#include <thread>
#include <string>

void print(std::string str) noexcept {
    for (auto i = 0; i < 5; i++) {
        std::cout << str[0] << str[1] << str[2] << std::endl;
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