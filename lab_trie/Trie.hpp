#pragma once
#include <string>
#include "SubTrie.hpp"
#include "Iterator.hpp"

class BadSearchException : std::exception {
private:
    std::string m_error;
public:
    explicit BadSearchException(std::string error) : m_error(error) {}

    const char *what() const noexcept override {
        return m_error.c_str();
    }
};

template<class T>
class Trie {
private:
    SubTrie<T> *root = new SubTrie<T>;
    size_t m_size = 0;
public:

    using iterator = TrieIterator<T>;
    using const_iterator = ConstTrieIterator<T>;

    using value_type = T;
    using key_type = std::string;

    Trie() = default;

    template<class InputIterator>
    Trie(InputIterator first, InputIterator last) {
        root = new SubTrie<T>;
        for (auto it = first; it != last; ++it) {
            std::pair<key_type, value_type> p{*it};
            this->insert(p.first, p.second);
        }
    }

    Trie(const Trie<T> &trie) {
        m_size = trie.m_size;
        root = new SubTrie<T>(*trie.root);
    }

    ~Trie() {
        if (this->root) {
            this->root->clear();
            delete root;
        }
    }

    Trie<T> &operator=(const Trie &trie) {
        if (this != &trie) {
            this->clear(); /*deep deleting each node, root remains!*/
            this->root->init(*(trie.root));
            m_size = trie.m_size;
        }
        return *this;
    }

    iterator begin();

    const_iterator cbegin() const;

    iterator end();

    const_iterator cend() const;

    bool empty() const {
        return (!(root->children).size());
    }

    size_t size() const {
        return m_size;
    }

    value_type &operator[](const key_type &k);

    std::pair<iterator, bool> insert(const key_type &k, const value_type &val);

    template<class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for (auto it = first; it != last; ++it) {
            std::pair<key_type, value_type> p{*it};
            this->insert(p.first, p.second);
        }
    }

    //удаление
    void erase(iterator position) {
        SubTrie<T> *temp = position.data;
        internal_erase(temp, position.search_str);
    }

    size_t erase(const key_type &k) {
        SubTrie<T> *temp = root;
        for (auto letter: k) {
            auto it = temp->children.find(letter);
            if (it != temp->children.end()) {
                temp = it->second;
            } else {
                return 0;
            }
        }
        internal_erase(temp, k);
        return size;
    }

    void erase(iterator first, iterator last) {
        for (iterator it = first; it != last;) {
            erase(it++);
        }
    }

    void swap(Trie &trie) {
        Trie<T> *tmp = std::move(trie);
        trie = std::move(this);
        this = std::move(tmp);
    }

    void clear() {
        root->clear();
        m_size = 0;
    }

    iterator find(const key_type &k) {
        SubTrie<T>* temp = root;
        for (auto letter : k) {
            auto it_ = (temp->children).find(letter);
            if (it_ == temp->children.end()) {
                return end();
            }
            else {
                temp = it_->second;
            }
        }
        if (temp->is_end_of_word) {
            return iterator(k, temp);
        }
        else {
            return end();
        }
    }

    const_iterator find(const key_type &k) const;

    SubTrie<T> GetSubTrie(const key_type &subKey) {
        SubTrie<T>* temp = root;
        for (auto letter : subKey) {
            auto it_ = temp->children.find(letter);
            if (it_ == temp->children.end()) {
                throw BadSearchException(subKey);
            }
            else {
                temp = it_->second;
            }
        }
        return *temp;
    }
};
