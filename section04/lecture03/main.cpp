#include <exception>
#include <iostream>
#include <thread>

class thread_guard final {
    std::thread thr;
public:
    thread_guard(std::thread&& thr_arg) : thr(std::move(thr_arg)) {}

    ~thread_guard() {
        if (thr.joinable()) {
            thr.join();
        }
    }
};

void hello() noexcept {
    std::cout << "Hello, thread!\n";
}

int main() {
    try {
        std::thread thr(hello);
        auto guard {thread_guard(std::move(thr))};
        throw std::exception();
    } catch (std::exception& e) {
        std::cout << "Exception caught: " << e.what() << '\n';
    }
    return 0;
}