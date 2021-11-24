#pragma once

#include <functional>

template<class T, class Deleter = std::default_delete<T>>
class SharedPTR final {
    using t_SharedPTR = SharedPTR<T, Deleter>;
    using val_type = std::conditional_t<std::is_array_v<T>, typename std::remove_extent_t<T>, T>;
    using dlt_type = Deleter;

    long *m_counter = nullptr;
    val_type *m_ptr = nullptr;
    dlt_type deleter = Deleter();

    void _cleanup_() {
        if (m_counter) {
            if (*m_counter == 1) {
                deleter(m_ptr);
                delete (m_counter);
                m_counter = nullptr;
                m_ptr = nullptr;
                return;
            }
            (*m_counter)--;
        }
    }

public:
    SharedPTR() = default;

    explicit SharedPTR(val_type *pObj) : m_ptr(pObj) {
        if (!m_ptr) {
            return;
        }
        m_counter = new long(0);
        if (m_ptr) {
            (*m_counter)++;
        }
    }

    SharedPTR(t_SharedPTR &&uniquePTR) noexcept: m_ptr(uniquePTR.m_ptr), m_counter(uniquePTR.m_counter),
                                                 deleter(uniquePTR.deleter) {
        uniquePTR.m_ptr = nullptr;
        uniquePTR.m_counter = nullptr;
    };

    SharedPTR(const t_SharedPTR &sharedPtr) : m_ptr(sharedPtr.m_ptr), m_counter(sharedPtr.m_counter) {
        if (m_ptr) {
            (*m_counter)++;
        }
    }

    ~SharedPTR() { _cleanup_(); }

    t_SharedPTR &operator=(t_SharedPTR &&sharedPtr) noexcept {
        if (this != &sharedPtr) {
            _cleanup_();
            m_counter = sharedPtr.m_counter;
            m_ptr = sharedPtr.m_ptr;
            deleter = sharedPtr.deleter;
            sharedPtr.m_ptr = nullptr;
            sharedPtr.m_counter = nullptr;
        }
        return *this;
    }

    t_SharedPTR &operator=(val_type *pObj) {
        if (this->m_ptr != pObj) {
            release();
            m_ptr = pObj;
            if (m_ptr) {
                m_counter = new long(0);
                if (m_ptr) {
                    (*m_counter)++;
                }
            }
        }
        return *this;
    };

    t_SharedPTR &operator=(const t_SharedPTR &sharedPTR) {
        if (this != &sharedPTR) {
            _cleanup_();
            m_counter = sharedPTR.m_counter;
            m_ptr = sharedPTR.m_ptr;
            deleter = sharedPTR.deleter;
            if (m_ptr) {
                (*m_counter)++;
            }
        }
        return *this;
    }

    val_type &operator*() const {
        return *get();
    }

    val_type *operator->() const {
        return get();
    }

    val_type *get() const {
        return m_ptr;
    }

    Deleter &get_deleter() {
        return deleter;
    }

    long use_count() const {
        return m_counter ? *m_counter : 0;
    }

    bool unique() const {
        return use_count() == 1;
    }

    operator bool() const {
        return m_ptr != nullptr;
    }

    void release() { _cleanup_(); }

    void reset(val_type *pObj = nullptr) {
        release();
        m_ptr = pObj;
        if (m_ptr) {
            m_counter = new long(0);
            (*m_counter)++;
        }
    }

    void swap(t_SharedPTR &sharedPTR) {
        std::swap(m_ptr, sharedPTR.m_ptr);
        std::swap(m_counter, sharedPTR.m_counter);
    }
};