#pragma once
#ifndef SBROWSER2_TYPE_TRAITS_HPP
#define SBROWSER2_TYPE_TRAITS_HPP

#include <functional>
#include <memory>
#include <type_traits>

#include <ext/boolean.hpp>
#include <ext/concepts.hpp>


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


#endif //SBROWSER2_TYPE_TRAITS_HPP
