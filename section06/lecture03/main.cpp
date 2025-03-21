#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <string>

using namespace std::literals;

std::string s_data;

std::mutex mut;
std::condition_variable cond_var;

void reader() {
    std::cout << "Reader thread locking the mutex\n";
    std::unique_lock unique_lck(mut);
    std::cout << "Reader thread has locked the mutex\n";

    std::cout << "Reader thread is sleeping...\n";
    cond_var.wait(unique_lck);
    std::cout << "Data is: " << s_data << std::endl;
}

void writer() {
    {
        std::cout << "Writer thread locking the mutex\n";
        std::lock_guard guard_lck(mut);
        std::cout << "Writer thread has locked the mutex\n";
        std::this_thread::sleep_for(2s);

        s_data = "Test data";
    }

    std::cout << "Writer sends notification\n";
    cond_var.notify_one();
}

int main() {
    s_data = "Empty";
    std::thread reader_thr(reader);
    std::thread writer_thr(writer);

    writer_thr.join();
    reader_thr.join();
    return 0;
}