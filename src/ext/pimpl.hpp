#ifndef SBROWSER2_SRC_EXT_PIMPL_HPP
#define SBROWSER2_SRC_EXT_PIMPL_HPP

#include <memory>
#include "ext/keywords.hpp"


// Use this macro at the beginning of every class that will have a PIMPL private class attached to it. It exposes the
// d_ptr, but cast into the correct type, as well as friending the private class. There are non-const and const verisons
// of the d_func() for const and non-const interface-method access.
#define MAKE_PIMPL(c) \
    inline c ## _private* d_func() noexcept {return reinterpret_cast<c ## _private*>(d_ptr.get());} \
    inline const c ## _private* d_func() const noexcept {return reinterpret_cast<const c ## _private*>(d_ptr.get());} \
    friend c ## _private


// Initialize the PIMPL private class by setting it to a unique pointer of the corresponding private class. Only the
// base class actually defines the d_ptr (std::unique_ptr<dom_object_private>), so only 1 private class exsists in
// inheritance chains.
#define INIT_PIMPL(c) \
    d_ptr = std::make_unique<c ## _private>()


// Access the d_func() in interface-methods with a convenient d pointer. It's a const-pointer (not pointer-to-const), so
// it acts like the 'this' pointer, for the PIMPL private class. In const-interface-methods, it will act as a
// const-pointer-const pointer. Accessed as a raw pointer.
#define ACCESS_PIMPL(Class) \
    Class##_private* const d = d_func()


// Forward declare the existence of a private class in a namespace, and then begin the definition of the struct. Follow
// the macro with an opening brace, the definition of attributes, and a closing brace.
#define DEFINE_PRIVATE_CLASS(ns, c)     \
    namespace ns {class c ## _private;} \
    struct ns:: c ## _private


#endif //SBROWSER2_SRC_EXT_PIMPL_HPP
