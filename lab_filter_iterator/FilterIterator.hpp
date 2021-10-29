#include <utility>

#pragma once

namespace filteriterator {

    class FilterIteratorExceptions : std::exception {
    private:
        std::string m_error;
    public:
        explicit FilterIteratorExceptions(std::string error) : m_error(std::move(error)) {}

        const char *what() const noexcept override {
            return m_error.c_str();
        }
    };

    template<class Predicate, class Iterator>
    class FilterIterator final {
    public:
        typedef typename std::iterator_traits<Iterator>::value_type value_type;
        typedef typename std::iterator_traits<Iterator>::reference reference;
        typedef typename std::iterator_traits<Iterator>::pointer pointer;
        typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
        typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;

        FilterIterator() = delete;

        explicit FilterIterator(Predicate predicate, Iterator begin, Iterator end) : m_predicate(predicate),
                                                                                     m_iter(begin), m_end(end) {
            while (m_iter != m_end && !m_predicate(*m_iter)) {
                ++m_iter;
            }
        }

        explicit FilterIterator(Iterator begin, Iterator end) : m_iter(begin), m_predicate(), m_end(end) {
            while (m_iter != m_end && !m_predicate(*m_iter)) {
                ++m_iter;
            }
        };

        Predicate predicate() const { return m_predicate; };

        Iterator end() const { return m_end; };

        Iterator const &base() const { return m_iter; };

        bool operator==(const FilterIterator &that) const {
            return this->m_iter == that.m_iter;
        };

        bool operator!=(const FilterIterator &that) const {
            return this->m_iter != that.m_iter;
        };

        reference operator*() const {
            if (m_iter == m_end) {
                throw FilterIteratorExceptions( "Can't dereference out of range filter iterator");
            }
            return *m_iter;
        };

        FilterIterator &operator++() {
            ++m_iter;
            while (m_iter != m_end && !m_predicate(*m_iter)) {
                ++m_iter;
            }
            return *this;
        };

        FilterIterator operator++(int) {
            auto result = *this;
            ++(*this);
            return result;
        };

    private:
        Predicate m_predicate;
        Iterator m_iter;
        Iterator m_end;
    };

    template<class Predicate, class Iterator, class = std::enable_if<!std::is_default_constructible_v<Predicate>>>
    FilterIterator<Predicate, Iterator>
    makeFilterIterator(Predicate predicate, Iterator begin, Iterator end) {
        return FilterIterator<Predicate, Iterator>(predicate, begin, end);
    }

    template<class Predicate, class Iterator, class = std::enable_if<std::is_class_v<Predicate>>,
            class = std::enable_if<std::is_default_constructible_v<Predicate>>>
    FilterIterator<Predicate, Iterator>
    makeFilterIterator(Iterator iterator, Iterator end) {
        return FilterIterator<Predicate, Iterator>(iterator, end);
    }
}