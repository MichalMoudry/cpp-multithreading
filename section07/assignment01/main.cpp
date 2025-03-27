#include <vector>
#include <thread>
#include <atomic>

class SomeType final {
public:
	void do_it() {}
};

std::atomic<SomeType*> val {nullptr};
std::mutex process_mutex;

void process() {
    if (!val) {
        std::lock_guard<std::mutex> lk(process_mutex);
        if (!val)
            val = new SomeType();
    }

    SomeType* ptr {val};
    ptr->do_it();
    delete ptr;
}

int main() {
    std::vector<std::thread> tasks;
    for (auto i {0}; i < 15; i++) {
        tasks.push_back(std::thread(process));
    }

    for (auto& thr : tasks) {
        thr.join();
    }
    return 0;
}
