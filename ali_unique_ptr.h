//
// Created by Ali Moammeri on 3/28/22.
//

#ifndef ALI_UNIQUE_PTR_H
#define ALI_UNIQUE_PTR_H

#include <iostream>
#include <cctype>

namespace ali {
    template<class T> class unique_ptr {
        friend std::ostream& operator<<(std::ostream&, const unique_ptr<T>&);
    public:
        unique_ptr() noexcept= default;
        explicit unique_ptr(std::nullptr_t nptr) noexcept: _pointer{nptr} {}
        explicit unique_ptr(T* pointer) noexcept : _pointer{pointer} {}
        unique_ptr(const unique_ptr<T>&) noexcept= delete;
        unique_ptr(unique_ptr<T>&& other) noexcept : _pointer {other.release()}{};
        ~unique_ptr() { delete _pointer; }

        T* get() const noexcept { return _pointer; }
        T* release() noexcept {
            T* temp_ptr {get()};
            _pointer = nullptr;
            return temp_ptr;
        }
        void reset(T* pointer = T()) noexcept {
            delete _pointer;
            _pointer = pointer;
        }
        void reset(std::nullptr_t nptr) noexcept {
            delete _pointer;
            _pointer = nptr;
        }
        void swap(unique_ptr<T>& other) { std::swap(_pointer, other._pointer); }
        unique_ptr& operator=(unique_ptr<T>&& other) noexcept {
            reset(other.release());
            return *this;
        }
        unique_ptr& operator=(const unique_ptr<T>&) noexcept = delete;
        bool operator==(const unique_ptr<T>& other) const noexcept { return get() == other.get(); }
        bool operator!=(const unique_ptr<T>& other) const noexcept { return get() != other.get(); }
        bool operator<(const unique_ptr<T>& other) const noexcept { return get() < other.get(); }
        bool operator>(const unique_ptr<T>& other) const noexcept { return get() > other.get(); }
        bool operator<=(const unique_ptr<T>& other) const noexcept { return get() <= other.get(); }
        bool operator>=(const unique_ptr<T>& other) const noexcept { return get() >= other.get(); }
        explicit operator bool() const noexcept { return _pointer != nullptr; }
        T& operator*() { return *get(); }
        T* operator->() { return get(); }

    private:
        T* _pointer{nullptr};
    };

    // Specialization for arrays:
    template <class T> class unique_ptr<T[]> {
        friend std::ostream& operator<<(std::ostream&, const unique_ptr<T>&);
    public:
        unique_ptr() noexcept= default;
        explicit unique_ptr(std::nullptr_t nptr) noexcept: _pointer{nptr} {}
        explicit unique_ptr(T pointer[]) noexcept : _pointer{pointer} {}
        unique_ptr(const unique_ptr<T>&) noexcept= delete;
        unique_ptr(unique_ptr<T>&& other) noexcept : _pointer {other.release()}{};
        ~unique_ptr() { delete[] _pointer; }

        T* get() const noexcept { return _pointer; }
        T* release() noexcept {
            T* temp_ptr {get()};
            _pointer = nullptr;
            return temp_ptr;
        }
        void reset(T* pointer = T()) noexcept {
            delete _pointer;
            _pointer = pointer;
        }
        void reset(std::nullptr_t nptr) noexcept {
            delete _pointer;
            _pointer = nptr;
        }
        void swap(unique_ptr<T>& other) { std::swap(_pointer, other._pointer); }
        unique_ptr& operator=(unique_ptr<T>&& other) noexcept {
            reset(other.release());
            return *this;
        }

        unique_ptr& operator=(const unique_ptr<T>&) noexcept = delete;
        bool operator==(const unique_ptr<T>& other) const noexcept { return get() == other.get(); }
        bool operator!=(const unique_ptr<T>& other) const noexcept { return get() == other.get(); }
        bool operator<(const unique_ptr<T>& other) const noexcept { return get() < other.get(); }
        bool operator>(const unique_ptr<T>& other) const noexcept { return get() > other.get(); }
        bool operator<=(const unique_ptr<T>& other) const noexcept { return get() <= other.get(); }
        bool operator>=(const unique_ptr<T>& other) const noexcept { return get() >= other.get(); }
        explicit operator bool() const noexcept { return _pointer != nullptr; }
        T& operator*() { return *get(); }
        T* operator->() { return get(); }
        T& operator[](const std::size_t& index) { return *(get() + index); }

    private:
        T* _pointer{nullptr};
    };
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const ali::unique_ptr<T>& u_ptr) {
    out << u_ptr.get();
    return out;
}

#endif //ALI_UNIQUE_PTR_H