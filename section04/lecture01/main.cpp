#include <chrono>
#include <iostream>
#include <thread>

void hello() {
    std::cout << "Hello, Thread!" << std::endl;
}

int main() {
    std::thread thr(hello);
    std::cout << "Hello thread has native handle: " << thr.native_handle() << '\n';
    std::cout << "Thread ID: " << thr.get_id() << '\n';
    thr.join();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}