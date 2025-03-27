#include <functional>
#include <future>
#include <iostream>
#include <thread>

void produce(std::promise<int>& px) {
    using namespace std::literals;
    auto x {42};
    std::this_thread::sleep_for(2s);
    std::cout << "Promise sets shared state to " << x << std::endl;
    px.set_value(x);
}

void consume(std::future<int>& fx) {
    std::cout << "Future calling get()...\n";
    auto x {fx.get()};
    std::cout << "Future returns from calling get()\n";
    std::cout << "The answer is " << x << std::endl;
}

int main() {
    std::promise<int> prom;
    std::future<int> future {prom.get_future()};
    std::thread thr_producer(produce, std::ref(prom));
    std::thread thr_consumer(consume, std::ref(future));

    thr_producer.join(); thr_consumer.join();
    return 0;
}