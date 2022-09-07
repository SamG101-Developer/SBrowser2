#pragma once
#ifndef SBROWSER2_SRC_EXT_ARRAY_HPP
#define SBROWSER2_SRC_EXT_ARRAY_HPP

#include "ext/view.hpp"
#include <array>
#include <iterator>


_EXT_BEGIN


template <typename T, size_t N>
using array = std::array<T, N>;

#define array_view_iterator typename array<T, N>::iterator


template <typename T, size_t N>
struct array_view : public view<array_view_iterator>
{
public constructors:
    using view<array_view_iterator>::view;

    explicit array_view(array<T, N>&& other)
            : view<array_view_iterator>{std::make_move_iterator(other.begin()), std::make_move_iterator(other.end())}
    {}

    explicit array_view(const array<T, N>& other)
            : view<array_view_iterator>{other.begin(), other.end()}
    {}
};



_EXT_END

#endif //SBROWSER2_SRC_EXT_ARRAY_HPP
