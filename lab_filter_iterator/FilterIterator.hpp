#pragma once

namespace FilterIterator {
    template<class Predicate, class Iterator>
    class FilterIterator {
    public:
        typedef typename std::iterator_traits<Iterator>::value_type value_type;
        typedef typename std::iterator_traits<Iterator>::reference reference;
        typedef typename std::iterator_traits<Iterator>::pointer pointer;
        typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
        typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;

        FilterIterator() = delete;

        FilterIterator(Predicate predicate, Iterator begin, Iterator end = Iterator()) : m_predicate(predicate), m_iter(begin), m_end(end) {
            while (!m_predicate(*m_iter) && m_iter != m_end) {
                m_iter++;
            }
            return m_iter;
        }

        explicit FilterIterator(Iterator begin, Iterator end = Iterator()) : m_iter(begin), m_predicate(), m_end(end) {};

        template<class OtherIterator>
        explicit FilterIterator(FilterIterator<Predicate, OtherIterator> const &t,
                                typename std::enable_if<std::is_same_v<OtherIterator, Iterator>>) : m_iter(t.base()), m_predicate(t.predicate()), m_end(t.end()) {}

        Predicate predicate() const {return m_predicate;};

        Iterator end() const {return m_end;};

        Iterator const &base() const {return m_iter;};

        reference operator*() const {return *m_iter;};

        FilterIterator &operator++() {
            m_iter++;
            while(!m_predicate(*m_iter) && m_iter != m_end) {
                m_iter++;
            }
            return *this;
        };

    private:
        Predicate m_predicate;
        Iterator m_iter;
        Iterator m_end;
    };

    template <class Predicate, class Iterator>
    FilterIterator<Predicate,Iterator>
    makeFilterIterator(Predicate predicate, Iterator begin, Iterator end = Iterator()) {
        return FilterIterator<Predicate, Iterator>(predicate, begin, end);
    }

    template <class Predicate, class Iterator, class = std::enable_if<std::is_class_v<Predicate>, Iterator>>
    FilterIterator<Predicate,Iterator>
    makeFilterIterator(Iterator iterator, Iterator end = Iterator()) {
        return FilterIterator<Predicate, Iterator>(iterator, end);
    }
}
