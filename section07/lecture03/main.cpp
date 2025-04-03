#include <atomic>
#include <functional>
#include <iostream>
#include <list>
#include <thread>
#include <vector>

template<typename T>
class LockFreeQueue final {
private:
    std::list<T> list;
    typename std::list<T>::iterator i_head, i_tail;
public:
    LockFreeQueue() {
        list.push_back(T());
        i_head = list.begin();
        i_tail = list.end();
    }

    bool consume(T& t_ref) {
        auto i_first {i_head};
        i_first += 1;

        if (i_first != i_tail) {
            i_head = i_first;
            t_ref = *i_head;
            return true;
        }

        return false;
    }

    void produce(const T& t_ref) {
        list.push_back(t_ref);
        i_tail = list.end();
        list.erase(list.begin(), i_head);
    }

    void print() {
        auto head {i_head};
        head += 1;
        for (auto i {head}; i != i_tail; i++) {
            std::cout << *i << ", ";
        }
        std::cout << std::endl;
    }
};

int main() {
    LockFreeQueue<int> lfq;
    std::vector<std::thread> threads;
    auto j {1};

    for (auto i {0}; i < 10; i++) {
        std::thread producer(&LockFreeQueue<int>::produce, &lfq, std::ref(i));
        threads.push_back(std::move(producer));

        std::thread consumer(&LockFreeQueue<int>::consume, &lfq, std::ref(j));
    }
    //std::thread producer_thread{};
    //std::thread consumer_thread{};

    return 0;
}