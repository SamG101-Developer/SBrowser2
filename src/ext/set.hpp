#pragma once
#ifndef SBROWSER2_SET_HPP
#define SBROWSER2_SET_HPP

#include "ext/keywords.hpp"
#include <tsl/robin_set.h>


_EXT_BEGIN

template <
        class Key, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>,
        class Allocator = std::allocator<Key>, bool StoreHash = false,
        class GrowthPolicy = tsl::rh::power_of_two_growth_policy<2>>
using set = tsl::robin_set<Key, Hash, KeyEqual, Allocator, StoreHash, GrowthPolicy>;

_EXT_END


#endif //SBROWSER2_SET_HPP
