#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Semaphore final {
private:
    std::mutex mut;
    std::condition_variable cv;
    int counter {0};
    int max_counter {10};
public:
    void release() {
        std::lock_guard guard {mut};
        std::cout << "Adding one item" << std::endl;

        if (counter < max_counter) {
            counter += 1;
            count();
        }

        cv.notify_all();
    }

    void acquire() {
        std::unique_lock lock {mut};
        std::cout << "Removing one item" << std::endl;

        while (counter == 0) {
            cv.wait(lock);
        }

        counter -= 1;
        count();
    }

    void count() const {
        std::cout << "Value of counter: " << counter << std::endl;
    }
};

int main() {
    Semaphore sem;
    std::cout << "Size of semaphore " << sizeof sem << std::endl;

    auto insert {[&sem] {
        sem.release();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }};

    auto relinquish {[&sem] {
        sem.acquire();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }};

    std::vector<std::thread> tasks;
    for (auto i {0}; i < 2; i++) {
        tasks.push_back(std::thread {insert});
    }
    for (auto i {0}; i < 4; i++) {
        tasks.push_back(std::thread {relinquish});
    }
    for (auto i {0}; i < 3; i++) {
        tasks.push_back(std::thread {insert});
    }

    for (auto& task : tasks) {
        task.join();
    }
    return 0;
}