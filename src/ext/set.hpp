#pragma once
#ifndef SBROWSER2_SET_HPP
#define SBROWSER2_SET_HPP

#include "ext/view.hpp"
#include <tsl/robin_set.h>


_EXT_BEGIN

template <typename _Vt>
using set = tsl::robin_set<_Vt>;


// an `ext::set_view<T>` is a view whose iterator is the iterator of an `ext::set<T>` with template arguments. it
// differs from the base `ext::view<T>` because there is a custom constructor that converts the normal `ext::set<T>` to
// the 'ext::set_view<T>`
template <typename _Tx>
class set_view : public view<typename set<_Tx>::iterator>
{
    using view<typename set<_Tx>::iterator>::view;

    explicit set_view(const set<_Tx>& other)
            : view<typename set<_Tx>::iterator>{other.begin(), other.end()}
    {}
};


_EXT_END


#endif //SBROWSER2_SET_HPP
