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


// check if a templated class is a base of another class (don't need template type to check)
template <template <typename> typename _Base, typename _Derived>
concept templated_base_of = requires(_Derived _Obj)
{
    []<typename _Ty>(const _Base<_Ty>&){}(_Obj);
};


// check if a type is iterable ie does it have .begin() and .end() iterator access
template <typename _Tx>
concept iterable = requires (_Tx _Obj)
{
    _Obj.begin(); _Obj.end();
};


// check if a type is a smart pointer
template <typename _Tx>
concept smart_pointer = requires (_Tx _Obj)
{
    _Obj.get() == &*_Obj;
};


// check if a pointer can be dynamically cast to another pointer
template <typename _Tx, typename _Tx1>
concept dynamically_castable_to = requires (_Tx _PtrL)
{
    dynamic_cast<_Tx1>(_PtrL);
};


// check if a type is a range_v3 type
template <typename T>
concept range_v3_view = requires(const T& range)
{
    ranges::view_<T>;
};


// check if a type is one of many
template <typename ..._Valty, typename _Tx>
concept same_as_any = requires(_Valty... _Val)
{
    (std::same_as<_Tx, _Valty> || ...);
};


// check if a type is a primitive numeric type
template <typename T>
concept primitive_numeric = requires(T)
{
    std::integral<T> || std::floating_point<T>;
};


// pointer deduction for raw and smart pointers together
namespace ext {template <typename _Tx> struct _unwrap_smart_pointer;}
namespace ext {template <typename _Tx> using unwrap_smart_pointer = _unwrap_smart_pointer<_Tx>;}
namespace ext {template <typename _Tx> using unwrap_smart_pointer_t = typename unwrap_smart_pointer<_Tx>::type;}

template <smart_pointer _Tx>
struct ext::_unwrap_smart_pointer<_Tx> {using type = typename _Tx::pointer;};

template <typename _Tx>
struct ext::_unwrap_smart_pointer {using type = _Tx;};


#endif //SBROWSER2_TYPE_TRAITS_HPP
