#ifndef SBROWSER2_SRC_EXT_VARIANT_HPP
#define SBROWSER2_SRC_EXT_VARIANT_HPP

#include "ext/keywords.hpp"
#include <swl/variant.hpp>


_EXT_BEGIN

template <typename ...Ts>
using variant = swl::variant<Ts...>;

template <typename ...Ts>
using variant_view = const variant<std::reference_wrapper<Ts>...>&;

_EXT_END


#endif //SBROWSER2_SRC_EXT_VARIANT_HPP
