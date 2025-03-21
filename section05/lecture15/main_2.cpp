#include <thread>
#include <mutex>
#include <iostream>

using namespace std::literals;

std::mutex mut1, mut2;

void func_a() {
    std::this_thread::sleep_for(10ms);
    std::cout << "After you, Claude!\n";
    std::scoped_lock scoped_lck(mut1, mut2);
    std::this_thread::sleep_for(2s);

    std::cout << "ThreadA has locked both mutexes\n";
}

void func_b() {
    auto is_locked {false};
    std::cout << "After you, Cecil!\n";
    std::scoped_lock scoped_lck(mut2, mut1);
    std::this_thread::sleep_for(2s);
    std::cout << "Thread B has locked both mutexes\n";
}

int main() {
    std::thread thr_a(func_a);
    std::this_thread::sleep_for(10ms);
    std::thread thr_b(func_b);

    thr_a.join(); thr_b.join();
    return 0;
}