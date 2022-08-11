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

/**
 * An `ext::map_view<K, V>` is a view whose iterator is the iterator of an `ext::map<K, V>` with template arguments. It
 * differs from the base `ext::view<T>` because there is a custom constructor that converts the normal `ext::map<K, V>`
 * to the 'ext::map_view<K, V>`.
 * @tparam K The type that the keys of the map are
 * @tparam V The type that the vals of the map are
 */
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
