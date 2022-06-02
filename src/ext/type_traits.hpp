#pragma once
#ifndef SBROWSER2_TYPE_TRAITS_HPP
#define SBROWSER2_TYPE_TRAITS_HPP

#include <type_traits>
#include <ext/boolean.hpp>
#include <ext/shared_pointer.hpp>


// type definitions
using uchar     = unsigned char;
using ushort    = unsigned short;
using uint      = unsigned int;
using ulong     = unsigned long;
using ulonglong = unsigned long long;


// check if a mixin is a base class of a type ie is any templated version of ext::number the inherited into a class etc
namespace ext {template <typename _Tx1, template <typename, typename...> typename _Tx2> struct _is_template_base_of;}
namespace ext {template <typename _Tx1, template <typename, typename...> typename _Tx2> using is_template_base_of = _is_template_base_of<std::remove_cvref_t<_Tx1>, _Tx2>;}
namespace ext {template <typename _Tx1, template <typename, typename...> typename _Tx2> constexpr bool is_template_base_of_v = is_template_base_of<_Tx1, _Tx2>::value;}

template <typename _Tx1, template <typename, typename...> typename _Tx2>
struct ext::_is_template_base_of final : public std::false_type{};

template <typename _Tx1, template <typename, typename...> typename _Tx2>
struct ext::_is_template_base_of<_Tx2<_Tx1>, _Tx2> final : public std::true_type{};


// check if a type is iterable ie does it have .begin() and .end() iterator access
namespace ext {template <typename _Tx, typename = void> struct _is_iterable;}
namespace ext {template <typename _Tx> using is_iterable = _is_iterable<std::remove_cvref_t<_Tx>>;}
namespace ext {template <typename _Tx> constexpr bool is_iterable_v = is_iterable<_Tx>::value;}

template <typename _Tx, typename>
struct ext::_is_iterable : public std::false_type{};

template <typename _Tx>
struct ext::_is_iterable<_Tx, std::void_t<decltype(std::begin(std::declval<_Tx>())), decltype(std::begin(std::declval<_Tx>()))>> : std::true_type{};


// check if a type is a smart pointer
namespace ext {template <typename _Tx> struct _is_smart_pointer;}
namespace ext {template <typename _Tx> using is_smart_pointer = _is_smart_pointer<_Tx>;}
namespace ext {template <typename _Tx> constexpr bool is_smart_pointer_v = _is_smart_pointer<_Tx>::value;}

template <typename _Tx>
struct ext::_is_smart_pointer : public std::false_type{};

template <typename _Tx>
struct ext::_is_smart_pointer<ext::shared_pointer<_Tx>> : std::true_type{};


#endif //SBROWSER2_TYPE_TRAITS_HPP
