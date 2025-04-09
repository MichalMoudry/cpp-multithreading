#include <exception>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <string>
#include <thread>

class ConcurrentQueueException final : public std::runtime_error {
public:
    ConcurrentQueueException(std::string&& message)
        : std::runtime_error {message} {}
};

template <class T>
class ConcurrentQueue final {
private:
    std::queue<T> internal_queue;
    std::mutex mut;
    int max {50};
public:
    ConcurrentQueue() = default;
    ConcurrentQueue(const ConcurrentQueue&) = delete;
    ConcurrentQueue& operator=(const ConcurrentQueue&) = delete;
    ConcurrentQueue(ConcurrentQueue&&) = delete;
    ConcurrentQueue& operator=(ConcurrentQueue&&) = delete;

    void push(T value) {
        std::lock_guard guard {mut};
        if (internal_queue.size() > max) {
            throw ConcurrentQueueException {"Queue is full"};
        }
        internal_queue.push(value);
    }

    void pop(T& value) {
        std::unique_lock guard {mut};
        if (internal_queue.empty()) {
            throw ConcurrentQueueException {"Queue is empty"};
        }

        value = internal_queue.front();
        internal_queue.pop();
    }
};

ConcurrentQueue<std::string> queue;

void reader() {
    std::string data;

    std::cout << "Reader calling pop..." << std::endl;
    for (auto i {0}; i < 50; i++) {
        queue.pop(data);
        std::cout << "Reader recevied data: " << data << std::endl;
    }
}

void writer() {
    using namespace std::literals;
    std::this_thread::sleep_for(2s);
    for (auto i {0}; i < 51; i++) {
        queue.push("Item " + std::to_string(i));
    }

    std::cout << "Writer returned from push..." << std::endl;
}

int main() {
    auto write_future {std::async(std::launch::async, writer)};
    auto read_future {std::async(std::launch::async, reader)};

    try {
        read_future.get();
    }
    catch (std::exception& e) {
        std::cout << "Received error: " << e.what() << std::endl;
    }

    try {
        write_future.get();
    }
    catch (std::exception& e) {
        std::cout << "Received error: " << e.what() << std::endl;
    }

    return 0;
}