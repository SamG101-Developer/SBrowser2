#ifndef SBROWSER2_SRC_EXT_PIMPL_HPP
#define SBROWSER2_SRC_EXT_PIMPL_HPP

#include "ext/concepts.hpp"
#include <memory>
#include <self_macro.h>


_EXT_BEGIN
    // Lambda that accesses the 'd_func()' method of a PIMPL-enabled class; this is defined for binding to ranges-v3
    // views such as transformation, as it heavily deconvolutes code especially for classes in different namespaces.
    auto get_pimpl = []<typename T>(T* object) {return object->d_func();};
_EXT_END


// Use this macro at the beginning of every class that will have a PIMPL private class attached to it. It exposes the
// d_ptr, but cast into the correct type, as well as friending the private class. There are non-const and const verisons
// of the d_func() for const and non-const interface-method access. Defines 'self_t' as a type alias to the current
// class.
#define MAKE_PIMPL(c)                                                                                                       \
private:                                                                                                                    \
    inline c ## _private* d_func() noexcept {return reinterpret_cast<c ## _private*>(this->d_ptr.get());}                   \
    inline const c ## _private* d_func() const noexcept {return reinterpret_cast<const c ## _private*>(this->d_ptr.get());} \
    friend c ## _private;                                                                                                   \
    SELF_MACRO_DEFINE_SELF(self_t, public)

// Use this macro at the beginning of every templated class that will have a PIMPL private templated class attached to
// it. It exposes the d_ptr, but cast into the correct templated type, as well as friending the private templated class.
// There are non-const and const verisons of the d_func() for const and non-const interface-method access. Defines
// 'self_t' as a type alias to the current templated class.
#define MAKE_PIMPL_TEMPLATED(c, ...)                                                                                                                  \
private:                                                                                                                                              \
    inline c ## _private<__VA_ARGS__>* d_func() noexcept {return reinterpret_cast<c ## _private<__VA_ARGS__>*>(this->d_ptr.get());}                   \
    inline const c ## _private<__VA_ARGS__>* d_func() const noexcept {return reinterpret_cast<const c ## _private<__VA_ARGS__>*>(this->d_ptr.get());} \
    friend c ## _private<__VA_ARGS__>;                                                                                                                \
    SELF_MACRO_DEFINE_SELF(self_t, public)


// Initialize the PIMPL private class by setting it to a unique pointer of the corresponding private class. Only the
// base class actually defines the d_ptr (std::unique_ptr<dom_object_private>), so only 1 private class exsists in
// inheritance chains, saving memory.
#define INIT_PIMPL(c) \
    this->d_ptr = std::make_unique<c ## _private>()

// Initialize the PIMPL private templated class by setting it to a unique pointer of the corresponding private templated
// class. Only the base class actually defines the d_ptr (std::unique_ptr<dom_object_private>), so only 1 private class
// exsists in inheritance chains, saving memory.
#define INIT_PIMPL_TEMPLATED(c, ...) \
    this->d_ptr = std::make_unique<c ## _private<__VA_ARGS__>>()


// Access the d_func() in interface-methods with a convenient d pointer. It's a const-pointer (not pointer-to-const), so
// it acts like the 'this' pointer, for the PIMPL private class. In const-interface-methods, it will act as a
// const-pointer-const pointer. Accessed as a raw pointer.
#define ACCESS_PIMPL(c) \
    c ## _private* const d = d_func()

// Access the d_func() in interface-methods with a convenient d pointer. It's a const-pointer (not pointer-to-const), so
// it acts like the 'this' pointer, for the PIMPL private templated class. In const-interface-methods, it will act as a
// const-pointer-const pointer. Accessed as a raw pointer.
#define ACCESS_PIMPL_TEMPLATED(c, ...) \
    c ## _private<__VA_ARGS__>* const d = d_func()


// Forward declare the existence of a private class in a namespace, and then begin the definition of the struct. Follow
// the macro with an opening brace, the definition of attributes, and a closing brace.
#define DEFINE_PRIVATE_CLASS(ns, c)      \
    namespace ns {struct c ## _private;} \
    struct ns:: c ## _private

// Forward declare the existence of a private templated class in a namespace, and then begin the definition of the
// templated struct. Follow the macro with an opening brace, the definition of attributes, and a closing brace.
#define DEFINE_PRIVATE_CLASS_TEMPLATED(ns, c, ...)               \
    namespace ns {template <__VA_ARGS__> struct c ## _private;} \
    template <__VA_ARGS__> struct ns:: c ## _private


#endif //SBROWSER2_SRC_EXT_PIMPL_HPP
