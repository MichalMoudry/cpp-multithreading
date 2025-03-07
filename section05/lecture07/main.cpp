#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>

std::timed_mutex time_mutex;

void task1() {
    std::cout << "Task1 trying to lock the mutex\n";
    time_mutex.lock();
    std::cout << "Task 1 locks the mutex\n";
    std::this_thread::sleep_for(
        std::chrono::seconds(5)
    );
    std::cout << "Task 1 unlocking the mutex\n";
    time_mutex.unlock();
}

void task2() {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(500)
    );
    std::cout << "Task 2 trying to lock the mutex\n";
    while (!time_mutex.try_lock_for(std::chrono::seconds(1))) {
        std::cout << "Task 2 couldn't lock the mutex\n";
    }

    std::cout << "Task 2 has locked the mutex\n";
    time_mutex.unlock();
}

int main() {
    std::thread thr1(task1);
    std::thread thr2(task2);

    thr1.join(); thr2.join();

    return 0;
}