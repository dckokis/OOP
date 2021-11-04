#pragma once

#include <map>

template<typename Key,
        typename Value,
        typename Compare = std::less<Key>,
        typename Alloc = std::allocator<std::pair<const Key, Value>>>
class btree final {
    template<typename key, typename value>
    class Node final {
    public:
        using key_type = key;
        using value_type = value;

        Node() = default;

        explicit Node(const value_type &data) : m_value(data) {};

        value_type m_value = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
    };

    template<bool is_const>
    class TreeIterator {
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::conditional_t<is_const, const Node<Key, std::pair<const Key, Value>>, Node<Key, std::pair<const Key, Value>>>;
        using reference = value_type &;
        using pointer = value_type *;

        TreeIterator() = default;

        explicit TreeIterator(value_type &node) : m_value(node) {};

        TreeIterator &operator++() {
            
        }

    private:
        value_type m_value;
    };

public:
    using value_type = std::pair<const Key, Value>;
    using key_type = Key;
    using btree_type = Value;
    using key_compare = Compare;
    using reference = value_type &;
    using const_reference = const value_type &;
//    using iterator =  ;
//    using const_iterator =  ...;

    btree() {
        root = nullptr;
    }

    explicit btree(const Compare &comp, const Alloc &a = Alloc()) : comparator(comp), allocator(a) {
        root = nullptr;
    };

    btree(const btree &another);

    btree &operator=(const btree &another);

//    iterator begin();
//
//    const_iterator begin() const;
//
//    iterator end();
//
//    const_iterator end() const;

    bool empty() const;

    size_t size() const;

    Value &operator[](const Key &key);

    Value &at(const Key &key);

    const Value &at(const Key &key) const;

//    std::pair<iterator, bool> insert(const value_type &);
//
//    void erase(iterator position);
//
//    size_type erase(const Key &key);
//
//    void erase(iterator first, iterator last);
//
//    void swap(btree &another);
//
//    void clear();
//
//    iterator find(const Key &key);
//
//    const_iterator find(const Key &key) const;
private:
    Node<key_type, value_type> *root;
    key_compare comparator = Compare();
    Alloc allocator = Alloc();
};

template<typename K, typename V, typename C, typename A>
inline bool operator==(const btree<K, V, C, A> &x, const btree<K, V, C, A> &y) {
    // ....
}

template<typename K, typename V, typename C, typename A>
inline bool operator!=(const btree<K, V, C, A> &x, const btree<K, V, C, A> &y) {
    // ....
}
