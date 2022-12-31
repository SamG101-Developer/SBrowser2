#ifndef SBROWSER2_SRC_EXT_MACROS_PIMPL2_HPP
#define SBROWSER2_SRC_EXT_MACROS_PIMPL2_HPP

#include <memory>
#include <utility>
#include <self_macro.h>

#include "javascript/macros/expose.hpp"
#include "javascript/macros/errors.hpp"


/* PIMPL */

#define MAKE_PIMPL(type)                     \
public:                                      \
    using this_t = type;                     \
    using this_private_t = type ## _private; \
    friend struct type ## _private;          \
    _MAKE_PIMPL(type)

#define MAKE_PIMPL_T(type, ...)                           \
public:                                                   \
    using this_t = type<__VA_ARGS__>;                     \
    using this_private_t = type ## _private<__VA_ARGS__>; \
    friend struct type ## _private<__VA_ARGS__>;          \
    _MAKE_PIMPL(type)


#define MAKE_QIMPL(type)             \
public:                              \
    using this_public_t = type;      \
    using this_t = type ## _private; \
    friend struct type;              \
    _MAKE_QIMPL(type)

#define MAKE_QIMPL_T(type, ...)                   \
public:                                           \
    using this_public_t = type<__VA_ARGS__>;      \
    using this_t = type ## _private<__VA_ARGS__>; \
    friend struct type<__VA_ARGS__>;              \
    _MAKE_QIMPL(type)


// This macro makes a class a PIMPL public class -- this is done by defining alias types for the type of this class and
// its corresponding private class (used in class methods). Define 2 methods to access the PIMPL pointer in their class.
#define _MAKE_PIMPL(type)                                                                                                             \
private:                                                                                                                              \
    inline auto d_func() noexcept -> this_private_t* {return reinterpret_cast<this_private_t*>(this->d_ptr.get());}                   \
    inline auto d_func() const noexcept -> const this_private_t* {return reinterpret_cast<const this_private_t*>(this->d_ptr.get());} \
public:


// This macro makes a class a PIMPL private class -- this is done by defining alias types fo the type of this class and
// its corresponding public class (used in class methods). Define 2 methods to access the QIMPL pointer in their class.
#define _MAKE_QIMPL(type)                                                                                                           \
private:                                                                                                                            \
    inline auto q_func() noexcept -> this_public_t* {return reinterpret_cast<this_public_t*>(this->q_ptr.get());}                   \
    inline auto q_func() const noexcept -> const this_public_t* {return reinterpret_cast<const this_public_t*>(this->q_ptr.get());} \
public:


// Initialize the private class of a public class by creating the unique pointer to the private type of this class
// (defined by the MAKE_PIMPL(...) macro), and set the private class's public class pointer to this.
#define INIT_PIMPL                                                  \
    static_assert(                                                  \
        std::is_final_v<this_t> == std::is_final_v<this_private_t>, \
        "Public and private class must have a matching final tag"); \
    this->d_ptr = std::make_unique<this_private_t>();               \
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
#define DEFINE_PUBLIC_CLASS(ns, c) \
    import ext.core;               \
    import js.env.module_type;     \
    export import :p;              \
    namespace ns {export class c;} \
    export class ns::c

#define DEFINE_PUBLIC_CLASS_T(ns, c, ...)                 \
    import ext.core; import ext.js                        \
    import js.env.module_type;                            \
    export import :p;                                     \
    namespace ns {export template <__VA_ARGS__> class c;} \
    export template <__VA_ARGS__> class ns::c


