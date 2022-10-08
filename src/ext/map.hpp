#pragma once
#ifndef SBROWSER2_MAP_HPP
#define SBROWSER2_MAP_HPP

#include "ext/vector.hpp"
#include "ext/pair.hpp"
#include <ankerl/unordered_dense.h>


_EXT_BEGIN

template <typename Key, typename Val>
using map = ankerl::unordered_dense::map<Key, Val, ankerl::unordered_dense::hash<Key>, std::equal_to<Key>, _EXT vector<_EXT pair<Key, Val>>>;

_EXT_END


#endif //SBROWSER2_MAP_HPP
