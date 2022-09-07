#pragma once
#ifndef SBROWSER2_MAP_HPP
#define SBROWSER2_MAP_HPP

#include "ext/view.hpp"
#include <iterator>
#include <tsl/robin_map.h>


_EXT_BEGIN


template <typename K, typename V>
using map = tsl::robin_map<K, V>;

#define map_view_iterator typename map<K, V>::iterator


template <typename K, typename V>
class map_view : public view<map_view_iterator>
{
public constructors:
    using view<map_view_iterator>::view;

    explicit map_view(map<K, V>&& other)
            : view<map_view_iterator>{std::make_move_iterator(other.begin()), std::make_move_iterator(other.end())}
    {}

    explicit map_view(const map<K, V>& other)
            : view<map_view_iterator>{other.begin(), other.end()}
    {}
};


_EXT_END


#endif //SBROWSER2_MAP_HPP
