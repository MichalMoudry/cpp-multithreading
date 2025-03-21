#include <iostream>
#include <mutex>
#include <ostream>
#include <thread>
#include <string>

using namespace std::literals;

std::string s_data;
auto update_progress {false};
auto is_completed {false};

std::mutex data_mutex;
std::mutex is_completed_mutex;

void fetch_data() {
    for (auto i {0}; i < 5; i++) {
        std::cout << "Fetcher thread waiting for data..." << std::endl;
        std::this_thread::sleep_for(2s);

        std::lock_guard data_lck(data_mutex);
        s_data += "Block" + std::to_string(i+1);
        std::cout << "s_data: " << s_data << std::endl;
        update_progress = true;
    }

    std::cout << "Fetch data has ended\n";
    std::lock_guard completed_lock(is_completed_mutex);
    is_completed = true;
}

void progress_bar() {
    size_t len {0};
    while (true) {
        std::cout << "Progress bar thread waiting for data..." << std::endl;

        std::unique_lock data_lck(data_mutex);
        while (!update_progress) {
            data_lck.unlock();
            std::this_thread::sleep_for(10ms);
            data_lck.lock();
        }

        len = s_data.size();
        update_progress = false;
        data_lck.unlock();

        std::cout << "Received " << len << " bytes so far" << std::endl;
        std::lock_guard is_completed_lock(is_completed_mutex);
        if (is_completed) {
            std::cout << "Progress bar thread has ended" << std::endl;
            break;
        }
    }
}

void process_data() {
    std::cout << "Processing thread waiting for data..." << std::endl;
    std::unique_lock is_completed_lock(is_completed_mutex);
    while (!is_completed) {
        is_completed_lock.unlock();
        std::this_thread::sleep_for(10ms);
        is_completed_lock.lock();
    }

    is_completed_lock.unlock();

    std::lock_guard data_lock(data_mutex);
    std::cout << "Processing s_data: " << s_data << std::endl;
}

int main() {
    std::thread fetcher(fetch_data);
    std::thread prog(progress_bar);
    std::thread processor(process_data);

    fetcher.join(); prog.join(); processor.join();
    return 0;
}