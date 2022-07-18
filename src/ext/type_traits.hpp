#pragma once
#ifndef SBROWSER2_TYPE_TRAITS_HPP
#define SBROWSER2_TYPE_TRAITS_HPP

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/number.hpp"
#include "ext/variant.hpp"

#include <functional>
#include <memory>
#include <type_traits>


// type definitions
using longlong  = long long;

using uchar     = unsigned char;
using ushort    = unsigned short;
using uint      = unsigned int;
using ulong     = unsigned long;
using ulonglong = unsigned long long;


// pointer deduction for raw and smart pointers together
namespace ext {template <typename _Tx> struct _unwrap_smart_pointer;}
namespace ext {template <typename _Tx> using unwrap_smart_pointer = _unwrap_smart_pointer<_Tx>;}
namespace ext {template <typename _Tx> using unwrap_smart_pointer_t = typename unwrap_smart_pointer<_Tx>::type;}

template <smart_pointer _Tx>
struct ext::_unwrap_smart_pointer<_Tx> {using type = typename _Tx::pointer;};

template <typename _Tx>
struct ext::_unwrap_smart_pointer {using type = _Tx;};


// extend variant with a new types
namespace ext {template <typename _Old, typename ..._New> struct _extend_variant;}
namespace ext {template <typename _Old, typename ..._New> using extend_variant = _extend_variant<_Old, _New...>;}
namespace ext {template <typename _Old, typename ..._New> using extend_variant_t = typename _extend_variant<_Old, _New...>::type;}

template <typename _Old, typename ..._New>
struct ext::_extend_variant {using type = _Old;};

template <typename ..._Old, typename ..._New>
struct ext::_extend_variant<ext::variant<_Old...>, _New...> {using type = ext::variant<_Old..., _New...>;};


// std::hash implementations
template <>
struct std::hash<ext::boolean>
{
    constexpr auto operator()(ext::boolean_view _Keyval) const noexcept -> size_t {return std::hash<bool>{}(_Keyval);}
};


template <typename T>
struct std::hash<ext::number<T>>
{
    constexpr auto operator()(ext::number_view<T> _Keyval) const noexcept -> size_t {return std::hash<T>{}(_Keyval);}
};


template <typename T>
struct std::hash<std::function<T>>
{
    constexpr auto operator()(std::function<T> _Keyval) const noexcept -> size_t {return std::hash<size_t>{}(&_Keyval);}
};


template <>
struct std::hash<ext::any>
{
    constexpr auto operator()(ext::any_view _Keyval) const noexcept -> size_t {return std::hash<size_t>{}(&_Keyval);}
};


#endif //SBROWSER2_TYPE_TRAITS_HPP
