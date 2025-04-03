#include <functional>
#include <future>
#include <iostream>
#include <thread>

using namespace std::literals;

void task(std::promise<int>& promise, int a, int b) {
    std::this_thread::sleep_for(2s);
    promise.set_value(a + b);
}

void print_result(std::future<int>& future) {
    std::cout << "Waiting for result\n";
    std::cout << "Result is: " << future.get() << std::endl;
}

int main() {
    std::promise<int> promise;
    auto future {promise.get_future()};

    std::thread calc_thread{task, std::ref(promise), 5, 13};
    std::thread printer_thread{print_result, std::ref(future)};

    calc_thread.join(); printer_thread.join();
    return 0;
}