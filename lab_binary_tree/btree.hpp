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

        explicit Node(const value_type &data, const Node &parent = nullptr) : m_value(data), m_parent(parent) {};

        bool operator==(Node<key_type, value_type> const &another) {
            return ((m_value == another.m_value) & (right == another.right) & (left == another.left) &
                    (m_parent == another.m_parent));
        }

        const key_type &getKey() const {
            return m_value.first;
        }

        value_type m_value = nullptr;
        Node *m_parent = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
    };

    template<bool is_const, typename compare = std::less<Key>>
    class TreeIterator {
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::conditional_t<is_const, const Node<Key, std::pair<const Key, Value>>, Node<Key, std::pair<const Key, Value>>>;
        using reference = value_type &;
        using pointer = value_type *;
        compare cmp = compare();

        TreeIterator() = default;

        explicit TreeIterator(reference node) : m_node(node) {};

        TreeIterator operator++() {
            if (m_node.right) {
                m_node = m_node.right;
                while (m_node.left) {
                    m_node = m_node.left;
                }
                return *this;
            }
            if (cmp(m_node.getKey(), m_node.m_parent->getKey())) {
                m_node = m_node.m_parent;
            } else {
                m_node = m_node.m_parent->m_parent;
            }
            return *this;
        }

        TreeIterator operator--() {
            if (m_node.left) {
                m_node = m_node.right;
                while (m_node.right) {
                    m_node = m_node.right;
                }
                return *this;
            }
            auto key = m_node.getKey();
            while (m_node.m_parent && cmp(key, m_node.m_parent->getKey())) {
                m_node = m_node.m_parent;
            }
            if (m_node.m_parent) {
                m_node = m_node.m_parent;
            }
            return *this;
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
            if (another.empty()) {
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
        return root->m_value == nullptr;
    }

    size_t size() const {
        size_t size = 0;
        for (auto cur = this->cbegin(); cur != this->cend(); cur++) {
            if (*cur != nullptr) {
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

    }

    size_type erase(const Key &key);

    void erase(iterator first, iterator last);

    void swap(btree &another);

    void clear() {
        _clear_subtree_(root->left);
        _clear_subtree_(root->right);
    }

    iterator find(const Key &key) {
        if (this->empty()) { return end(); }
        auto cur = findKey(key);
        if (cur) {
            return iterator(cur);
        } else {
            return end();
        }
    };

    const_iterator find(const Key &key) const {
        if (this->empty()) { return cend(); }
        auto cur = findKey(key);
        if (cur) {
            return const_iterator(cur);
        } else {
            return cend();
        }
    }

private:
    void _clear_subtree_(node_type *node) {
        if (node) {
            if (node->left) {
                _clear_subtree_(node->left);
            }
            if (node->right) {
                _clear_subtree_(node->right);
            }
            if (!node->left and !node->right) {
                delete (node);
            }
        }
    }

    node_type *findKey(const Key &key) {
        auto cur = root;
        while (key != cur->getKey()) {
            if (comparator(cur->getKey(), key)) {
                if (cur->left) {
                    cur = cur->left;
                } else { return nullptr; }
            } else {
                if (cur->right) {
                    cur = cur->right;
                } else { return nullptr; }
            }
        }
    }

    template<typename>
    friend
    class TreeIterator;

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
    return !(x == y);
}
