#ifndef SBROWSER2_SRC_EXT_MACROS_PIMPL2_HPP
#define SBROWSER2_SRC_EXT_MACROS_PIMPL2_HPP

#include <utility>
#include <self_macro.h>


#define MAKE_PIMPL(type)                     \
    using this_private_t = type ## _private; \
    friend struct type ## _private;          \
    _MAKE_PIMPL(type)

#define MAKE_PIMPL_T(type, ...)                           \
    using this_private_t = type ## _private<__VA_ARGS__>; \
    friend struct type ## _private<__VA_ARGS__>;          \
    _MAKE_PIMPL(type)


#define MAKE_QIMPL(type)             \
    using this_t = type ## _private; \
    friend struct type;              \
    _MAKE_QIMPL(type)

#define MAKE_QIMPL_T(type, ...)                   \
    using this_t = type ## _private<__VA_ARGS__>; \
    friend struct type<__VA_ARGS__>;              \
    _MAKE_QIMPL(type)


// This macro makes a class a PIMPL public class -- this is done by defining alias types for the type of this class and
// its corresponding private class (used in class methods). Define 2 methods to access the PIMPL pointer in their class.
#define _MAKE_PIMPL(type)                                                                                    \
public:                                                                                                      \
    using this_t = type;                                                                                     \
private:                                                                                                     \
    inline auto d_func() noexcept -> this_private_t* {return reinterpret_cast<this_private_t*>(this->d_ptr.get());}             \
    inline auto d_func() const noexcept -> const this_private_t* {return reinterpret_cast<const this_private_t*>(this->d_ptr.get());} \
public:


// This macro makes a class a PIMPL private class -- this is done by defining alias types fo the type of this class and
// its corresponding public class (used in class methods). Define 2 methods to access the QIMPL pointer in their class.
#define _MAKE_QIMPL(type)                                                                                   \
public:                                                                                                     \
    using this_public_t = type;                                                                             \
private:                                                                                                    \
    inline auto q_func() noexcept -> this_public_t* {return reinterpret_cast<this_public_t*>(this->q_ptr.get());}             \
    inline auto q_func() const noexcept -> const this_public_t* {return reinterpret_cast<const this_public_t*>(this->q_ptr.get());} \
public:


// Initialize the private class of a public class by creating the unique pointer to the private type of this class
// (defined by the MAKE_PIMPL(...) macro), and set the private class's public class pointer to this.
#define INIT_PIMPL                                    \
    this->d_ptr = std::make_unique<this_private_t>(); \
    d_func()->q_ptr = this


// Get access to the d_ptr by casting it via the d_func() method -- make it a const pointer, and possibly a const
// pointer const, depending on the context of the class.
#define ACCESS_PIMPL \
    auto* const d = d_func()


// Get access to the q_ptr by casting it via the q_func() method -- make it a const pointer, and possibly a const
// pointer const, depending on the context of the class.
#define ACCESS_QIMPL \
    auto* const q = q_func()


// Define a public class, defining the class and its corresponding private class in their respective namespaces, and
// then beginning the definition of the class. Note: cannot be created in the global namespace.
#define DEFINE_PUBLIC_CLASS(ns, c)     \
    namespace ns {export class c;}              \
    namespace ns {struct c ## _private;} \
    export class ns:: c


// Define a private class, defining the class and its corresponding public class in their respective namespaces, and
// then beginning the definition of the class. Note: cannot be created in the global namespace.
#define DEFINE_PRIVATE_CLASS(ns, c)    \
    namespace ns {class c;}              \
    namespace ns {export struct c ## _private;} \
    export struct ns:: c ## _private


#endif //SBROWSER2_SRC_EXT_MACROS_PIMPL2_HPP
