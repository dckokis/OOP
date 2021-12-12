#include <iostream>
#include "btree.hpp"

int main() {

    btree<int, int> test;

    auto[a, flag] = test.insert(std::make_pair(1, 1));
    auto[b, flag1] = test.insert(std::make_pair(2, 2));
    if (flag) {
        std::cout << (*a).second << std::endl;
    }
    if (flag1) {
        std::cout << (*b).second << std::endl;
    }
    test.erase(a);
    test.erase(b);
    std::cout << std::boolalpha << test.empty();
    return 0;
}
