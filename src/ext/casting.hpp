#pragma once
#ifndef SBROWSER2_CASTING_HPP
#define SBROWSER2_CASTING_HPP

namespace ext {template <typename ..._Valty> auto multi_cast(auto* _Pointer) -> bool;}
namespace ext {template <typename       _Ty> auto cross_cast(auto* _Pointer) -> _Ty;}


template <typename ..._Valty>
auto ext::multi_cast(auto* _Pointer) -> bool
{
    // check if the pointer can be cast into any of the types in _Valty parameter pack
    return ((dynamic_cast<_Valty>(_Pointer)) || ...);
}


template <typename _Ty>
auto ext::cross_cast(auto* _Pointer) -> bool
{
    // perform a dynamic_cast TODO : error if cast is nullptr?
    return dynamic_cast<_Ty>(_Pointer);
}


#endif //SBROWSER2_CASTING_HPP
