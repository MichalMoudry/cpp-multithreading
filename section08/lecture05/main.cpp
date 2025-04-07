#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

template<typename T>
void print_vector(const std::string&& vec_name, const std::vector<T>& vec) {
    std::cout << vec_name << " vector: ";
    for (auto& v : vec) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec {1, 2, 3, 4};
    std::vector<int> vec2;

    std::transform(
        vec.begin(),
        vec.end(),
        std::back_inserter(vec2),
        [](int n) {
            return n*2;
        }
    );

    print_vector("Input", vec);
    print_vector("Output", vec2);

    // -- inner product
    std::vector<int> x {1, 2, 3, 4, 5};
    std::vector<int> y {5, 4, 3, 2, 1};
    auto res {std::inner_product(x.begin(), x.end(), y.begin(), 0)};

    print_vector("(X)", x);
    print_vector("(Y)", y);
    std::cout << "Inner product of (X) and (Y): " << res << std::endl;

    return 0;
}