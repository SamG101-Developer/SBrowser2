#pragma once
#ifndef SBROWSER2_SRC_EXT_ENUMS_HPP
#define SBROWSER2_SRC_EXT_ENUMS_HPP

#include "ext/concepts.hpp"

template <type_is_enum T>
constexpr auto operator|(T lhs, T rhs) -> T
{
    return std::bit_cast<T>(std::bit_cast<std::underlying_type_t<T>>(lhs) | std::bit_cast<std::underlying_type_t<T>>(rhs));
}


template <type_is_enum T>
constexpr auto operator&(T lhs, T rhs) -> bool
{
    return static_cast<bool>(std::bit_cast<std::underlying_type_t<T>>(lhs) & std::bit_cast<std::underlying_type_t<T>>(rhs));
}


#endif //SBROWSER2_SRC_EXT_ENUMS_HPP
