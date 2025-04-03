#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <future>
#include <thread>
#include <utility>
#include <vector>

static std::mt19937 mt;
std::uniform_real_distribution<double> dist(0, 100);

double accum(double* beg, double* end) {
    return std::accumulate(beg, end, 0.0);
}

double add_parallel(std::vector<double>& vec) {
    auto vec0 {&vec[0]};
    auto v_size {vec.size()};

    auto partition1 {vec0 + v_size/4};
    auto future_1 {std::async(std::launch::async, accum, vec0, partition1)};

    auto partition_2 {vec0 + 2 * v_size/4};
    auto future_2 {std::async(std::launch::async, accum, partition1, partition_2)};

    auto partition_3 {vec0 + 3 * v_size/4};
    auto future_3 {std::async(std::launch::async, accum, partition_2, partition_3)};

    auto future_4 {std::async(std::launch::async, accum, partition_3, vec0 + v_size)};

    return future_1.get() + future_2.get() + future_3.get() + future_4.get();
}

double packaged_add(std::vector<double>& vec) {
    using task_type = double(double*, double*);
    std::packaged_task<task_type>
        p_task1(accum),
        p_task2(accum),
        p_task3(accum),
        p_task4(accum);
    auto future_1 {p_task1.get_future()};
    auto future_2 {p_task2.get_future()};
    auto future_3 {p_task3.get_future()};
    auto future_4 {p_task4.get_future()};

    auto vec_0 {&vec[0]};
    auto v_size {vec.size()};

    auto partition_1 {vec_0 + v_size/4};
    std::thread thr1 {std::move(p_task1), vec_0, partition_1};

    auto partition_2 {vec_0 + 2 * v_size/4};
    std::thread thr2 {std::move(p_task2), partition_1, partition_2};

    auto partition_3 {vec_0 + 3 * v_size/4};
    std::thread thr3 {std::move(p_task3), partition_2, partition_3};

    std::thread thr4 {std::move(p_task4), partition_3, vec_0 + v_size};
    thr1.join(); thr2.join(); thr3.join(); thr4.join();
    return future_1.get() + future_2.get() + future_3.get() + future_4.get();
}

int main() {
    std::vector<double> vec(16);
    std::iota(vec.begin(), vec.end(), 1.0);

    std::vector<double> v_rand(10'000);
    std::generate(v_rand.begin(), v_rand.end(), [&v_rand]() {
        return dist(mt);
    });

    std::cout << "Sum of first 16 ints: " << add_parallel(vec) << std::endl;
    std::cout << "Sum of 10,000 random numbers: " << add_parallel(v_rand) << std::endl;

    std::cout << "Sum of first 16 ints: " << packaged_add(vec) << std::endl;
    std::cout << "Sum of 10,000 random numbers: " << packaged_add(v_rand) << std::endl;
    return 0;
}