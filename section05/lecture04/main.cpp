#include <exception>
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <string>

std::mutex task_mutex;

void task(const std::string& str) {
    for (auto i = 0; i < 5; i++) {
        try {
            //std::lock_guard guard(task_mutex);
            std::unique_lock guard(task_mutex);

            std::cout << str[0] << str[1] << str[2] << std::endl;
            //throw std::exception();
            guard.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        catch (std::exception& e) {
            std::cout << "Exception caught: " << e.what() << '\n';
        }
    }
}

int main() {
    std::thread thr1(task, "abc");
    std::thread thr2(task, "def");
    std::thread thr3(task, "xyz");

    thr1.join(); thr2.join(); thr3.join();
    return 0;
}