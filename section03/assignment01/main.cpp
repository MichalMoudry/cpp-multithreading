#include <iostream>
#include <thread>
#include <string>
#include <vector>

std::string fizzbuzz(int input) {
    std::string result {};
    if (input % 3 == 0) {
        result += "fizz";
    }
    if (input % 5 == 0) {
        result += "buzz";
    }
    if (result == "") {
        result = std::to_string(input);
    }
    return result;
}

void run_fizzbuzz(int round_count) {
    std::vector<std::string> players {
        "Abdul",
        "Bart",
        "Claudia",
        "Divya"
    };
    int count {0};
    for (int i = 0; i < round_count; i++) {
        for (auto& player : players) {
            count += 1;
            std::cout << player << " says " << fizzbuzz(count) << std::endl;
        }
    }
}

int main() {
    std::cout << "Assignment 01 start!\n";

    std::thread thr(run_fizzbuzz, 2);
    thr.join();
}