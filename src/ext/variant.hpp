#ifndef SBROWSER2_SRC_EXT_VARIANT_HPP
#define SBROWSER2_SRC_EXT_VARIANT_HPP

#include "ext/keywords.hpp"
#include <swl/variant.hpp>


_EXT_BEGIN

using namespace swl;

template <typename ...Ts>
using variant_view = const variant<std::reference_wrapper<Ts>...>&;

template <typename T>
const std::type_info& variant_type(T&& variant_object)
{
    return std::visit([](auto&& _) -> decltype(auto) {return typeid(_);}, std::forward<T>(variant_object));
}

_EXT_END


#endif //SBROWSER2_SRC_EXT_VARIANT_HPP
