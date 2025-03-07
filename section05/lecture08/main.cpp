#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

std::mutex mut;

auto x {0};

void write() {
    std::lock_guard guard(mut);
    // start of critical section
    x++;
    // end of critical section
}

void read() {
    std::lock_guard guard(mut);
    // start of critical section
    std::this_thread::sleep_for(
        std::chrono::milliseconds(100)
    );
    // end of critical section
}

int main() {
    std::vector<std::thread> threads;
    for (auto i {0}; i < 20; i++) {
        threads.push_back(std::thread(read));
    }
    threads.push_back(std::thread(write));
    threads.push_back(std::thread(write));

    for (auto i {0}; i < 20; i++) {
        threads.push_back(std::thread(read));
    }

    for (auto& thr : threads) {
        thr.join();
    }

    return 0;
}