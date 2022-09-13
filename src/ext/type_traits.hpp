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


// pointer deduction for raw and smart pointers together

_EXT_BEGIN

template <typename T>
struct _unwrap_smart_pointer;

template <smart_pointer T>
struct _unwrap_smart_pointer<T>
{using type = typename T::pointer;};

template <typename T>
struct _unwrap_smart_pointer
{using type = T;};

template <typename T>
using unwrap_smart_pointer = _unwrap_smart_pointer<std::remove_cvref_t<T>>;

template <typename T>
using unwrap_smart_pointer_t = typename unwrap_smart_pointer<T>::type;


// extend variant with a new types
template <typename Old, typename ...New>
struct _extend_variant;

template <typename Old, typename ...New>
struct _extend_variant
{using type = Old;};

template <typename ...Old, typename ...New>
struct _extend_variant<variant<Old...>, New...>
{using type = variant<Old..., New...>;};

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


#endif //SBROWSER2_TYPE_TRAITS_HPP
