#pragma once
#ifndef SBROWSER2_HASH_HPP
#define SBROWSER2_HASH_HPP

#include <ext/type_traits.hpp>

namespace ext::detail {auto constexpr _Hash(const char* _S) -> size_t;}

auto constexpr ext::detail::_Hash(const char* _S) -> size_t
{
    constexpr ulong _A = 54059, _B = 76963, _C = 86969, _D = 37;

    auto _H = _D;
    while (*_S) {_H = (_H * _A) ^ (_S[0] * _B); _S++;}
    return _H;
}


#endif //SBROWSER2_HASH_HPP
