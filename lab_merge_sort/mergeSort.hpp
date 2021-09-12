#pragma once
#include <algorithm>

template<class RandomAccessIterator, class Compare>
inline void merge_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    auto size = std::distance(first, last);
    if (size == 1)
        return;
    auto sizeOfLeftPart = size / 2;
    auto middle = first;
    std::advance(middle, sizeOfLeftPart);

    merge_sort(first, middle, comp);
    merge_sort(middle, last, comp);

    std::inplace_merge(first, middle, last, comp);
}


