#pragma once

#include <map>

template<typename Key,
        typename Value,
        typename Compare = std::less<Key>>
class btree final {
public:
    using value_type = std::pair<const Key, Value>;
    using key_type = Key;
private:
    class Node final {
    public:
        Node() = default;

        explicit Node(const Value &data, const Node &parent) : m_value(data), m_parent(parent) {};

        bool operator==(Node const &another) const {
            if (this != nullptr && another != nullptr) {
                return ((m_value == another.m_value) && (right == another.right) && (left == another.left) &&
                        (m_parent == another.m_parent));
            }
            return false;
        }

        const Key &getKey() const {
            return m_value.first;
        }

        const Node &getLeft() const {
            return left;
        }

        const Node &gerRight() const {
            return right;
        }

        const Node &getParent() const {
            return m_parent;
        }

        value_type &getValue() {
            return m_value;
        }

        const value_type &getConstValue() const {
            return m_value;
        }

        void setParent(const Node &new_parent) {
            if (new_parent != nullptr) {
                if (comparator(getKey(), new_parent.getKey())) {
                    new_parent.left = this;
                } else {
                    new_parent.right = this;
                }
            }
            m_parent = new_parent;
        }

        void setLeft(const Node &new_left) {
            if (new_left != nullptr) {
                new_left.m_parent = this;
            }
            left = new_left;
        }

        void setRight(const Node &new_right) {
            if (new_right != nullptr) {
                new_right.m_parent = this;
            }
            right = new_right;
        }

    private:
        value_type m_value = nullptr;
        Node &m_parent = nullptr;
        Node &left = nullptr;
        Node &right = nullptr;
    };

    template<bool is_const>
    class TreeIterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using data_type = std::conditional_t<is_const, const Node, Node>;
        using reference = data_type &;
        using pointer = data_type *;

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
            if (comparator(m_node.getKey(), m_node.m_parent->getKey())) {
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
            while (m_node.m_parent && comparator(key, m_node.m_parent->getKey())) {
                m_node = m_node.m_parent;
            }
            if (m_node.m_parent) {
                m_node = m_node.m_parent;
            }
            return *this;
        }

        ///////////////при возврате m_node.getValue() все равно *iter имеет тип Node
        data_type &operator*() {
            return m_node;
        }

        bool operator==(TreeIterator const &another) {
            return m_node == another.m_node;
        }

        bool operator!=(TreeIterator const &another) {
            return !(this == another);
        }

    private:
        data_type &m_node;
    };

public:
    using node_type = Node;
    using btree_type = Value;
    using size_type = size_t;
    using key_compare = Compare;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = TreeIterator<false>;
    using const_iterator = TreeIterator<true>;

    btree() {
        root = nullptr;
        _size = {};
    }

    explicit btree(const Compare &comp) {
        comparator = comp;
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
        return _size == 0;
    }

    size_t size() const {
        return _size;
    }

    Value &operator[](const Key &key) {
        auto inserted_iter = insert(std::make_pair(key, btree_type()));
        return (*inserted_iter).getValue();
    }

    Value &at(const Key &key) {
        auto curIter = findKey(key);
        if ((*curIter).getKey() != key) {
            throw std::out_of_range("btree out of range");
        } else {
            return (*this)[key];
        }
    }

    const Value &at(const Key &key) const {
        auto curIter = findKey(key);
        if ((*curIter).getKey() != key) {
            throw std::out_of_range("btree out of range");
        } else {
            return (*this)[key];
        }
    }

    std::pair<iterator, bool> insert(const value_type &data) {
        auto key = data.first;
        auto cur = findKey(key);
        if ((*cur).getKey() == key) {
            return std::make_pair(iterator(cur), false);
        }
        if (comparator((*cur).getKey(), key)) {
            (*cur).setLeft(new Node(data));
            _size++;
            return std::make_pair(iterator((*cur).getLeft(), true));
        } else {
            (*cur).setRight(new Node(data));
            _size++;
            return std::make_pair(iterator((*cur).gerRight(), true));
        }
    }

    void erase(iterator position) {
        erase(position.m_node.getKey());
    }

    size_type erase(const Key &key) {
        auto delIter = findKey(key);
        if (*delIter.getKey() == key) {
            auto delNode = *delIter;
            if (delNode.gerRight() == nullptr) {
                auto parent = delNode.getParent();
                parent.setLeft(delNode.getLeft());
            } else if (delNode.getLeft() == nullptr) {
                auto parent = delNode.getParent();
                parent.setRight(delNode.getRight());
            } else {
                delIter++;
                auto newNode = *delIter;
                auto oldParent = newNode.getParent();
                oldParent.setLeft(nullptr);
                newNode.setRight(delNode.getRight());
                newNode.setLeft(delNode.getLeft());
                newNode.setParent(delNode.getParent());
            }
            delete (delNode);
            _size--;
            return 1;
        }
        return 0;
    }

    void erase(iterator first, iterator last) {////?????
        if (first == begin() && last == end()) {
            clear();
        }
    }

    void swap(btree &another) {
        std::swap(root, another.root);
    }

    void clear() {
        _clear_subtree_(root->left);
        _clear_subtree_(root->right);
        _size = 0;
    }

    iterator find(const Key &key) {
        if (this->empty()) { return end(); }
        auto cur = findKey(key);
        if ((*cur).getKey() == key) {
            return cur;
        } else {
            return end();
        }
    };

    const_iterator find(const Key &key) const {
        if (this->empty()) { return cend(); }
        auto cur = findKey(key);
        if ((*cur).getKey() == key) {
            return const_iterator(*cur);
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

    iterator findKey(const Key &key) const {
        auto cur = root;
        while (key != (*cur).getKey()) {
            if (comparator((*cur).getKey(), key)) {
                if (cur->left) {
                    cur = cur->left;
                } else { break; }
            } else {
                if (cur->right) {
                    cur = cur->right;
                } else { break; }
            }
        }
        return iterator(cur);
    }

    size_type _size;
    node_type *root;
    inline static key_compare comparator = Compare();
};

template<typename K, typename V, typename C, typename A>
inline bool operator==(const btree<K, V, C> &x, const btree<K, V, C> &y) {
    if (x.size() != y.size()) {
        return false;
    }
    auto curX = *(x.cbegin());
    auto curY = *(y.cbegin());
    return curX == curY;
//    auto xIter = x.cbegin();
//    auto yIter = y.cbegin();
//    xIter--, yIter--;
//    for (xIter, yIter; xIter != x.cend(), yIter != y.cend(); xIter++, yIter++) {
//        if (*xIter != *yIter) {
//            return false;
//        }
//    }
}

template<typename K, typename V, typename C, typename A>
inline bool operator!=(const btree<K, V, C> &x, const btree<K, V, C> &y) {
    return !(x == y);
}
