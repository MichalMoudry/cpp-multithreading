#include <string>
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

// global mutex object
std::mutex task_mutex;

void task(const std::string& str) {
    for (auto i = 0; i < 5; i++) {
        task_mutex.lock();
        std::cout << str[0] << str[1] << str[2] << std::endl;
        task_mutex.unlock();
    }
}

void task1() {
    std::cout << "Task1 trying to lock the mutex" << std::endl;
    while (task_mutex.try_lock()) {
        std::cout << "Task1 could not lock the mutex" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "Task1 locked the mutex" << std::endl;
    task_mutex.unlock();
    std::cout << "Task1 unlocking the mutext" << std::endl;
}

int main() {
    std::thread thr(task1);
    thr.join();
    /*std::thread thr(task, "abc");
    std::thread thr2(task, "def");
    thr.join();
    thr2.join();*/
    return 0;
}