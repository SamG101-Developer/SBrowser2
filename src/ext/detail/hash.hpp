#pragma once
#ifndef SBROWSER2_HASH_HPP
#define SBROWSER2_HASH_HPP

#include <functional>
#include <ext/type_traits.hpp>

namespace ext::detail {auto constexpr _Hash(std::string_view _S) -> size_t;}

auto constexpr ext::detail::_Hash(std::string_view _S) -> size_t
{
    std::hash<std::string_view> _Hasher;
    return _Hasher(_S);
}


#endif //SBROWSER2_HASH_HPP
