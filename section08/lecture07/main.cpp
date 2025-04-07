#include <iostream>
#include <mutex>
#include <string>
#include <thread>

class Bank final {
    std::mutex mut;
public:
    void debit(const std::string& name, int amount) {
        std::lock_guard guard {mut};
        std::cout << "Debiting " << amount << " from " << name << std::endl;
    }

    void credit(const std::string& name, int amount) {
        std::lock_guard guard {mut};
        std::cout << "Crediting " << amount << " from " << name << std::endl;
    }

    void print(const std::string& name) {
        std::lock_guard guard {mut};
        std::cout << "Displaying account for " << name << std::endl;
    }
};

int main() {
    Bank bank;
    std::thread thr([&bank] {
        bank.debit("Peter", 1'000);
        bank.credit("Paul", 1'000);
        bank.print("Peter");
        bank.print("Paul");
    });

    thr.join();
    std::cout << "Done\n";
    return 0;
}