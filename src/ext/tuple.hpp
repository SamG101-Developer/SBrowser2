#ifndef SBROWSER2_SRC_EXT_TUPLE_HPP
#define SBROWSER2_SRC_EXT_TUPLE_HPP

#include "ext/keywords.hpp"
#include <tuplet/tuple.hpp>


_EXT_BEGIN

template <typename ..._Valty>
using tuple = tuplet::tuple<_Valty...>;

template <typename ..._Valty>
using tuple_view = const _EXT tuple<_Valty...>&;

_EXT_END


#endif //SBROWSER2_SRC_EXT_TUPLE_HPP
