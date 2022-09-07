#pragma once
#ifndef SBROWSER2_VECTOR_HPP
#define SBROWSER2_VECTOR_HPP

#include "ext/view.hpp"
#include <iterator>
#include <veque.hpp>


_EXT_BEGIN


template <typename T>
using vector = veque::veque<T>;

#define vector_view_iterator typename vector<T>::iterator


template <typename T>
struct vector_view : public view<vector_view_iterator>
{
public constructors:
    using view<vector_view_iterator>::view;

    explicit vector_view(vector<T>&& other)
            : view<vector_view_iterator>(std::make_move_iterator(other.begin()), std::make_move_iterator(other.end()))
    {}

    explicit vector_view(const vector<T>& other)
            : view<vector_view_iterator>{other.begin(), other.end()}
    {}
};


_EXT_END


#endif //SBROWSER2_VECTOR_HPP
