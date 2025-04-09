#include <mutex>
#include <iostream>

template<typename T>
class Monitor final {
    T data;
    std::mutex mut;
public:
    Monitor<T>(T data = T{}) : data(data) {}

    template<typename Func>
    auto operator() (Func func) {
        std::lock_guard guard {mut};
        return func(data);
    }
};

class Bank final {
public:
    void debit(const std::string& name, int amount) {
        std::cout << "Debiting " << amount << " from " << name << std::endl;
    }

    void credit(const std::string& name, int amount) {
        std::cout << "Crediting " << amount << " from " << name << std::endl;
    }

    void print(const std::string& name) {
        std::cout << "Displaying account for " << name << std::endl;
    }
};

int main() {
    Monitor<Bank> monitor;
    monitor([](Bank bank) {
        bank.debit("Peter", 1'000);
        bank.credit("Paul", 1'000);
        bank.print("Peter");
        bank.print("Paul");
    });
    /*auto monitor {Bank{}};
    monitor.print("");*/
    return 0;
}