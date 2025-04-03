#include <future>
#include <iostream>
#include <thread>

using namespace std::literals;

void task() {
    std::this_thread::sleep_for(5s);
    std::cout << "Task result: " << 42 << std::endl;
}

void func() {
    std::cout << "Calling async\n";
    auto res {std::async(std::launch::async, task)};
}

int main() {
    func();
    std::cout << "Task started\n";
    return 0;
}