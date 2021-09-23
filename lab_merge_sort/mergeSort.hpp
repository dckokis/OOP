#pragma once

#include <algorithm>

template<class RandomAccessIterator, class Compare>
typename std::enable_if<std::is_same<typename std::iterator_traits<RandomAccessIterator>::iterator_category, std::random_access_iterator_tag>::value>::type
merge_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    auto size = std::distance(first, last);
    if (size <= 1)
        return;
    auto sizeOfLeftPart = size / 2;
    auto middle = first;
    std::advance(middle, sizeOfLeftPart);

    merge_sort(first, middle, comp);
    merge_sort(middle, last, comp);

    std::inplace_merge(first, middle, last, comp);
}

template<class RandomAccessIterator>
        typename std::enable_if<std::is_same<typename std::iterator_traits<RandomAccessIterator>::iterator_category, std::random_access_iterator_tag>::value>::type
        merge_sort(RandomAccessIterator first, RandomAccessIterator last) {
    merge_sort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}