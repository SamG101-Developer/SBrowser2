#pragma once
#ifndef SBROWSER2_CASTING_HPP
#define SBROWSER2_CASTING_HPP

namespace ext {template <typename ..._Valty> auto multi_cast(auto* _Pointer) -> bool;}
namespace ext {template <typename       _Ty> auto cross_cast(auto* _Pointer) -> _Ty;}


template <typename ..._Valty>
auto ext::multi_cast(auto* _Pointer) -> bool
{
    // check if the pointer can be cast into any of the types in _Valty parameter pack - the function returns a boolean
    // rather than a cast pointer, because it could return a cast into any successful type, so it is more used for yes/
    // no the pointer is this type, as opposed to using the functionality of a dynamically cast type
    return ((dynamic_cast<_Valty>(_Pointer)) || ...);
}


template <typename _Ty>
auto ext::cross_cast(auto* _Pointer) -> _Ty
{
    // syntactic sugar for a dynamic cast from one superclass to a sibling-level superclass of an object - for example,
    // if a type C inherits A, B, and A* object = new C{}, the type can be cast from A* -> B*, ie the type has been
    // "cross" cast to a sibling level superclass. throws an error is the cast was unsuccessful
    auto* cross_cast_pointer = dynamic_cast<_Ty>(_Pointer);
    assert(cross_cast_pointer);
    return cross_cast_pointer;
}


#endif //SBROWSER2_CASTING_HPP
