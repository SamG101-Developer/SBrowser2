#ifndef SBROWSER2_SRC_EXT_MACROS_PIMPL2_HPP
#define SBROWSER2_SRC_EXT_MACROS_PIMPL2_HPP

#include <self_macro.h>


// This macro makes a class a PIMPL public class -- this is done by defining alias types for the type of this class and
// its corresponding private class (used in class methods). Define 2 methods to access the PIMPL pointer in their class,
// and friend the private class.
#define MAKE_PIMPL_2(type)                                                                                   \
public:                                                                                                      \
    using this_t = type;                                                                                     \
    using this_private_t = type ## _private;                                                                 \
private:                                                                                                     \
    inline auto d_func() noexcept {return reinterpret_cast<this_private_t*>(this->d_ptr.get());}             \
    inline auto d_func() const noexcept {return reinterpret_cast<const this_private_t*>(this->d_ptr.get());} \
    friend struct type ## _private;                                                                          \
public:


// This macro makes a class a PIMPL private class -- this is done by defining alias types fo the type of this class and
// its corresponding public class (used in class methods). Define 2 methods to access the QIMPL pointer in their class,
// and friend the public class.
#define MAKE_QIMPL_2(type)                                                                                  \
public:                                                                                                     \
    using this_t = type ## _private;                                                                        \
    using this_public_t = type;                                                                             \
private:                                                                                                    \
    inline auto q_func() noexcept {return reinterpret_cast<this_public_t*>(this->q_ptr.get());}             \
    inline auto q_func() const noexcept {return reinterpret_cast<const this_public_t*>(this->q_ptr.get());} \
    friend class type;                                                                                      \
public:


// Initialize the private class of a public class by creating the unique pointer to the private type of this class
// (defined by the MAKE_PIMPL(...) macro), and set the private class's public class pointer to this.
#define INIT_PIMPL_2                                  \
    this->d_ptr = std::make_unique<this_private_t>(); \
    d_func()->q_ptr = this;


// Get access to the d_ptr by casting it via the d_func() method -- make it a const pointer, and possibly a const
// pointer const, depending on the context of the class.
#define ACCESS_PIMPL_2 \
    auto* const d = d_func();


// Get access to the q_ptr by casting it via the q_func() method -- make it a const pointer, and possibly a const
// pointer const, depending on the context of the class.
#define ACCESS_QIMPL_2 \
    auto* const q = q_func();


// Define a public class, defining the class and its corresponding private class in their respective namespaces, and
// then beginning the definition of the class. Note: cannot be created in the global namespace.
#define DEFINE_PUBLIC_CLASS_2(ns, c)     \
    namespace ns {class c;}              \
    namespace ns {struct c ## _private;} \
    class ns:: c


// Define a private class, defining the class and its corresponding public class in their respective namespaces, and
// then beginning the definition of the class. Note: cannot be created in the global namespace.
#define DEFINE_PRIVATE_CLASS_2(ns, c)    \
    namespace ns {class c;}              \
    namespace ns {struct c ## _private;} \
    struct ns:: c ## _private


#endif //SBROWSER2_SRC_EXT_MACROS_PIMPL2_HPP
