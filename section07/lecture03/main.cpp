#include <atomic>
#include <list>
#include <thread>

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
};

int main() {
    //std::thread producer_thread{};
    //std::thread consumer_thread{};

    return 0;
}