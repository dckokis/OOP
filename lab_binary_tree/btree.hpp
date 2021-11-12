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

        bool operator==(Node<key_type, value_type> const &another) {
            return ((m_value == another.m_value) & (right == another.right) & (left == another.left));
        }

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

        explicit TreeIterator(reference node) : m_node(node) {};

        TreeIterator operator++() {
//            m_node = m_node.right;
//            return *this;
        }

        TreeIterator operator--() {
//            m_node = m_node.left;
//            return *this;
        }

        reference operator*() {
            return m_node.m_value;
        }

        bool operator==(TreeIterator const &another) {
            return m_node == another.m_node;
        }

        bool operator!=(TreeIterator const &another) {
            return !(this == another);
        }

    private:
        value_type m_node;
    };

public:
    using value_type = std::pair<const Key, Value>;
    using key_type = Key;
    using node_type = Node<key_type, value_type>;
    using btree_type = Value;
    using size_type = size_t;
    using key_compare = Compare;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = TreeIterator<false>;
    using const_iterator = TreeIterator<true>;

    btree() {
        root = nullptr;
    }

    explicit btree(const Compare &comp, const Alloc &a = Alloc()) : comparator(comp), allocator(a) {
        root = nullptr;
    };

    btree(const btree &another) {
        if (another.empty()) {
            root = new node_type();
            return;
        }
        root = another.root;
    }

    btree &operator=(const btree &another) {
        if (this != another) {
            this->clear();
            if(another.empty()) {
                root = new node_type();
                return *this;
            }
            root = another.root;
        }
        return *this;
    }

    iterator begin() {
        return iterator(root);
    }

    const_iterator cbegin() const {
        return const_iterator(root);
    }

    iterator end() {
        return {};
    }

    const_iterator cend() const {
        return {};
    }

    bool empty() const {
        return root == nullptr;
    }

    size_t size() const {
        size_t size = 0;
        for(auto cur = this->cbegin(); cur != this->cend(); cur++) {
            if(*cur != nullptr) {
                size++;
            }
        }
        return size;
    }

    Value &operator[](const Key &key);

    Value &at(const Key &key);

    const Value &at(const Key &key) const;

    std::pair<iterator, bool> insert(const value_type &);

    void erase(iterator position) {
        for(auto cur = this->cbegin(); cur != this->cend(); cur++) {
            if(cur == position) {
                //delete_node(*cur);
            }
        }
    }

    size_type erase(const Key &key);

    void erase(iterator first, iterator last);

    void swap(btree &another);

    void clear();

    iterator find(const Key &key);

    const_iterator find(const Key &key) const;

private:
    void delete_node(node_type &node) {
        if((node.right == nullptr) & (node.left == nullptr)) {

        }
    }
    node_type *root;
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