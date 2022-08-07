#pragma once
#ifndef SBROWSER2_VECTOR_HPP
#define SBROWSER2_VECTOR_HPP

#include <veque.hpp>
#include "ext/view.hpp"


_EXT_BEGIN

template <typename _Vt>
using vector = veque::veque<_Vt>;

template <typename T>
struct vector_view : public view<T>
{
    using view<typename vector<T>::iterator>::view;

    explicit vector_view(const vector<T>& other)
            : view<typename vector<T>::iterator>{&other.begin(), other.end()}
    {}
};

_EXT_END


#endif //SBROWSER2_VECTOR_HPP
