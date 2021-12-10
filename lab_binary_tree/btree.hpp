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

        explicit Node(const value_type &data) : m_value(data) {};

        const Key &getKey() const {
            return m_value.first;
        }

        std::shared_ptr<Node> getLeft() const {
            return left;
        }

        std::shared_ptr<Node> getRight() const {
            return right;
        }

        std::shared_ptr<Node> getParent() const {
            return m_parent;
        }

        value_type &getValue() {
            return m_value;
        }

        const value_type &getConstValue() const {
            return m_value;
        }

        void setParent(std::shared_ptr<Node> new_parent) {
            if (new_parent) {
                if (comparator(getKey(), new_parent.getKey())) {
                    new_parent->left = this;
                } else {
                    new_parent->right = this;
                }
                m_parent = new_parent;
            }
        }

        void setLeft(std::shared_ptr<Node> new_left) {
            if (new_left) {
                new_left->m_parent = std::shared_ptr<Node>(this);
                left = new_left;
            }
        }

        void setRight(const Node &new_right) {
            if (new_right) {
                new_right->m_parent = this;
                right = new_right;
            }
        }

    private:
        value_type m_value;
        std::shared_ptr<Node> m_parent = nullptr;
        std::shared_ptr<Node> left = nullptr;
        std::shared_ptr<Node> right = nullptr;
    };

    template<bool is_const>
    class TreeIterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::pair<const Key, Value>;
        using data_type = std::conditional_t<is_const, const value_type, value_type>;
        using reference = std::add_lvalue_reference_t<value_type>;
        using pointer = std::add_pointer_t<value_type>;

        TreeIterator() = default;

        explicit TreeIterator(std::shared_ptr<Node> node) : m_node(node) {};

        TreeIterator operator++() {
            if (m_node->getRight()) {
                m_node = m_node->getRight();
                while (m_node->getLeft()) {
                    m_node = m_node->getLeft();
                }
                return *this;
            }
            if (comparator(m_node->getKey(), m_node->getParent()->getKey())) {
                m_node = m_node->getParent();
            } else {
                m_node = m_node->getParent()->getParent();
            }
            return *this;
        }

        TreeIterator operator--() {
            if (m_node->getLeft()) {
                m_node = m_node->getRight();
                while (m_node->getRight()) {
                    m_node = m_node->getRight();
                }
                return *this;
            }
            auto key = m_node->getKey();
            while (m_node->getParent() && comparator(key, m_node->getParent()->getKey())) {
                m_node = m_node->getParent();
            }
            if (m_node->getParent()) {
                m_node = m_node->getParent();
            }
            return *this;
        }

        value_type &operator*() {
            return m_node->getValue();
        }

        bool operator==(TreeIterator const &another) {
            return m_node == another->m_node;
        }

        bool operator!=(TreeIterator const &another) {
            return !(this == another);
        }


    private:
        std::shared_ptr<Node> m_node;
    };

public:
    using btree_type = Value;
    using size_type = size_t;
    using key_compare = Compare;
    using reference = std::add_lvalue_reference<value_type>;
    using const_reference = std::add_const<reference>;
    using iterator = TreeIterator<false>;
    using const_iterator = TreeIterator<true>;

    btree() {
        root = nullptr;
    }

    explicit btree(const Compare &comp) {
        comparator = comp;
        root = nullptr;
    };

    btree(const btree &another) {
        if (another.empty()) {
            root = new Node();
            return;
        }
        root = another.root;
    }

    btree &operator=(const btree &another) {
        if (this != another) {
            this->clear();
            if (another.empty()) {
                root = new Node();
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
        auto[inserted_iter, flag] = insert(std::make_pair(key, btree_type()));
        return (*inserted_iter).second;
    }

    Value &at(const Key &key) {
        auto curIter = findIterToKey(key);
        if ((*curIter).first != key) {
            throw std::out_of_range("btree out of range");
        } else {
            return (*this)[key];
        }
    }

    const Value &at(const Key &key) const {
        auto curIter = findIterToKey(key);
        if ((*curIter).first != key) {
            throw std::out_of_range("btree out of range");
        } else {
            return (*this)[key];
        }
    }

    std::pair<iterator, bool> insert(const value_type &data) {
        auto key = data.first;
        auto cur = findNode(key);
        if (cur->getKey() == key) {
            auto existing = std::make_shared<Node>(cur->getValue());
            return std::make_pair(iterator(existing), false);
        }
        auto insertable = std::make_shared<Node>(data);
        if (comparator(cur->getKey(), key)) {
            cur->setLeft(insertable);
            _size++;
            return std::make_pair(iterator(cur->getLeft()), true);
        } else {
            cur->setLeft(insertable);
            _size++;
            return std::make_pair(iterator(cur->getRight()), true);
        }
    }

    void erase(iterator position) {
        erase(position.m_node.getKey());
    }

    size_type erase(const Key &key) {
        auto delNode = findNode(key);
        if (delNode.getKey() == key) {
            if (delNode.getRight().isEmpty()) {
                auto parent = delNode.getParent();
                parent.setLeft(delNode.getLeft());
            } else if (delNode.getLeft().isEmpty()) {
                auto parent = delNode.getParent();
                parent.setRight(delNode.getRight());
            } else {
                Node &replacement = delNode.getRight();
                while (!replacement.getLeft().isEmpty()) {
                    replacement = replacement.getLeft();
                }
                replacement.setLeft(delNode.getLeft());
                replacement.setRight(delNode.getRight());
                replacement.setParent(delNode.getParent());
            }
            delete (delNode);
            _size--;
            return 1;
        }
        return 0;
    }

    void erase(iterator first, iterator last) {
        if (first == begin() && last == end()) {
            clear();
        }
        for (auto a = first; a != last; a++) {
            erase(a);
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
        auto cur = findIterToKey(key);
        if ((*cur).first == key) {
            return cur;
        } else {
            return end();
        }
    };

    const_iterator find(const Key &key) const {
        if (this->empty()) { return cend(); }
        auto cur = findIterToKey(key);
        if ((*cur).first == key) {
            return const_iterator(*cur);
        } else {
            return cend();
        }
    }

private:
    void _clear_subtree_(Node *node) {
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

    iterator findIterToKey(const Key &key) const {
        return iterator(findNode(key));
    }

    std::shared_ptr<Node> findNode(const Key &key) {
        auto cur = root;
        while (key != cur->getKey()) {
            if (comparator(cur->getKey(), key)) {
                if (cur->getLeft()) {
                    cur = cur->getLeft();
                } else { break; }
            } else {
                if (cur->getRight()) {
                    cur = cur->getRight();
                } else { break; }
            }
        }
        return cur;
    }

    size_type _size = {};
    std::shared_ptr<Node> root;
    inline static key_compare comparator = Compare();
};

template<typename K, typename V, typename C, typename A>
inline bool operator==(const btree<K, V, C> &x, const btree<K, V, C> &y) {
    if (x.size() != y.size()) {
        return false;
    }
    return x.cbegin() == y.cend();
}

template<typename K, typename V, typename C, typename A>
inline bool operator!=(const btree<K, V, C> &x, const btree<K, V, C> &y) {
    return !(x == y);
}
