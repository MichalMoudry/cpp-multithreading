#include <atomic>
#include <thread>
#include <iostream>
#include <vector>

std::atomic_flag lock_cout = ATOMIC_FLAG_INIT;

void task(int n) {
    while (lock_cout.test_and_set()) {}

    using namespace std::literals;
    std::this_thread::sleep_for(50ms);
    std::cout << "I'm a task with argument " << n << std::endl;
    lock_cout.clear();
}

int main() {
    std::vector<std::thread> tasks;
    for (auto i {0}; i < 10; i++) {
        tasks.push_back(std::thread(task, i));
    }

    for (auto& thr : tasks) {
        thr.join();
    }
    return 0;
}