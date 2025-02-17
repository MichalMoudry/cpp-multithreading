#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <utility>

void hello(std::string str) {
    std::cout << str << '\n';
}

void func(std::string&& str) {
    std::cout << "Ownership of \"" << str << "\" transferred to thread\n";
}

void func_with_ref(const std::string& str) {
    std::cout << "Str ref: " << str << '\n';
}

int main() {
    std::thread thr(hello, "Hello, Thread!");
    thr.join();

    std::string str {"moveable"};
    std::cout << "Str val before: " << str << std::endl;
    std::thread thr2(func, std::move(str));
    thr2.join();
    std::cout << "Str val after: " << str << std::endl;

    auto ref_str {std::string{"str for ref"}};
    auto ref = &ref_str;
    func_with_ref(std::ref(ref_str));
    std::cout << "Str size: " << sizeof(ref_str) << '\n';
}