#include <memory>
#include <iostream>

int main() {
    std::shared_ptr<int> ptr1(new int(41));
    auto ptr2 {std::make_shared<int>(42)};

    std::cout << "Pointer 1: " << *ptr1 << std::endl;
    std::cout << "Pointer 2 " << *ptr2 << std::endl;

    return 0;
}