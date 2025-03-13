#include <iostream>
#include <mutex>
#include <thread>

class Test final {
public:
    Test() {
        std::cout << "Test ctor called\n";
    }
    void func() {

    }
};

Test* ptest = nullptr; // variable to be lazily initialized
//std::mutex mut;
std::once_flag ptest_flag;

void process() {
    std::call_once(ptest_flag, []() {
        ptest = new Test();
    });
    /*if (!ptest) {
        ptest = new Test();
    }
    ptest->func();*/
}

int main() {
    std::thread thr1(process);
    std::thread thr2(process);
    thr1.join(); thr2.join();
    return 0;
}