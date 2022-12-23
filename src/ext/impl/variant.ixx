module;
#include "ext/macros/namespaces.hpp"
#include <utility>


export module ext.core:variant;
import :concepts;
import :tuple;
import :vector;

#include <swl/variant.hpp>


_EXT_BEGIN
    export using namespace ::swl;
    export using variant_monostate_t = swl::monostate;

    export template <typename ...Ts, typename T>
    auto operator==(_EXT variant<Ts...>& v, T&& t)
    {return _EXT holds_alternative<T>(v) && _EXT unsafe_get<T>(v) == std::forward<T>(t);}

    export template <typename ...Ts, typename T>
    auto operator!=(_EXT variant<Ts...>& v, T&& t)
    {return !_EXT holds_alternative<T>(v) || _EXT holds_alternative<T>(v) && _EXT unsafe_get<T>(v) != std::forward<T>(t);}
_EXT_END

_EXT_BEGIN
    export template <typename ...Types>
    struct variant_to_tuple
    {using type = void;};

    export template <typename ...Types>
    struct variant_to_tuple<_EXT variant<Types...>>
    {using type = _EXT tuple<Types...>;};

    export template <typename T>
    using variant_to_tuple_t = typename variant_to_tuple<T>::type;
_EXT_END

_EXT_BEGIN
    export template <typename T, _EXT callable F, typename ...Types>
    auto get_and(ext::variant<Types...> variant, F&& function)
    {return ext::holds_alternative<T>(variant) && function(variant);}

    export template <typename T, typename ...Types>
    auto get_and_equals(ext::variant<Types...> variant, T&& value)
    {return ext::holds_alternative<T>(variant) && ext::unsafe_get<T>(variant) == std::forward<T>(value);}
_EXT_END
