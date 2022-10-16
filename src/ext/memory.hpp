#ifndef SBROWSER2_SRC_EXT_MEMORY_HPP
#define SBROWSER2_SRC_EXT_MEMORY_HPP

#include "ext/concepts.hpp"


_STD_BEGIN

template <class T>
class observer_ptr {
public:
    using value_type = T;
    using pointer = std::add_pointer_t<T>;
    using const_pointer = std::add_pointer_t<const T>;
    using reference = std::add_lvalue_reference_t<T>;
    using const_reference = std::add_lvalue_reference_t<const T>;

public:
    constexpr observer_ptr() noexcept;
    constexpr observer_ptr(nullptr_t) noexcept;
    explicit observer_ptr(pointer) noexcept;
    template <class U> explicit observer_ptr(U*) noexcept;
    template <class U> observer_ptr(const observer_ptr<U>&) noexcept;

    observer_ptr& operator=(nullptr_t) noexcept;
    template <class U> observer_ptr& operator=(U* other) noexcept;
    template <class U> observer_ptr& operator=(const observer_ptr<U>&) noexcept;

    pointer get() const noexcept;
    reference operator*() const noexcept;
    pointer operator->() const noexcept;
    explicit operator bool() const noexcept;

    explicit operator pointer() noexcept;
    explicit operator const_pointer() const noexcept;

    pointer release() noexcept;
    void reset(pointer t = nullptr) noexcept;
    void swap(observer_ptr&) noexcept;
};


_STD_END


#endif //SBROWSER2_SRC_EXT_MEMORY_HPP
