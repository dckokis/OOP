#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <stdexcept>
#include <stack>

template<typename Key,
        typename Value,
        typename Compare = std::less<Key>,
        typename Alloc = std::allocator<std::pair<const Key, Value>>>
class btree {
public:
    using value_type = std::pair<const Key, Value>;
    using size_type = std::size_t;
    using reference = std::add_lvalue_reference_t<value_type>;
    using const_reference = std::add_const_t<reference>;
    using pointer = std::add_pointer_t<value_type>;
    using const_pointer = std::add_const_t<pointer>;

private:
    class TreeNode final {
    private:
        using value_ptr = std::unique_ptr<value_type, std::function<void(value_type *)>>;
        value_ptr data;
        std::shared_ptr<TreeNode> left, right;
        std::weak_ptr<TreeNode> parent;
    public:
        explicit TreeNode(value_ptr &&pair) : data(std::move(pair)) {}

        explicit TreeNode(Key &&key, Value &&value) {
            data = std::make_unique<TreeNode>(value_ptr(key, value));
        }

        std::shared_ptr<TreeNode> getRight() {
            return right;
        }

        std::shared_ptr<TreeNode> getLeft() {
            return left;
        }

        void setLeft(std::shared_ptr<TreeNode> new_left) {
            left = new_left;
        }

        void setRight(std::shared_ptr<TreeNode> new_right) {
            right = new_right;
        }

        std::weak_ptr<TreeNode> getParent() {
            return parent;
        }

        value_ptr getData() {
            return data;
        }
    };

    template<bool IsConst>
    struct TreeIterator {
    protected:
        std::weak_ptr<TreeNode> node_{};
        bool end_flag_{};

        friend class tree;

        void increment() {
            std::shared_ptr<TreeNode> node = node_.lock();
            if (end_flag_) {
                throw std::out_of_range("skip list iterator out of range");
            }
            if (node->getRight()) {
                if (!node->getRight()->getLeft()) {
                    node = node->getRight();
                } else {
                    node = node->getRight();
                    while (node->getLeft()) {
                        node = node->getLeft();
                    }
                }
            } else {
                while (node->getParent().lock() && node == node->getParent().lock()->getRight()) {
                    node = node->getParent().lock();
                }
                if (!node->getParent().lock()) {
                    end_flag_ = true;
                } else {
                    node = node->getParent().lock();
                }
            }
            node_ = node;
        }

        void decrement() {
            std::shared_ptr<TreeNode> node = node_.lock();
            if (end_flag_) {
                while (node->getRight()) {
                    node = node->getRight();
                }
                end_flag_ = false;
            } else if (node->getLeft()) {
                if (!node->getLeft()->getRight()) {
                    node = node->getLeft();
                } else {
                    node = node->getLeft();
                    while (node->getRight()) {
                        node = node->getRight();
                    }
                }
            } else {
                while (node->getParent().lock() && node == node->getParent().lock()->getLeft()) {
                    node = node->getParent().lock();
                }
                if (!node->getParent().lock()) {
                    throw std::out_of_range("skip list iterator out of range");
                }
                node = node->getParent().lock();
            }
            node_ = node;
        }

    public:
        TreeIterator() = delete;

        explicit TreeIterator(const std::shared_ptr<TreeNode> &node, const bool end_flag = false) {
            node_ = node;
            end_flag_ = end_flag;
        }

        using value_type = std::conditional_t<IsConst, const value_type, value_type>;
        using reference = std::conditional_t<IsConst, const_reference, reference>;
        using pointer = std::conditional_t<IsConst, const_pointer, pointer>;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using distance_type = difference_type;

        TreeIterator &operator++() {
            increment();
            return *this;
        }

        TreeIterator operator++(int) {
            auto tmp = *this;
            increment();
            return tmp;
        }

        TreeIterator &operator--() {
            decrement();
            return *this;
        }

        TreeIterator operator--(int) {
            auto tmp = *this;
            decrement();
            return tmp;
        }

        reference operator*() const {
            std::shared_ptr<TreeNode> node = node_.lock();
            if (end_flag_ || !node) {
                throw std::out_of_range("skip list iterator out of range");
            }
            return *(node->getData());
        }

        pointer operator->() const {
            std::shared_ptr<TreeNode> node = node_.lock();
            if (end_flag_ || !node) {
                throw std::out_of_range("skip list iterator out of range");
            }
            return node->getData().get();
        }

        bool operator==(const TreeIterator &another) const {
            return end_flag_ == another.end_flag_ && node_.lock() == another.node_.lock();
        }

        bool operator!=(const TreeIterator &another) const {
            return !(*this == another);
        }
    };

    std::shared_ptr<TreeNode> root{};
    size_type size_{};
    Compare compare = Compare();
public:
    using iterator = TreeIterator<false>;
    using const_iterator = TreeIterator<true>;

    btree() = default;

    explicit btree(const Compare &comp) {
        compare = comp;
    }

    btree(const btree &another) {
        *this = another;
    }

    btree(btree &&another) noexcept {
        *this = another;
        another.clear();
        delete(another);
    }

    btree &operator=(const btree &another) {
        clear();
        compare = another.compare;
        for (auto i = another.begin(); i != another.end(); ++i) {
            (*this)[i->first] = i->second;
        }
        return *this;
    }

