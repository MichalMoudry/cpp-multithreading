#include <condition_variable>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

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
public:
    ConcurrentQueue() = default;
    ConcurrentQueue(const ConcurrentQueue&) = delete;
    ConcurrentQueue& operator=(const ConcurrentQueue&) = delete;
    ConcurrentQueue(ConcurrentQueue&&) = delete;
    ConcurrentQueue& operator=(ConcurrentQueue&&) = delete;

    void push(T value) {
        std::lock_guard guard {mut};
        internal_queue.push(value);
        cv.notify_one();
    }

    void pop(T& value) {
        std::unique_lock guard {mut};
        cv.wait(guard, [this] { return !internal_queue.empty(); });
        value = internal_queue.front();
        internal_queue.pop();
    }
};

using Func = std::function<void()>;
using namespace std::literals;

class ThreadPool final {
private:
    ConcurrentQueue<Func> internal_queue;
    std::vector<std::thread> threads;

    void worker() {
        while (true) {
            Func task;
            internal_queue.pop(task);
            task();
        }
    }
public:
    ThreadPool() {
        for (auto i {0}; i < std::thread::hardware_concurrency(); i++) {
            threads.push_back(std::thread{&ThreadPool::worker, this});
        }
    }

    ~ThreadPool() {
        for (auto& thread : threads) {
            thread.join();
        }
    }

    void submit(Func f) {
        internal_queue.push(f);
    }
};

std::mutex mut;

void task() {
    std::lock_guard guard {mut};
    auto thread_id {std::this_thread::get_id()};
    std::cout << "Thread ID: " << thread_id << " started task" << std::endl;
    std::this_thread::sleep_for(100ms);
    std::cout << "Thread ID: " << thread_id << " finished task" << std::endl;
}

int main() {
    std::cout
        << "Creating a thread pool with "
        << std::thread::hardware_concurrency()
        << " threads"
        << std::endl;
    auto pool {std::make_unique<ThreadPool>()};
    for (auto i {0}; i < 10; i++) {
        pool->submit(task);
    }

    std::this_thread::sleep_for(5s);

    return 0;
}