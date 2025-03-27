#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int> counter {0};

void task() {
    for (auto i {0}; i < 100'000; i++) {
        counter += 1;
    }
}

int main() {
    std::vector<std::thread> tasks;
    for (auto i {0}; i < 10; i++) {
        tasks.push_back(std::thread(task));
    }

    for (auto& thr : tasks) {
        thr.join();
    }

    std::cout << "Counter: " << counter << std::endl;
    return 0;
}