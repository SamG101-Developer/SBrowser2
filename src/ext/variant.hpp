#ifndef SBROWSER2_SRC_EXT_VARIANT_HPP
#define SBROWSER2_SRC_EXT_VARIANT_HPP

#include "ext/keywords.hpp"
#include <swl/variant.hpp>


_EXT_BEGIN

template <typename ..._Valty>
using variant = swl::variant<_Valty...>;

template <typename ..._Valty>
using variant_view = const variant<_Valty...>&;

_EXT_END


#endif //SBROWSER2_SRC_EXT_VARIANT_HPP
