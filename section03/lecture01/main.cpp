#include <iostream>
#include <thread>

void hello() {
    std::cout << "Hello, thread!\n";
}

class Functor final {
public:
    void operator()() {
        std::cout << "Hello, Functor thread!\n";
    }
};

int main() {
    Functor func;
    std::thread thr([]() {
        std::cout << "Hello, Lambda thread!\n";
    });
    thr.join(); // wait for thread to complete
}