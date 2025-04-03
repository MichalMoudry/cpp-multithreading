#include <future>
#include <iostream>
#include <thread>

using namespace std::literals;

int main() {
    std::packaged_task<int(int, int)> p_task{
        [](int a, int b) {
            std::this_thread::sleep_for(2s);
            return a + b;
        }
    };

    auto future {p_task.get_future()};
    std::thread thr{std::move(p_task), 5, 13};
    //p_task(5, 13);
    std::cout << "Waiting for result\n";

    auto res {future.get()};
    std::cout << "Result is " << res << std::endl;
    thr.join();

    return 0;
}