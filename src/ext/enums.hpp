#pragma once
#include <type_traits>
#ifndef SBROWSER2_SRC_EXT_ENUMS_HPP
#define SBROWSER2_SRC_EXT_ENUMS_HPP

#include "ext/concepts.hpp"


template <ext::type_is_enum T>
constexpr auto operator|(T lhs, T rhs) -> T
{
    return std::bit_cast<T>(std::bit_cast<std::underlying_type_t<T>>(lhs) | std::bit_cast<std::underlying_type_t<T>>(rhs));
}


template <ext::type_is_enum T>
constexpr auto operator&(T lhs, T rhs) -> bool
{
    return static_cast<bool>(std::bit_cast<std::underlying_type_t<T>>(lhs) & std::bit_cast<std::underlying_type_t<T>>(rhs));
}


template <ext::type_is_enum T>
constexpr auto operator!(T rhs) -> bool
{
    return std::bit_cast<std::underlying_type_t<T>>(rhs) != std::bit_cast<std::underlying_type_t<T>>(0);
}


#endif //SBROWSER2_SRC_EXT_ENUMS_HPP
