#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string str {"Hello world!"};
    std::cout << "String to search: " << str << std::endl;
    std::cout << "Searching for first occurrence of 'o'\n";

    auto res {std::find(str.cbegin(), str.cend(), 'o')};
    if (res != str.cend()) {
        std::cout << "Found a matching element at index: " << res - str.cbegin() << std::endl;
        std::cout << "At this point in the string: ";
        for (auto i {res}; i != str.cend(); i++) {
            std::cout << *i;
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "No matching element\n";
    }
    return 0;
}