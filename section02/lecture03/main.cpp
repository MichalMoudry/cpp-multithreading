#include <iostream>
#include <vector>
#include <string>

void func(std::vector<std::string> arg) {
    std::cout << "Argument vector has " << arg.size() << " elements" << std::endl;
}

void r_val_func(int&& x) {
    std::cout << "Rvaliue reference" << std::endl;
}

int main() {
    std::vector<std::string> vec (1'000'000);
    std::cout << "Size before: " << vec.size() << " elements" << std::endl;
    func(vec);
    std::cout << "Size after: " << vec.size() << " elements" << std::endl;

    int test {3};
    r_val_func(4);
    // r_val_func(test); => compiler err
}