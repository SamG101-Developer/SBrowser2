#pragma once
#ifndef SBROWSER2_TYPE_TRAITS_HPP
#define SBROWSER2_TYPE_TRAITS_HPP

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/keywords.hpp"
#include "ext/number.hpp"
#include "ext/variant.hpp"

#include <functional>
#include <memory>
#include <type_traits>


#define COMMA ,


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

template <typename _Tx>
struct _unwrap_smart_pointer;

template <smart_pointer _Tx>
struct _unwrap_smart_pointer<_Tx> {using type = typename _Tx::pointer;};

template <typename _Tx>
struct _unwrap_smart_pointer {using type = _Tx;};

template <typename _Tx>
using unwrap_smart_pointer = _unwrap_smart_pointer<_Tx>;

template <typename _Tx>
using unwrap_smart_pointer_t = typename unwrap_smart_pointer<_Tx>::type;


// extend variant with a new types
template <typename _Old, typename ..._New>
struct _extend_variant;

template <typename _Old, typename ..._New>
struct _extend_variant {using type = _Old;};

template <typename ..._Old, typename ..._New>
struct _extend_variant<_EXT variant<_Old...>, _New...> {using type = _EXT variant<_Old..., _New...>;};

template <typename _Old, typename ..._New>
using extend_variant = _extend_variant<_Old, _New...>;

template <typename _Old, typename ..._New>
using extend_variant_t = typename _extend_variant<_Old, _New...>::type;

_EXT_END


// std::hash implementations

_STD_BEGIN

template <>
struct hash<_EXT boolean>
{
    constexpr auto operator()(_EXT boolean_view _Keyval) const noexcept -> size_t {return _STD hash<bool>{}(_Keyval);}
};


template <typename T>
struct hash<_EXT number<T>>
{
    constexpr auto operator()(_EXT number_view<T> _Keyval) const noexcept -> size_t {return _STD hash<T>{}(_Keyval);}
};


template <typename T>
struct hash<std::function<T>> // TODO -> ext::function<T...> once its ready for implementation
{
    constexpr auto operator()(std::function<T> _Keyval) const noexcept -> size_t {return _STD hash<size_t>{}(&_Keyval);}
};


template <>
struct hash<_EXT any>
{
    constexpr auto operator()(_EXT any_view _Keyval) const noexcept -> size_t {return _STD hash<size_t>{}(&_Keyval);}
};

_STD_END


#endif //SBROWSER2_TYPE_TRAITS_HPP
