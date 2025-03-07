#include <vector>
#include <thread>
#include <iostream>

class Singleton final {
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
    Singleton() {
        std::cout << "Initializing singleton" << std::endl;
    }
};

Singleton& get_instance() {
    static Singleton instance;
    return instance;
}

void task() {
    Singleton& single = get_instance();
    std::cout << &single << std::endl;
}

int main() {
    std::vector<std::thread> threads;
    for (auto i {0}; i < 20; i++) {
        threads.push_back(std::thread(task));
    }

    for (auto& thr : threads) {
        thr.join();
    }
    return 0;
}