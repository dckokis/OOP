#pragma once

#include <iostream>
#include <algorithm>

class Sort final {
private:
    template<class T>
    static constexpr bool IsRandomAccessIter = std::is_same_v<typename std::iterator_traits<T>::iterator_category, std::random_access_iterator_tag>;
public:
    template<class RandomAccessIterator, class Compare, class = std::enable_if<IsRandomAccessIter<RandomAccessIterator>>>
    static void merge_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
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
    static typename std::enable_if_t<IsRandomAccessIter<RandomAccessIterator>>
    merge_sort(RandomAccessIterator first, RandomAccessIterator last) {
        merge_sort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
    }

    template<class Iterator>
    static typename std::enable_if_t<!IsRandomAccessIter<Iterator>> merge_sort(Iterator first, Iterator last) {
        std::cout << "OK" << std::endl;
    }
};