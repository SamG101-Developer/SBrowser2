module;
#include "ext/macros/namespaces.hpp"
#include <bit>
#include <range/v3/range/concepts.hpp>
#include <type_traits>
#include <function2/function2.hpp>
#include <swl/variant.hpp>


export module ext.core:type_traits;

import :boolean;
import :concepts;
import :functional;
import :map;
import :number;
import :string;
import :span;
import :variant;


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
    // Extend variant with a new types
    export template <typename OldType, typename ...NewTypes>
    struct extend_variant
    {using type = void;};

    export template <typename ...OldTypes, typename ...NewTypes>
    struct extend_variant<_EXT variant<OldTypes...>, NewTypes...>
    {using type = _EXT variant<OldTypes..., NewTypes...>;};

    export template <typename OldVariant, typename ...NewTypes>
    using extend_variant_t = typename extend_variant<OldVariant, NewTypes...>::type;


    // Get the view of an object -- general (non-specialized) type returns the same type. TODO : const& for default?
    export template <typename T>
    struct view_of
    {using type = T;};

    // Convert a range-v3 view by keeping it the same (readonly)
    export template <ranges::view_ T>
    struct view_of<T>
    {using type = T;};

    // Convert a pure-iterable container (same iterator type for begin() amd end()) to its corresponding 'span<...>' type.
    export template <_EXT pure_iterable T>
    struct view_of<T>
    {using type = _EXT span<typename T::value_type>;};

    // Convert a 'string_like<T>' object to a 'string_view<...>' object of the same char-traits.
    export template <>
    struct view_of<ext::u8string>
    {using type = _EXT u8string_view;};

    // Convert a 'function<Ts...>' to a 'function_view<Ts...>'.
    export template <typename ...Ts>
    struct view_of<_EXT function<Ts...>>
    {using type = _EXT function_view<Ts...>;};

    // Convert a 'unique_function<Ts...>' to a 'function_view<Ts...>'.
    export template <typename ...Ts>
    struct view_of<_EXT unique_function<Ts...>>
    {using type = _EXT function_view<Ts...>;};

    // Typedef the type value of the 'view_of' struct.
    export template <typename T>
    using view_of_t = typename view_of<std::remove_cvref_t<T>>::type;


    // Other
    template <typename T, typename F = std::less<T>>
    auto three_way_compare(T&& lhs, T&& rhs, F&& lt_predicate = std::less<T>{}) -> ext::boolean
    {return (lhs == rhs) ? 0 : lt_predicate(std::forward<T>(lhs), std::forward<T>(rhs)) ? -1 : 1;}
_EXT_END
