#include <functional>
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <chrono>

template <typename T>
class SharedVector final {
private:
    std::vector<T> data;
    std::mutex vec_mutex;
public:
    SharedVector<T>() = default;
    SharedVector<T>(std::vector<T>&& new_data)
        : data(new_data) {}
    void add(const T& item) {
        vec_mutex.lock();
        data.push_back(item);
        vec_mutex.unlock();
    }
    void print() {
        vec_mutex.lock();
        for (auto& item : data) {
            std::cout << item << ", ";
        }
        vec_mutex.unlock();
    }
};

void func(SharedVector<int>& vec) {
    for (auto i = 0; i < 5; i++) {
        vec.add(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        vec.print();
    }
}

int main() {
    auto test_vec {SharedVector<int>()};

    std::thread thr1(func, std::ref(test_vec));
    std::thread thr2(func, std::ref(test_vec));
    std::thread thr3(func, std::ref(test_vec));

    thr1.join(); thr2.join(); thr3.join();
    return 0;
}