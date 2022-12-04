#ifndef SBROWSER2_SRC_EXT_MACROS_PROPERTY_HPP
#define SBROWSER2_SRC_EXT_MACROS_PROPERTY_HPP


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
    auto set_ ## p(t new_ ## p) -> t


// Define a static getter for a property and its type
#define DEFINE_STATIC_GETTER(p, t) \
    static auto get_ ## p() -> t


// Define a static setter for a property and its type
#define DEFINE_STATIC_SETTER(p, t) \
    static auto set_ ## p(t new_ ## p) -> t


#endif //#ifndef SBROWSER2_SRC_EXT_MACROS_PROPERTY_HPP
