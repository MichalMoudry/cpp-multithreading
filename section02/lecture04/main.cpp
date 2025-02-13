#include <memory>
#include <string>
#include <iostream>
#include <utility>

struct Test {
    int val1;
    std::string val2;
};

class TestClass final {
public:
    TestClass(const Test&) = delete;
    TestClass& operator =(const TestClass&) = delete;
    TestClass(TestClass&&) noexcept = default;
    TestClass& operator =(TestClass&&) noexcept = default;
    TestClass() = default;
};

void func(const Test& test) {
    std::cout << "Lvalue: " << test.val1 << " | " << test.val2 << std::endl;
}

void func(const Test&& test) {
    std::cout << "Rvalue: " << test.val1 << " | " << test.val2 << std::endl;
}

int main() {
    Test values {1, "Test value"};
    auto values2 {std::unique_ptr<Test>{new Test{2, "Test value 2"}}};

    func(values);
    func(std::move(values));

    TestClass test {};
    TestClass test2 {std::move(test)};
}