// Define a private class, defining the class and its corresponding public class in their respective namespaces, and
// then beginning the definition of the class. Note: cannot be created in the global namespace.
#define DEFINE_PRIVATE_CLASS(ns, c)             \
    import ext.core; import ext.js;             \
    namespace ns {export struct c ## _private;} \
    export struct ns::c ## _private

#define DEFINE_PRIVATE_CLASS_T(ns, c, ...)                             \
    namespace ns {export template <__VA_ARGS__> struct c ## _private;} \
    export template <__VA_ARGS__> struct ns::c ## _private


/* NAMESPACE DEFINITIONS */

#define DEFINE_FWD_DECL_NAMESPACE(ns) \
    export namespace ns

#define DEFINE_FWD_DECL_NAMESPACE_DETAIL(ns) \
    export namespace ns::detail

#define DEFINE_FWD_DECL_NAMESPACE_MIXINS(ns) \
    export namespace ns::mixins

#define DEFINE_FWD_DECL_NAMESPACE_CONCEPTS(ns) \
    export namespace ns::concepts

#define IMPORT_ALL_TYPES(ns) \
    import apis.ns.types


/* PROPERTIES */

// This macro forwards an assignment value of a class into a setter instead. It works slightly different than in web
// specs: the actual code operation is the same, but how and where the macro is defined is different.
#define PUT_FORWARDS(setter)                      \
    template <typename T>                         \
    auto operator=(T&& new_val) -> decltype(auto) \
    {setter(std::forward<T>(new_val));}


// Define a getter for a property and its type
#define DEFINE_GETTER(p, t) \
    auto get_ ## p() const -> t


// Define a setter for a property and its type
#define DEFINE_SETTER(p, t) \
    auto set_ ## p(t new_ ## p) -> ext::view_of_t<t>


// Define a static getter for a property and its type
#define DEFINE_STATIC_GETTER(p, t) \
    static auto get_ ## p() -> t


// Define a static setter for a property and its type
#define DEFINE_STATIC_SETTER(p, t) \
    static auto set_ ## p(t new_ ## p) -> t


#define COMMA ,


/* OPTIONAL CLASS MEMBERS */

// The stringifier is defined as the 'operator ext::string()' of a class, for uniformity within C++ and JavaScript --
// this method will always be converted to 'toJSON' view v8pp. It outputs the string representation of the class.
// Defined as private as only the JavaScript interop code uses it.
#define MAKE_STRINGIFIER \
private:                 \
    operator ext::string() const


// Make a class serializable by defining 2 methods -- one to serialize the class into a map and one to deserialize a
// class from a map into this class.
#define MAKE_SERIALIZABLE \
    auto _serialize(ext::map<ext::string, ext::any>& serialized, ext::boolean for_storage) -> void; \
    auto _deserialize(const ext::map<ext::string, ext::any>& serialized, ext::boolean for_storage) -> this_t*;


// A transferable class is a class that inherits the EventTarget interface (so implicitly has no copy constructor or
// assignment), but has copy steps defined specially.
#define MAKE_TRANSFERABLE(t) \
    t(const t& other);       \
    auto operator=(const t& other) -> decltype(auto);


/* LANGUAGE SHORTHAND */
#define return_if(condition) if (condition) return
#define constexpr_return_if(condition) if constexpr (condition) return
#define break_if(condition) if (condition) break
#define continue_if(condition) if (condition) continue
#define for_if(if_statement, for_statement) if (if_statement) for (for_statement)

#define string_switch(_String) switch(ext::hash{}(_String))
#define string_case(_String) case(ext::hash{}(_String))
#define string_default default

#define _EXT_NODISCARD [[nodiscard]]
#define _EXT_FALLTHOUGH [[fallthrough]]


/* CLASS ANNOTATIONS */
#define friends
#define typedefs
#define constructors

#define js_static_constants
#define js_methods
#define js_properties


/* CONSTRUCTORS */
#define DISALLOW_COPY(type)     \
    type(const type&) = delete; \
    auto operator=(const type&) -> type& = delete

#define ALLOW_COPY(type)               \
    type(const type&) = default; \
    auto operator=(const type&) -> type& = default

#define ALLOW_MOVE(type)             \
    type(type&&) noexcept = default; \
    auto operator=(type&&) noexcept -> type& = delete

#define DOM_CTORS(type)  \
    type();              \
    DISALLOW_COPY(type); \
    ALLOW_MOVE(type)


#endif //SBROWSER2_SRC_EXT_MACROS_PIMPL2_HPP
