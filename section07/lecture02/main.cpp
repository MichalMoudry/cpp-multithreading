#include <atomic>
#include <iostream>

int main() {
    std::atomic<int> x {0};
    std::cout << "After initialization: x = " << x << std::endl;

    x = 2;
    int y {x};
    std::cout << "After assignment: x = " << x << ", y = " << y << std::endl;

    x.store(3);
    std::cout << "After store: x = " << x.load() << std::endl;

    std::cout << "Exchange returns " << x.exchange(y) << std::endl;
    std::cout << "After exchange: x = " << x << ", y = " << y << std::endl;
    return 0;
}