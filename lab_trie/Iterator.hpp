#pragma once

template<class T>
class TrieIterator : public std::iterator<std::forward_iterator_tag, std::pair<std::string, T &>> {
public:

    TrieIterator(value_type &x);

    TrieIterator(const TrieIterator &mit);

    TrieIterator &operator++();

    TrieIterator operator++(int);

    bool operator==(const TrieIterator &rhs);

    bool operator!=(const TrieIterator &rhs);

    reference operator*();

    reference *operator->();

};

template<class T>
class ConstTrieIterator : public std::iterator<std::forward_iterator_tag, std::pair<std::string, T &>> {
    ConstTrieIterator(value_type &x);

    ConstTrieIterator(const ConstTrieIterator &mit);

    ConstTrieIterator &operator++();

    ConstTrieIterator operator++(int);

    bool operator==(const ConstTrieIterator &rhs);

    bool operator!=(const ConstTrieIterator &rhs);

    const reference operator*();

    const reference *operator->();
};

