#include <iostream>
#include <vector>
#include <assert.h>
#include "FilterIterator.hpp"

using namespace std;
using namespace FilterIterator;

struct is_even {
    bool operator()(int x) { return x % 2 == 0; }
};

int main() {
    //try{
        auto v = std::vector{1, 2, 3, 4};
        auto i = v.begin();
        is_even pred;
        auto f = makeFilterIterator<is_even, vector<int>::iterator>(pred, i, v.end());

        assert(*f == 2);
        ++f;
        assert(*f == 4);
   // } catch (FilterIteratorException &exception) {
   //     exception.Message();
   // }
}
