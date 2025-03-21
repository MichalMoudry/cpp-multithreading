#include <iostream>
#include <mutex>
#include <thread>
#include <string>

using namespace std::literals;

std::mutex mut1;

void print(const std::string& value) {
    std::cout << value << std::endl;
}

void func_a() {
    auto is_locked {false};
    while (!is_locked) {
        std::lock_guard lck_guard(mut1);
        print("Test value from 'func_a'");
        is_locked = true;
    }
}

void func_b() {
    print("Test value from 'func_b'");
}

int main() {
    return 0;
}