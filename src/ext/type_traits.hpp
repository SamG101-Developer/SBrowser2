#pragma once
#ifndef SBROWSER2_TYPE_TRAITS_HPP
#define SBROWSER2_TYPE_TRAITS_HPP

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/functional.hpp"
#include "ext/keywords.hpp"
#include "ext/map.hpp"
#include "ext/number.hpp"
#include "ext/tuple.hpp"
#include "ext/variant.hpp"

#include <functional>
#include <memory>
#include <type_traits>


#define DEFINE_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPES(_TemplateParameter_t, _Name, _DefaultType) \
    template <_TemplateParameter_t T>                                                                   \
    struct _Name {using type = _DefaultType;};                                                          \
                                                                                                        \
    template <_TemplateParameter_t T>                                                                   \
    using _Name##_t = typename _Name<T>::type

#define ADD_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPE(_Name, _Specialization, _Ret_t) \
    template<>                                                                           \
    struct _Name<_Specialization> {using type = _Ret_t;}


// type definitions
using longlong  = long long;

using uchar     = unsigned char;
using ushort    = unsigned short;
using uint      = unsigned int;
using ulong     = unsigned long;
using ulonglong = unsigned long long;


// pointer deduction for raw and smart pointers together

_EXT_BEGIN

template <typename T>
struct _unwrap_smart_pointer;

template <smart_pointer T>
struct _unwrap_smart_pointer<T> {using type = typename T::pointer;};

template <typename T>
struct _unwrap_smart_pointer {using type = T;};

template <typename T>
using unwrap_smart_pointer = _unwrap_smart_pointer<std::remove_cvref_t<T>>;

template <typename T>
using unwrap_smart_pointer_t = typename unwrap_smart_pointer<T>::type;


// extend variant with a new types
template <typename Old, typename ...New>
struct _extend_variant;

template <typename Old, typename ...New>
struct _extend_variant {using type = Old;};

template <typename ...Old, typename ...New>
struct _extend_variant<variant<Old...>, New...> {using type = variant<Old..., New...>;};

template <typename Old, typename ...New>
using extend_variant = _extend_variant<Old, New...>;

template <typename Old, typename ...New>
using extend_variant_t = typename _extend_variant<Old, New...>::type;


// other

template <typename T, typename F = std::less<T>>
auto three_way_compare(T&& lhs, T&& rhs, F&& lt_predicate = std::less<T>{}) -> ext::boolean
{
    if (lhs == rhs) return 0;
    return lt_predicate(std::forward<T>(lhs), std::forward<T>(rhs)) ? -1 : 1;
}

_EXT_END



// std::hash implementations

_STD_BEGIN

template <>
struct hash<_EXT boolean>
{
    constexpr auto operator()(const _EXT boolean& value) const noexcept -> size_t {return value ? 1 : 0;}
};


template <typename T>
struct hash<_EXT number<T>>
{
    constexpr auto operator()(const _EXT number<T>& value) const noexcept -> size_t {return _STD hash<T>{}(static_cast<T>(value));}
};


template <typename T>
struct hash<_STD function<T>> // TODO -> ext::function<T...> once its ready for implementation
{
    constexpr auto operator()(std::function<T> value) const noexcept -> size_t {return _STD hash<size_t>{}(static_cast<size_t>(&value));}
};


template <typename ...Ts>
struct hash<_EXT function<Ts...>>
{
    constexpr auto operator()(const _EXT function<Ts...>& value) const noexcept -> size_t {return _STD hash<size_t>{}(static_cast<size_t>(&value));}
};


template <>
struct hash<_EXT any>
{
    constexpr auto operator()(const _EXT any& value) const noexcept -> size_t {return _STD hash<size_t>{}(static_cast<size_t>(&value));}
};


template <typename K, typename V>
struct hash<_EXT map<K, V>>
{
    constexpr auto operator()(const _EXT map<K, V>& value) const noexcept -> size_t {return _STD hash<size_t>{}(&value);}
};


template <typename ...Ts>
struct hash<_EXT tuple<Ts...>>
{
    constexpr auto operator()(const _EXT tuple<Ts...>& value) const noexcept -> size_t {return 0;} // TODO _STD hash<size_t>{}(&value);}
};

_STD_END


#endif //SBROWSER2_TYPE_TRAITS_HPP
