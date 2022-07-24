#pragma once
#ifndef SBROWSER2_MAP_HPP
#define SBROWSER2_MAP_HPP

#include "ext/keywords.hpp"
#include "ext/pair.hpp"
#include <tsl/robin_map.h>


_EXT_BEGIN

template <typename _Vt0, typename _Vt1>
using map = tsl::robin_map<_Vt0, _Vt1, std::hash<_Vt0>, std::equal_to<_Vt0>, std::allocator<ext::pair<_Vt0, _Vt1>>>;

template <typename _Vt0, typename _Vt1>
using map_view = const _EXT map<_Vt0, _Vt1>&;

_EXT_END


#endif //SBROWSER2_MAP_HPP
