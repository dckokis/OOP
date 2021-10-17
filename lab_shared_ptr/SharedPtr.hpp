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
            if (m_counter->get() == 0) {
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
        t_SharedPTR &operator=(t_SharedPTR &&sharedPtr)  noexcept {
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
        T &operator*() const; // Dereference the stored pointer.
        T *operator->() const; // Return the stored pointer.
        T *get() const; // Return the stored pointer.
        Deleter &get_deleter(); // Return a reference to the stored deleter.
        operator bool() const; // Return false if the stored pointer is null.
    public: // Modifiers.
        void release(); // Release ownership of any stored pointer.
        void reset(T *pObject = nullptr); // Replace the stored pointer.
        void swap(t_SharedPTR &sharedPTR); // Exchange the pointer with another object.
    };
}
#endif //LAB_SHARED_PTR_SHAREDPTR_HPP
