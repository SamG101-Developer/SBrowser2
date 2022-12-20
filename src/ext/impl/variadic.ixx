module;
#include "ext/macros/namespaces.hpp"
#include <utility>


export module ext.core:variadic;
import :tuple;

_EXT_DETAIL_BEGIN
    export template <signed Adjust, std::size_t... I, typename... T>
    auto nth_variadic_values(std::index_sequence<I...>, T&&... t)
    {return ext::make_tuple(ext::get<I + Adjust>(ext::make_tuple(std::forward<T>(t)...))...);}
_EXT_DETAIL_END


_EXT_BEGIN
    // Get the single Nth element from a variadic argument
    export template <size_t N, typename ...Args>
    auto nth_variadic_value(Args&&... args)
    {return _EXT get<N>(_EXT make_tuple<Args...>(std::forward<Args>(args)...));}

    // Get the Nth elements (I amount) from a variadic argument
    export template <signed Begin, signed Size, typename... T>
    auto nth_variadic_values(T&&... t)
    {return detail::nth_variadic_values<Begin>(std::make_index_sequence<(Size)>(), std::forward<T>(t)...);}

    export template <signed Begin, typename... T>
    auto nth_variadic_values(T&&... t)
    {return detail::nth_variadic_values<Begin>(std::make_index_sequence<(sizeof...(T) - Begin)>(), std::forward<T>(t)...);}

    // Get the single Nth type from a variadic argument
    export template <size_t Index, typename ...Types>
    struct nth_variadic_type
    {using type = decltype(_EXT get<Index>(std::declval<_EXT tuple<Types...>>()));};

    export template <size_t Index, typename ...Types>
    using nth_variadic_type_t = typename nth_variadic_type<Index, Types...>::type;
_EXT_END
