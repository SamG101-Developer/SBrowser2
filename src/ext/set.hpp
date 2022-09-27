#pragma once
#ifndef SBROWSER2_SET_HPP
#define SBROWSER2_SET_HPP

#include "ext/view.hpp"
#include <iterator>
#include <tsl/robin_set.h>


_EXT_BEGIN


template <typename T>
using set = tsl::robin_set<T>;

template <typename T>
using set_view_iterator = typename set<T>::iterator;


template <typename T>
class set_view : public view<set_view_iterator<T>>
{
public constructors:
    using view<set_view_iterator<T>>::view;

    explicit set_view(set<T>&& other)
            : view<set_view_iterator<T>>{std::make_move_iterator(other.begin()), std::make_move_iterator(other.end())}
    {}

    explicit set_view(const set<T>& other)
            : view<set_view_iterator<T>>{other.begin(), other.end()}
    {}
};


_EXT_END


#endif //SBROWSER2_SET_HPP
