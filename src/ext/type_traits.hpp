#pragma once
#ifndef SBROWSER2_TYPE_TRAITS_HPP
#define SBROWSER2_TYPE_TRAITS_HPP

#include <functional>
#include <memory>
#include <type_traits>
#include <ext/boolean.hpp>

#include <range/v3/range/concepts.hpp>


// type definitions
using longlong  = long long;

using uchar     = unsigned char;
using ushort    = unsigned short;
using uint      = unsigned int;
using ulong     = unsigned long;
using ulonglong = unsigned long long;


// check if a mixin is a base class of a type ie is any templated version of ext::number the inherited into a class etc TODO : switch params ie should be ...<BaseMixin, DerivedClass>
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
namespace ext {template <typename _Tx> using is_smart_pointer = _is_smart_pointer<std::remove_cvref_t<_Tx>>;}
namespace ext {template <typename _Tx> constexpr bool is_smart_pointer_v = is_smart_pointer<_Tx>::value;}

template <typename _Tx>
struct ext::_is_smart_pointer : public std::false_type{};

template <typename _Tx>
struct ext::_is_smart_pointer<std::shared_ptr<_Tx>> : std::true_type{};

template <typename _Tx>
struct ext::_is_smart_pointer<std::unique_ptr<_Tx>> : std::true_type{};


// pointer deduction for raw and smart pointers together
namespace ext {template <typename _Tx> struct _unwrap_smart_pointer;}
namespace ext {template <typename _Vt> using unwrap_smart_pointer = _unwrap_smart_pointer<std::remove_cvref_t<_Vt>>;}
namespace ext {template <typename _Vt> using unwrap_smart_pointer_t = typename unwrap_smart_pointer<_Vt>::type;}

template <typename _Tx> requires (ext::is_smart_pointer_v<_Tx>)
struct ext::_unwrap_smart_pointer<_Tx> {using type = typename _Tx::pointer;};

template <typename _Tx> requires (!ext::is_smart_pointer_v<_Tx>)
struct ext::_unwrap_smart_pointer<_Tx> {using type = _Tx;};


//
namespace ext {template <typename _Base, typename _Derived> using is_dynamically_castable_to = std::is_base_of<std::remove_pointer_t<_Base>, std::remove_pointer_t<_Derived>>;}
namespace ext {template <typename _Base, typename _Derived> constexpr bool is_dynamically_castable_to_v = is_dynamically_castable_to<_Base, _Derived>::value;}



// equality checks
template <typename _Fx>
auto operator==(const _Fx& _FunctionA, const _Fx& _FunctionB) requires std::is_invocable_v<_Fx> {return &_FunctionA == &_FunctionB;}


// TODO : temporary for ranges v3 until i can get their concepts working
template <typename T>
concept range_v3_view = requires(const T& range)
{
    {ranges::view_<T>};
};





#endif //SBROWSER2_TYPE_TRAITS_HPP
