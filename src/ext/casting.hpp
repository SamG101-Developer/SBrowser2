#pragma once
#ifndef SBROWSER2_CASTING_HPP
#define SBROWSER2_CASTING_HPP

#include <type_traits>
#include "ext/assertion.hpp"
#include "ext/concepts.hpp"
class dom_object;


_EXT_BEGIN

template <is_pointer_or_reference ...Ts>
auto multi_cast(auto pointer) -> bool
{
    // check if the pointer can be cast into any of the types in Ts parameter pack - the function returns a boolean
    // rather than a cast pointer, because it could return a cast into any successful type, so it is more used for yes/
    // no the pointer is this type, as opposed to using the functionality of a dynamically cast type
    using U = decltype(pointer);

    if constexpr (is_pointer<U>)
        return type_is<typename std::remove_pointer_t<U>::self_t*, Ts...>;
    else if constexpr (is_reference<U>)
        return type_is<typename std::remove_reference_t<U>::self_t&, Ts...>;
    else
        return type_is<typename U::self_t, Ts...>;
}


template <is_pointer_or_reference T>
auto cross_cast(auto* pointer) -> T
{
    // syntactic sugar for a dynamic cast from one superclass to a sibling-level superclass of an object - for example,
    // if a type C inherits A, B, and A* object = new C{}, the type can be cast from A* -> B*, ie the type has been
    // "cross" cast to a sibling level superclass. throws an error is the cast was unsuccessful
    auto* cross_cast_pointer = dynamic_cast<T>(pointer);
    ASSERT(cross_cast_pointer, "cross-casting must be successful", pointer);
    return cross_cast_pointer;
}


template <typename T, typename U>
auto iterator_cast(U iterator) -> T
{
    return (T)iterator;
}


template <is_pointer T>
auto nullptr_cast()
{
    return static_cast<T>(nullptr);
}


_EXT_END


template <typename T>
auto dom_cast(auto pointer) -> T
{
    return dynamic_cast<T>(pointer);
}


template <typename ...Ts>
auto dom_multi_cast(auto pointer) -> bool
{
    return _EXT multi_cast<Ts...>(pointer);
}


template <typename T>
auto dom_cross_cast(auto pointer) -> T
{
    return _EXT cross_cast<T>(pointer);
}


#endif //SBROWSER2_CASTING_HPP
