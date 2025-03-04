#include <thread>
#include <iostream>

int global_int {0};

void iter() {
    for (auto i = 0; i < 100'000; i++) {
        global_int += 1;
    }
}

int main() {
    std::thread thr(iter);
    std::thread thr2(iter);

    thr.join();
    thr2.join();

    std::cout << "Global int value is: " << global_int << '\n';
    return 0;
}