#include <iostream>
#include "btree.hpp"
int main() {

    btree<int, int> test;

    auto [a, flag] = test.insert(std::make_pair(1, 1));
    if(flag) {
        std::cout << (*a).second << std::endl;
    }
    return 0;
}
