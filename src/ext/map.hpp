#pragma once
#ifndef SBROWSER2_MAP_HPP
#define SBROWSER2_MAP_HPP

#include "ext/keywords.hpp"
#include <tsl/robin_map.h>


_EXT_BEGIN

template <typename _Vt1, typename _Vt2>
using map = tsl::robin_map<_Vt1, _Vt2>;

template <typename _Vt1, typename _Vt2>
using map_view = const _EXT map<_Vt1, _Vt2>&;

_EXT_END


#endif //SBROWSER2_MAP_HPP
