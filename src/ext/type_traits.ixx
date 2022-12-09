module;
#include "ext/macros/namespaces.hpp"
#include <bit>
#include <string_view>
#include <type_traits>
#include <function2/function2.hpp>
#include <swl/variant.hpp>


export module ext.type_traits;

import ext.boolean;
import ext.concepts;
import ext.functional;
import ext.map;
import ext.number;
import ext.string;
import ext.span;
import ext.variant;


#define _DEFINE_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPES(_TemplateParameter_t, _Name, _DefaultType) \
    template <_TemplateParameter_t T>                                                                    \
    struct _Name {using type = _DefaultType;};                                                           \
                                                                                                         \
    template <_TemplateParameter_t T>                                                                    \
    using _Name##_t = typename _Name<T>::type

#define _ADD_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPE(_Name, _Specialization, _Ret_t) \
    template<>                                                                            \
    struct _Name<_Specialization> {using type = _Ret_t;}


_EXT_BEGIN
    // extend variant with a new types
    export template <typename OldType, typename ...NewTypes>
    struct extend_variant
    {using type = void;};

    export template <typename ...OldTypes, typename ...NewTypes>
    struct extend_variant<_EXT variant<OldTypes...>, NewTypes...>
    {using type = _EXT variant<OldTypes..., NewTypes...>;};

    export template <typename OldVariant, typename ...NewTypes>
    using extend_variant_t = typename extend_variant<OldVariant, NewTypes...>::type;


    // get the view of an object
    export template <typename T>
    struct view_of
    {using type = T;};

    export template <_EXT string_like T>
    struct view_of<T>
    {using type = std::basic_string_view<typename T::value_type, typename T::traits_type>;};

    export template <_EXT pure_iterable T>
    struct view_of<T>
    {using type = _EXT span<typename T::value_type, decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>;};

    // export template <_EXT type_is_any_specialization<_EXT function_base> T>
    // struct view_of<T>
    // {using type = _EXT function_view<>;};

    export template <typename T>
    using view_of_t = typename view_of<std::remove_cvref_t<T>>::type;


    // other
    template <typename T, typename F = std::less<T>>
    auto three_way_compare(T&& lhs, T&& rhs, F&& lt_predicate = std::less<T>{}) -> ext::boolean
    {return (lhs == rhs) ? 0 : lt_predicate(std::forward<T>(lhs), std::forward<T>(rhs)) ? -1 : 1;}
_EXT_END
