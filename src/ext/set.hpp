#pragma once
#ifndef SBROWSER2_SET_HPP
#define SBROWSER2_SET_HPP

#include "ext/keywords.hpp"
#include <tsl/robin_set.h>


_EXT_BEGIN

template <typename _Vt>
using set = tsl::robin_set<_Vt>;

template <typename _Tx>
using set_view = const _EXT set<_Tx>&;

_EXT_END


#endif //SBROWSER2_SET_HPP
