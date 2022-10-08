#pragma once
#ifndef SBROWSER2_SET_HPP
#define SBROWSER2_SET_HPP

#include "ext/vector.hpp"
#include <ankerl/unordered_dense.h>


_EXT_BEGIN

template <typename T>
using set = ankerl::unordered_dense::set<T, ankerl::unordered_dense::hash<T>, std::equal_to<T>, _EXT vector<T>>;

_EXT_END


#endif //SBROWSER2_SET_HPP
