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
#include "ext/variant.hpp"

#include <memory>
#include <type_traits>


// TODO : Don't even remember what these macros do
#define DEFINE_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPES(_TemplateParameter_t, _Name, _DefaultType) \
    template <_TemplateParameter_t T>                                                                   \
    struct _Name {using type = _DefaultType;};                                                          \
                                                                                                        \
    template <_TemplateParameter_t T>                                                                   \
    using _Name##_t = typename _Name<T>::type

#define ADD_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPE(_Name, _Specialization, _Ret_t) \
    template<>                                                                           \
    struct _Name<_Specialization> {using type = _Ret_t;}


_EXT_BEGIN

// extend variant with a new types
template <typename OldType, typename ...NewTypes>
struct extend_variant
{using type = void;};

template <typename ...OldTypes, typename ...NewTypes>
struct extend_variant<variant<OldTypes...>, NewTypes...>
{using type = variant<OldTypes..., NewTypes...>;};

template <typename OldVariant, typename ...NewTypes>
using extend_variant_t = typename extend_variant<OldVariant, NewTypes...>::type;


// more elegant decltype
template <typename T>
struct typeof
{using type = std::remove_cvref_t<std::remove_pointer_t<T>>;};

template <typename T>
using typeof_t = typename typeof<T>::type;

// other

template <typename T, typename F = std::less<T>>
auto three_way_compare(T&& lhs, T&& rhs, F&& lt_predicate = std::less<T>{}) -> ext::boolean
{
    if (lhs == rhs) return 0;
    return lt_predicate(std::forward<T>(lhs), std::forward<T>(rhs)) ? -1 : 1;
}

_EXT_END


#endif //SBROWSER2_TYPE_TRAITS_HPP
