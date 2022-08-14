#pragma once
#ifndef SBROWSER2_MAP_HPP
#define SBROWSER2_MAP_HPP

#include "ext/view.hpp"
#include <tsl/robin_map.h>

#define map_view_iterator typename map<K, V>::iterator


_EXT_BEGIN

using namespace tsl;

template <typename K, typename V>
using map = tsl::robin_map<K, V>;


template <typename K, typename V>
class map_view : public view<map_view_iterator>
{
public constructors:
    using view<map_view_iterator>::view;

    explicit map_view(map<K, V>&& other)
            : view<map_view_iterator>{std::move(other.begin()), std::move(other.end())}
    {}

    explicit map_view(const map<K, V>& other)
            : view<map_view_iterator>{other.begin(), other.end()}
    {}
};

_EXT_END


#endif //SBROWSER2_MAP_HPP
