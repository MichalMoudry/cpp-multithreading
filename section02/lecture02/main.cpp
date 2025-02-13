#include <iostream>

int main() {
    int n {2};
    auto func = [n](int arg) { return 2 * arg + n; };
    std::cout << "2 * arg of 2 + " << n << " = " << func(2) << std::endl;
}