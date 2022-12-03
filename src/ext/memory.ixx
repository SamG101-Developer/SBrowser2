export module ext.memory;

import ext.boolean;
import ext.concepts;

// TODO : C++20 trailing return type formatting
// TODO : Implement methods
// TODO : Add more operators?


_STD_BEGIN

template <class T>
class observer_ptr final {
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
    template <class U> observer_ptr(const observer_ptr<U>&) noexcept = delete; // Use .get()
    template <class U> observer_ptr(observer_ptr<U>&&) noexcept = delete; // Use .get()
    observer_ptr(const observer_ptr&) noexcept = delete; // Use .get()
    observer_ptr(observer_ptr&&) noexcept = default; // Use .get()

    observer_ptr& operator=(nullptr_t) noexcept;
    template <class U> observer_ptr& operator=(U* other) noexcept;
    template <class U> observer_ptr& operator=(const observer_ptr<U>&) noexcept = delete; // Use .get()
    template <class U> observer_ptr& operator=(observer_ptr<U>&&) noexcept = delete; // Use .get()
    observer_ptr& operator=(const observer_ptr&) noexcept = delete; // Use .get()
    observer_ptr& operator=(observer_ptr&&) noexcept = default; // Use .get()

    pointer get() const noexcept;
    reference operator*() const noexcept;
    pointer operator->() const noexcept;
    explicit operator bool() const noexcept;

    explicit operator pointer() noexcept;
    explicit operator const_pointer() const noexcept;

    pointer release() noexcept;
    void reset(pointer t = nullptr) noexcept;
    void swap(observer_ptr&) noexcept;

private:
    T* raw;
};

_STD_END
