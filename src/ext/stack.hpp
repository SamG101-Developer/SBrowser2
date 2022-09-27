#pragma once
#ifndef SBROWSER2_SRC_EXT_STACK_HPP
#define SBROWSER2_SRC_EXT_STACK_HPP

#include "ext/vector.hpp"
#include "ext/view.hpp"
#include <iterator>
#include <plf_stack.h>


_EXT_BEGIN


template <typename T, typename C = typename vector<T>::allocator_type>
using stack = plf::stack<T, C>;

template <typename T>
using stack_view_iterator = typename stack<T>::pointer;


template <typename T>
struct stack_view : public view<stack_view_iterator<T>>
{
public constructors:
    using view<stack_view_iterator<T>>::view;

    explicit stack_view(stack<T>&& other)
            : view<stack_view_iterator<T>>{&std::make_move_iterator(&other.top()), other.size()}
    {}

    explicit stack_view(const stack<T>& other)
            : view<stack_view_iterator<T>>{&other.top(), other.size()}
    {}
};


_EXT_END


#endif //SBROWSER2_SRC_EXT_STACK_HPP
