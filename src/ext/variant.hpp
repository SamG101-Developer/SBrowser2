#ifndef SBROWSER2_SRC_EXT_VARIANT_HPP
#define SBROWSER2_SRC_EXT_VARIANT_HPP

#include "ext/vector.hpp"
#include "ext/tuple.hpp"
#include <swl/variant.hpp>


_EXT_BEGIN

using namespace swl;
using variant_monostate_t = swl::monostate;


template <typename T>
const std::type_info& variant_type(T&& variant_object)
{
    return ext::visit([](auto&& _) -> decltype(auto) {return typeid(_);}, std::forward<T>(variant_object));
}


template <typename ...Types>
struct variant_to_tuple
{using type = void;};

template <typename ...Types>
struct variant_to_tuple<_EXT variant<Types...>>
{using type = _EXT tuple<Types...>;};

template <typename T>
using variant_to_tuple_t = typename variant_to_tuple<T>::type;

template <typename T, typename F, typename ...Types>
auto get_and(ext::variant<Types...> variant, F&& function)
{
    return ext::holds_alternative<T>(variant) && function(variant);
}

_EXT_END


#endif //SBROWSER2_SRC_EXT_VARIANT_HPP
