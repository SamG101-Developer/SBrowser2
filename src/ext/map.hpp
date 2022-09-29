#pragma once
#ifndef SBROWSER2_MAP_HPP
#define SBROWSER2_MAP_HPP

#include "ext/keywords.hpp"
#include <tsl/robin_map.h>


_EXT_BEGIN

template <
        class Key, class T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>,
        class Allocator = std::allocator<std::pair<Key, T>>, bool StoreHash = false,
        class GrowthPolicy = tsl::rh::power_of_two_growth_policy<2>>
using map = tsl::robin_map<Key, T, Hash, KeyEqual, Allocator, StoreHash, GrowthPolicy>;

_EXT_END


#endif //SBROWSER2_MAP_HPP