    btree &operator=(btree &&another) noexcept {
        root = another.root;
        size_ = another.size_;
        compare = another.compare;
        another.clear();
        delete(another);
        return *this;
    }
    iterator begin() {
        auto current = root;
        if (!current) {
            return end();
        }
        while (current->getLeft()) {
            current = current->getLeft();
        }
        return iterator(current);
    }

    const_iterator begin() const {
        auto current = root;
        if (!current) {
            return end();
        }
        while (current->getLeft()) {
            current = current->getLeft();
        }
        return const_iterator(current);
    }

    iterator end() {
        return iterator(root, true);
    }

    const_iterator end() const {
        return const_iterator(root, true);
    }

    bool empty() const {
        return size_ == 0;
    }

    size_type size() const {
        return size_;
    }

    Value &operator[](const Key &key) {
        auto it = find(key);
        if (it == end()) {
            return insert(std::make_pair(key, Value())).first->second;
        }
        return it->second;
    }

    Value &at(const Key &key) {
        auto it = find(key);
        if (it == end()) {
            throw std::out_of_range("key not found");
        }
        return it->second;
    }

    const Value &at(const Key &key) const {
        auto it = find(key);
        if (it == end()) {
            throw std::out_of_range("key not found");
        }
        return it->second;
    }

    std::pair<iterator, bool> insert(const value_type &val) {
        auto new_node = std::make_shared<TreeNode>(std::move(Key(val.first)), std::move(Value(val.second)));
        if (!root) {
            root = new_node;
            ++size_;
            return std::make_pair(iterator(root), true);
        }
        auto current = root;
        std::shared_ptr<TreeNode> prev;

        while (current) {
            prev = current;
            if (compare(val.first, current->data->first)) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (!prev) {
            prev = new_node;
        } else if (val.first == prev->data->first) {
            return std::make_pair(iterator(prev), false);
        } else if (compare(val.first, prev->data->first)) {
            prev->left = new_node;
        } else {
            prev->right = new_node;
        }
        new_node->parent = prev;
        ++size_;
        return std::make_pair(iterator(new_node), true);
    }


    void erase(iterator position) {
        if (position == end()) {
            return;
        }
        erase(position->first);
    }

    size_type erase(const Key &key) {
        auto it = find(key);
        if (it == end()) {
            return 0;
        }
        auto node = it.node_.lock();
        auto cond = -1;
        if (!node->parent.lock()) {
            cond = 0;
        } else if (node->parent.lock()->right == node) {
            cond = 1;
        }
        if (node->right) {
            auto leftmost_of_right = node->right;
            while (leftmost_of_right->left) {
                leftmost_of_right = leftmost_of_right->left;
            }

            if (node->left) {
                node->left->parent = leftmost_of_right;
            }
            leftmost_of_right->left = node->left;

            if (cond != 0) {
                node->right->parent = node->parent;
                if (cond == -1) {
                    node->parent.lock()->left = node->right;
                } else {
                    node->parent.lock()->right = node->right;
                }
            } else {
                root = node->right;
            }
        } else if (node->left) {
            if (cond != 0) {
                node->left->parent = node->parent;
                if (cond == -1) {
                    node->parent.lock()->left = node->left;
                } else {
                    node->parent.lock()->right = node->left;
                }
            } else {
                root = node->left;
            }
        } else {
            if (cond == -1) {
                node->parent.lock()->left = nullptr;
            } else if (cond == 1) {
                node->parent.lock()->right = nullptr;
            } else {
                root = nullptr;
            }
        }
        --size_;
        return 1;
    }

    void erase(iterator first, iterator last) {
        for (auto i = first; i != last;) {
            auto next = ++i;
            erase(i);
            i = next;
        }
    }

    void swap(btree &another) noexcept {
        auto tmp = std::move(*this);
        *this = std::move(another);
        another = std::move(tmp);
    }

    void clear() {
        size_ = {};
        root = std::make_shared<TreeNode>(Key(), Value());
    }

    iterator find(const Key &key) {
        auto current = root;
        if (!current) {
            return end();
        }
        while (current->data->first != key) {
            if (compare(key, current->data->first)) {
                current = current->left;
            } else if (!compare(key, current->data->first)) {
                current = current->right;
            }
            if (!current) {
                return end();
            }
        }
        return iterator(current);
    }

    const_iterator find(const Key &key) const {
        auto current = root;
        if (!current) {
            return end();
        }
        while (current->data->first != key) {
            if (compare(key, current->data->first)) {
                current = current->left;
            } else if (!compare(key, current->data->first)) {
                current = current->right;
            }
            if (!current) {
                return end();
            }
        }
        return const_iterator(current);
    }
};


template<typename K, typename V, typename C, typename A>
bool operator==(const btree<K, V, C, A> &x, const btree<K, V, C, A> &y) {
    if (x.size() != y.size()) {
        return false;
    }
    for (auto i = x.begin(), j = y.begin(); i != x.end(); ++i, ++j) {
        if (*i != *j) {
            return false;
        }
    }
    return true;
}

template<typename K, typename V, typename C, typename A>
bool operator!=(const btree<K, V, C, A> &x, const btree<K, V, C, A> &y) {
    return !(x == y);
}

