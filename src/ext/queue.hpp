#pragma once
#ifndef SBROWSER2_SRC_EXT_QUEUE_HPP
#define SBROWSER2_SRC_EXT_QUEUE_HPP

#include "ext/view.hpp"
#include <iterator>
#include <plf_queue.h>


_EXT_BEGIN


template <typename T>
using queue = plf::queue<T>;

#define queue_view_iterator typename queue<T>::iterator


template <typename T>
struct queue_view : public view<queue_view_iterator>
{
public constructors:
    using view<queue_view_iterator>::view;

    explicit queue_view(queue<T>&& other)
            : view<queue_view_iterator>{std::make_move_iterator(other.start_element), std::make_move_iterator(other.top_element + 1)}
    {}

    explicit queue_view(const queue<T>& other)
            : view<queue_view_iterator>{other.start_element, other.top_element + 1}
    {}
};


_EXT_END


#endif //SBROWSER2_SRC_EXT_QUEUE_HPP
