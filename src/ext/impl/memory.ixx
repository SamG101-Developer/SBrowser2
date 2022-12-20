module;
#include "ext/macros/namespaces.hpp"
#include <type_traits>

export module ext.core:memory;
import :boolean;
import :concepts;

// TODO : C++20 trailing return type formatting


_STD_BEGIN
    export template <class T>
    class observer_ptr;
_STD_END


template <class T>
class std::observer_ptr final {
public:
    using value_type = T;
    using pointer = std::add_pointer_t<T>;
    using const_pointer = std::add_pointer_t<const T>;
    using reference = std::add_lvalue_reference_t<T>;
    using const_reference = std::add_lvalue_reference_t<const T>;

public:
    constexpr observer_ptr() noexcept = default;
    explicit observer_ptr(pointer ptr) noexcept {raw = ptr;}
    template <class U> explicit observer_ptr(U* ptr) noexcept {raw = ptr;}
    template <class U> observer_ptr(const observer_ptr<U>&) noexcept = delete;
    template <class U> observer_ptr(observer_ptr<U>&&) noexcept = delete;
    observer_ptr(const observer_ptr&) noexcept = delete;
    observer_ptr(observer_ptr&&) noexcept = default;

    observer_ptr& operator=(pointer ptr) noexcept {raw = ptr; return *this;}
    template <class U> observer_ptr& operator=(U* other) noexcept {raw = other; return *this;}
    template <class U> observer_ptr& operator=(const observer_ptr<U>&) noexcept = delete;
    template <class U> observer_ptr& operator=(observer_ptr<U>&&) noexcept = delete;
    observer_ptr& operator=(const observer_ptr&) noexcept = delete;
    observer_ptr& operator=(observer_ptr&&) noexcept = default;

    pointer get() const noexcept {return raw;}
    reference operator*() const noexcept {return *raw;}
    pointer operator->() const noexcept {return raw;}
    explicit operator bool() const noexcept {return raw != nullptr;}

    explicit operator pointer() noexcept {return raw;}
    explicit operator const_pointer() const noexcept {return raw;}

    // pointer release() noexcept;
    void reset(pointer t = nullptr) noexcept {std::swap(raw, t);}
    // void swap(observer_ptr&) noexcept;

private:
    T* raw = nullptr;
};
