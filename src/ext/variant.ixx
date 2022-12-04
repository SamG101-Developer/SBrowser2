module;
#include "ext/macros/namespaces.hpp"
#include <swl/variant.hpp>

_EXT_BEGIN
    using namespace swl;
    using variant_monostate_t = swl::monostate;
_EXT_END


export module ext.variant;
import ext.concepts;
import ext.tuple;
import ext.vector;

_EXT_BEGIN
    template <typename ...Types>
    struct variant_to_tuple
    {using type = void;};

    template <typename ...Types>
    struct variant_to_tuple<_EXT variant<Types...>>
    {using type = _EXT tuple<Types...>;};

    template <typename T>
    using variant_to_tuple_t = typename variant_to_tuple<T>::type;
_EXT_END

_EXT_BEGIN
    template <typename T, _EXT callable F, typename ...Types>
    auto get_and(ext::variant<Types...> variant, F&& function)
    {return ext::holds_alternative<T>(variant) && function(variant);}

    template <typename T, typename ...Types>
    auto get_and_equals(ext::variant<Types...> variant, T&& value)
    {return ext::holds_alternative<T>(variant) && ext::unsafe_get<T>(variant) == std::forward<T>(value);}
_EXT_END
