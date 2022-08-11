#pragma once
#ifndef SBROWSER2_VECTOR_HPP
#define SBROWSER2_VECTOR_HPP

#include <veque.hpp>
#include "ext/view.hpp"

#define vector_view_iterator typename vector<T>::iterator


_EXT_BEGIN

template <typename T>
using vector = veque::veque<T>;

// an `ext::vector_view<T>` is a view whose iterator is the iterator of an `ext::vector<T>` with template arguments. it
// differs from the base `ext::view<T>` because there is a custom constructor that converts the normal `ext::vector<T>`
// to the 'ext::vector_view<T>`
template <typename T>
struct vector_view : public view<vector_view_iterator>
{
    using view<vector_view_iterator>::view;

    vector_view(vector<T>&& other)
            : view<vector_view_iterator>(std::move(other.begin()), std::move(other.end()))
    {}

    vector_view(const vector<T>& other)
            : view<vector_view_iterator>{other.begin(), other.end()}
    {}
};

_EXT_END


#endif //SBROWSER2_VECTOR_HPP
