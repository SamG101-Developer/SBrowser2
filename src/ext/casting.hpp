#pragma once
#ifndef SBROWSER2_CASTING_HPP
#define SBROWSER2_CASTING_HPP

#include <type_traits>
#include "ext/assertion.hpp"
#include "ext/concepts.hpp"
#include "ext/variant.hpp"


_EXT_BEGIN

auto cast_functor_ranges = []<typename T>(auto* value) {return dynamic_cast<T>(value);};


// Special const cast can convert a 'const ptr* const' to a 'ptr*' type
template <_EXT is_pointer_or_reference T>
struct remove_const_to_const
{using type = std::remove_cv_t<T>;};

template <_EXT is_pointer_or_reference T>
struct remove_const_to_const<const T>
{using type = std::remove_cv_t<T>;};

template <_EXT is_pointer_or_reference T>
using remove_const_to_const_t = typename remove_const_to_const<T>::type;


template <_EXT is_pointer_or_reference ...Ts, _EXT is_pointer T>
auto multi_cast(T pointer) -> bool
{
    // Check if the pointer can be cast into any of the types in Ts parameter pack - the function returns a boolean
    // rather than a cast pointer, because it could return a cast into any successful type, so it is more used for yes/
    // no the pointer is this type, as opposed to using the functionality of a dynamically cast type. Becuase the cast
    // isn't actually ever used from this function call (not returned), const-correctess doesn't matter, so allow for
    // example a 'const node*' to be tested as an 'element*,' not just a 'const element*' (shortens code).
    decltype(auto) non_const_pointer = const_cast<remove_const_to_const_t<T>>(pointer);
    return (dynamic_cast<remove_const_to_const_t<Ts>>(non_const_pointer) || ...);
}


template <_EXT is_pointer_or_reference T>
auto cross_cast(auto pointer) -> T
{
    // syntactic sugar for a dynamic cast from one superclass to a sibling-level superclass of an object - for example,
    // if a type C inherits A, B, and A* object = new C{}, the type can be cast from A* -> B*, ie the type has been
    // "cross" cast to a sibling level superclass. throws an error is the cast was unsuccessful
    decltype(auto) cross_cast_pointer = dynamic_cast<T>(pointer);
    ASSERT(cross_cast_pointer, "Cross-casting must be successful", pointer);
    return cross_cast_pointer;
}


template <typename T, typename U>
auto iterator_cast(U iterator) -> T
{return (T)iterator;}


template <is_pointer T>
auto nullptr_cast()
{return static_cast<T>(nullptr);}


template <typename T> // TODO : _EXT type_is_any_specialization<_EXT variant> T
auto variant_cast(auto* pointer)
{
    return ext::visit([pointer](auto _) -> T {return dom_cast<decltype(_)>(pointer);}, T{});
}

_EXT_END


template <typename T>
auto dom_cast(auto pointer) -> T
{return dynamic_cast<T>(pointer);}


template <typename ...Ts>
auto dom_multi_cast(auto pointer) -> bool
{return _EXT multi_cast<Ts...>(pointer);}


template <typename T>
auto dom_cross_cast(auto pointer) -> T
{return _EXT cross_cast<T>(pointer);}


#endif //SBROWSER2_CASTING_HPP
