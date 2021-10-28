#pragma once

#include <map>
#include <string>
#include <utility>

template <class T>
class SubTrie {
    typedef T value_type;
    typedef std::string key_type;

    template <typename>
    friend class Trie;

    template<typename>
    friend class TrieIterator;

    template <typename>
    friend class TestHelper;

public:
    void clear() {
        if (children.size()) {
            for (auto it : children) {
                internal_clear(it.second);
            }
            children.clear();
        }
    };
    bool if_attended() const { return attended; };
    inline bool is_word_end() const { return is_end_of_word; }
    void set_if_attended(bool arg) { attended = arg; };
private:
    SubTrie() { };
    SubTrie(const bool is_end_of_word_, const value_type& value_, SubTrie<T>* const parent_) :
            parent(parent_),
            is_end_of_word(is_end_of_word_),
            value(value_) {};

    SubTrie(const bool is_end_of_word_, SubTrie<T>* const parent_) :
            parent(parent_),
            is_end_of_word(is_end_of_word_) {};

    SubTrie(SubTrie<T>* parent_, const SubTrie<T> & subtrie):
            parent(parent_),
            value(subtrie.value),
            is_end_of_word(subtrie.is_end_of_word)
    {
        init(subtrie);
    };

    SubTrie(const SubTrie<T> & subtrie)  :
            parent(nullptr),
            value(subtrie.value),
            is_end_of_word(subtrie.is_end_of_word)
    {
        init(subtrie);
    };

    SubTrie<T> & operator = (const SubTrie<T> & trie) {
        if (this != &trie) {
            if (trie.parent != nullptr) {
                parent = new SubTrie<T>(*trie.parent);
            }
            else {
                parent = nullptr;
            }

            value = trie.value;
            is_end_of_word = trie.is_end_of_word;
            init(trie);
        }
        return *this;
    };

private:
    void init(const SubTrie<T>& subtrie);
    void internal_clear(SubTrie<T>* ptr);
    std::map<char, SubTrie<T>*> children;
    SubTrie<T>* parent = nullptr;
    bool is_end_of_word = false;
    value_type value{};
    bool attended = false;

};

template<typename T>
void SubTrie<T>::internal_clear(SubTrie<T>* ptr) {
    if ((ptr->children).size()) {
        for (auto it : ptr->children) {
            internal_clear(it.second);
        }
        (ptr->children).clear();
        delete ptr;
    }
    else {
        delete ptr;
    }
}

template<class T>
inline void SubTrie<T>::init(const SubTrie<T>& subtrie) {
    if (subtrie.children.size()) {
        for (auto it : subtrie.children) {
            char ch_val = it.first;
            SubTrie<T>* new_child = new SubTrie<T>(this, SubTrie<T>(*it.second));
            std::pair<char, SubTrie<T>*> p{ ch_val, new_child };
            this->children.insert(p);
        }
    }
}

