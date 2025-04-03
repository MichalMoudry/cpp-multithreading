#include <future>
#include <iostream>
#include <thread>
#include <string>

using namespace std::literals;

int task() {
    std::cout << "Executing task() in thread with ID: ";
    std::cout << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(5s);
    std::cout << "Returning from task()\n";
    return 42;
}

void func(const std::string& option = "default"s) {
    std::future<int> res;
    if (option == "async"s) {
        res = std::async(std::launch::async, task);
    }
    else if (option == "deferred"s) {
        res = std::async(std::launch::deferred, task);
    }
    else {
        res = std::async(task);
    }

    std::cout << "Calling async with option \"" << option << "\"" << std::endl;
    std::this_thread::sleep_for(2s);
    std::cout << "Calling get()\n";
    std::cout << "Task result: " << res.get() << std::endl;
}

int main() {
    std::cout << "In main thread with ID: " << std::this_thread::get_id() << std::endl;

    func("async");
    func("deferred");
    func();
    return 0;
}