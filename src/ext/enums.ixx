export module ext.enums_;
import ext.concepts;
import std.core;


template <ext::type_is_enum T>
export constexpr auto operator|(T lhs, T rhs) -> T
{return std::bit_cast<T>(std::bit_cast<std::underlying_type_t<T>>(lhs) | std::bit_cast<std::underlying_type_t<T>>(rhs));}


template <ext::type_is_enum T>
export constexpr auto operator&(T lhs, T rhs) -> bool
{return static_cast<bool>(std::bit_cast<std::underlying_type_t<T>>(lhs) & std::bit_cast<std::underlying_type_t<T>>(rhs));}


template <ext::type_is_enum T>
export constexpr auto operator!(T rhs) -> bool
{return std::bit_cast<std::underlying_type_t<T>>(rhs) != std::bit_cast<std::underlying_type_t<T>>(0);}


_EXT_BEGIN
    template <_EXT type_is_enum ...Types>
    export struct enum_list;
_EXT_END


#endif //SBROWSER2_SRC_EXT_ENUMS_HPP
