module;
#include "ext/macros/namespaces.hpp"

export module ext.enums;
import ext.concepts;
import std.core;


export template <ext::type_is_enum T>
constexpr auto operator|(T lhs, T rhs) -> T
{return std::bit_cast<T>(std::bit_cast<std::underlying_type_t<T>>(lhs) | std::bit_cast<std::underlying_type_t<T>>(rhs));}


export template <ext::type_is_enum T>
constexpr auto operator&(T lhs, T rhs) -> bool
{return static_cast<bool>(std::bit_cast<std::underlying_type_t<T>>(lhs) & std::bit_cast<std::underlying_type_t<T>>(rhs));}


export template <ext::type_is_enum T>
constexpr auto operator!(T rhs) -> bool
{return std::bit_cast<std::underlying_type_t<T>>(rhs) != std::bit_cast<std::underlying_type_t<T>>(0);}


_EXT_BEGIN
    export template <_EXT type_is_enum ...Types>
    struct enum_list;
_EXT_END

