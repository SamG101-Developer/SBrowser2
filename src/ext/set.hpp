#pragma once
#ifndef SBROWSER2_SET_HPP
#define SBROWSER2_SET_HPP

#include "ext/view.hpp"
#include <tsl/robin_set.h>


_EXT_BEGIN

template <typename T>
using set = tsl::robin_set<T>;


#define set_view_iterator typename set<T>::iterator

// an `ext::set_view<T>` is a view whose iterator is the iterator of an `ext::set<T>` with template arguments. it
// differs from the base `ext::view<T>` because there is a custom constructor that converts the normal `ext::set<T>` to
// the 'ext::set_view<T>`
template <typename T>
class set_view : public view<set_view_iterator>
{
    using view<set_view_iterator>::view;

    explicit set_view(set<T>&& other)
            : view<set_view_iterator>{std::move(other.begin()), std::move(other.end())}
    {}

    explicit set_view(const set<T>& other)
            : view<set_view_iterator>{other.begin(), other.end()}
    {}
};


_EXT_END


#endif //SBROWSER2_SET_HPP
