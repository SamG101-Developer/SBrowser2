#pragma once
#ifndef SBROWSER2_HASH_HPP
#define SBROWSER2_HASH_HPP

#include <ext/type_traits.hpp>


namespace ext::detail {auto constexpr hash(const char* s) -> size_t;}
namespace {constexpr ulong a = 54059;}
namespace {constexpr ulong b = 76963;}
namespace {constexpr ulong c = 86969;}
namespace {constexpr ulong d = 00037;}

auto constexpr ext::detail::hash(const char* s) -> size_t
{
    auto h = d;
    while (*s) {h = (h * a) ^ (s[0] * b); s++;}
    return h;
}


#endif //SBROWSER2_HASH_HPP
