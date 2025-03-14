#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>

std::mutex mut1;
std::mutex mut2;

void func1() {
    std::cout << "Thread A trying to lock mutex 1...\n";
    std::lock_guard l_guard(mut1);
    std::cout << "Thread A has locked mutex 1...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::cout << "Thread A trying to lock mutex 2...\n";
    std::lock_guard l_guard2(mut2);
    std::cout << "Thread A has locked mutex 2...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Thread A releases all its locks";
}

void func2() {
    std::cout << "Thread B trying to lock mutex 1...\n";
    std::lock_guard l_guard(mut1);
    std::cout << "Thread B has locked mutex 1...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::cout << "Thread B trying to lock mutex 2...\n";
    std::lock_guard l_guard2(mut2);
    std::cout << "Thread B has locked mutex 2...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Thread B releases all its locks";
}

int main() {
    std::thread thr1(func1);
    std::thread thr2(func2);

    thr1.join();
    thr2.join();
    return 0;
}