#pragma once
#ifndef SBROWSER2_PAIR_HPP
#define SBROWSER2_PAIR_HPP

#include "ext/keywords.hpp"
#include <tuplet/tuple.hpp>


_EXT_BEGIN

template <typename _Vt0, typename _Vt1>
using pair = tuplet::pair<_Vt0, _Vt1>;

template <typename _Vt0, typename _Vt1>
using pair_view = const _EXT pair<_Vt0, _Vt1>&;

_EXT_END


#endif //SBROWSER2_PAIR_HPP
