#include <condition_variable>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <string>
#include <thread>
#include <iostream>
#include <future>

using namespace std::literals;

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
    std::condition_variable cv;
    const int max {50};
public:
    ConcurrentQueue() = default;
    ConcurrentQueue(const ConcurrentQueue&) = delete;
    ConcurrentQueue& operator=(const ConcurrentQueue&) = delete;
    ConcurrentQueue(ConcurrentQueue&&) = delete;
    ConcurrentQueue& operator=(ConcurrentQueue&&) = delete;

    void push(T value) {
        std::unique_lock guard {mut};

        while (internal_queue.size() > max) {
            guard.unlock();
            std::this_thread::sleep_for(50ms);
            guard.lock();
        }

        cv.notify_one();
    }

    void pop(T& value) {
        std::unique_lock guard {mut};
        cv.wait(guard, [this] {
            return !internal_queue.empty();
        });
        value = internal_queue.front();
        internal_queue.pop();
    }
};

ConcurrentQueue<std::string> queue;

void reader() {
    std::string data;

    std::cout << "Reader calling pop..." << std::endl;
    for (auto i {0}; i < 60; i++) {
        queue.pop(data);
        std::cout << "Reader recevied data: " << data << std::endl;
    }
}

void writer() {
    std::this_thread::sleep_for(2s);
    for (auto i {0}; i < 60; i++) {
        queue.push("Item " + std::to_string(i));
    }

    std::cout << "Writer returned from push..." << std::endl;
}

int main() {
    auto write_future {std::async(std::launch::async, writer)};
    auto read_future {std::async(std::launch::async, reader)};

    read_future.wait();
    write_future.wait();
    return 0;
}