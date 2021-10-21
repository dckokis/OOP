#ifndef LAB_SHARED_PTR_SHAREDPTR_HPP
#define LAB_SHARED_PTR_SHAREDPTR_HPP

#include <utility>

namespace sharedptr {
    class RefCount {
    private:
        unsigned int m_counter = {};
    public:
        RefCount() = default;

        RefCount(const RefCount &) = delete;

        RefCount &operator=(const RefCount &) = delete;

        void reset() {
            m_counter = 0;
        }

        unsigned int get() const {
            return m_counter;
        }

        void operator++() {
            m_counter++;
        }

        void operator++(int) {
            m_counter++;
        }

        void operator--() {
            m_counter--;
        }

        void operator--(int) {
            m_counter--;
        }
    };

///////////////////////////////////////////////////////////////////////////////////////
    template<class T, class Deleter>
    class SharedPtr {
        typedef SharedPtr<T, Deleter> t_SharedPTR;
    private:
        RefCount *m_counter{};
        T *m_ptr;
        Deleter deleter;

        void _cleanup_() {
            (*m_counter)--;
            if (!m_counter->get()) {
                delete m_ptr;
                delete m_counter;
                delete deleter;
            }
        }

    public:
        SharedPtr() = default;

        explicit SharedPtr(T *pObj) : m_ptr(pObj), m_counter(new RefCount), deleter(new Deleter) {
            (*m_counter)++;
        }

        SharedPtr(t_SharedPTR &&uniquePTR) noexcept {
            m_ptr = uniquePTR.m_ptr;
            m_counter = uniquePTR.m_counter;
            deleter = uniquePTR.deleter;
            uniquePTR.m_ptr = nullptr;
            uniquePTR.m_counter = nullptr;
            uniquePTR.deleter = deleter;
        };

        SharedPtr(const t_SharedPTR &sharedPtr) {
            if (sharedPtr.m_ptr) {
                ++sharedPtr.m_counter;
            }
            m_counter = sharedPtr.m_counter;
            m_ptr = sharedPtr.m_ptr;
        }

        ~SharedPtr() { _cleanup_(); }

    public:
        t_SharedPTR &operator=(t_SharedPTR &&sharedPtr) noexcept {
            if (m_ptr != sharedPtr.m_ptr && m_counter->get() != sharedPtr.m_counter->get()) {
                _cleanup_();
                m_counter = sharedPtr.m_counter;
                m_ptr = sharedPtr.m_ptr;
                sharedPtr.m_ptr = nullptr;
                sharedPtr.m_counter = nullptr;
            }
        }

        t_SharedPTR &operator=(T *pObj) {
            if (m_ptr != pObj) {
                _cleanup_();
                if (pObj) {
                    m_counter = new RefCount;
                    (*m_counter)++;
                    m_ptr = pObj;
                }
            }
        }

        t_SharedPTR &operator=(const t_SharedPTR &sharedPtr) {
            if (m_ptr != sharedPtr.m_ptr && m_counter->get() != sharedPtr.m_counter->get()) {
                _cleanup_();
                if (sharedPtr.m_ptr) {
                    ++(*sharedPtr.m_counter);
                }
                m_counter = sharedPtr.m_counter;
                m_ptr = sharedPtr.m_ptr;
            }
        }

    public: // Observers.
        T &operator*() const {
            return this->m_ptr;
        }

        T *operator->() const {
            return this->m_ptr;
        }

        T *get() const {
            return this->m_ptr;
        }

        Deleter &get_deleter() {
            return this->deleter;
        }

        operator bool() const {
            if (m_ptr) return true;
            else return false;
        }

    public: // Modifiers.
        void release() {
            --(*m_counter);
            if (!m_counter->get()) {
                delete m_ptr;
                delete deleter;
                delete m_counter;
            }
            m_ptr = nullptr;
            m_counter = nullptr;
        }

        void reset(T *pObject = nullptr) {
            --(*m_counter);
            if (!m_counter->get()) {
                delete m_ptr;
            }
            m_counter = {};
            if (!pObject) {
                m_ptr = nullptr;
                return;
            }
            m_ptr = pObject;
            (*m_counter)++;
        }

        void swap(t_SharedPTR &sharedPTR) {
            t_SharedPTR tmp{std::move(sharedPTR)};
            sharedPTR.m_ptr = std::move(m_ptr);
            m_ptr = std::move(tmp);
        }
    };
}
#endif //LAB_SHARED_PTR_SHAREDPTR_HPP
