#pragma once
#ifndef SBROWSER2_MAP_HPP
#define SBROWSER2_MAP_HPP

#include "ext/view.hpp"
#include <tsl/robin_map.h>


_EXT_BEGIN

using namespace tsl;

template <typename _Vt0, typename _Vt1>
using map = tsl::robin_map<_Vt0, _Vt1>;


// an `ext::map_view<K, V>` is a view whose iterator is the iterator of an `ext::map<K, V>` with template arguments. it
// differs from the base `ext::view<T>` because there is a custom constructor that converts the normal `ext::map<K, V>`
// to the 'ext::map_view<K, V>`
template <typename _Vt0, typename _Vt1>
class map_view : public view<typename map<_Vt0, _Vt1>::iterator>
{
public constructors:
    using view<typename map<_Vt0, _Vt1>::iterator>::view;

    explicit map_view(const map<_Vt0, _Vt1>& other)
            : view<typename map<_Vt0, _Vt1>::iterator>{other.begin(), other.end()}
    {}
};

_EXT_END


#endif //SBROWSER2_MAP_HPP
