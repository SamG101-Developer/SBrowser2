#pragma once
#ifndef SBROWSER2_CASTING_HPP
#define SBROWSER2_CASTING_HPP

namespace ext {template <typename ..._Valty, typename _Ty> auto multi_cast(const _Ty* _Pointer) -> bool;}


template <typename ..._Valty, typename _Ty>
auto ext::multi_cast(const _Ty* const _Pointer) -> bool
{
    // check if the pointer can be cast into any of the types in _Valty template type pack
    return ((dynamic_cast<_Valty>(_Pointer)) or ...);
}


#endif //SBROWSER2_CASTING_HPP
