#pragma once
#ifndef SBROWSER2_SRC_EXT_QUEUE_HPP
#define SBROWSER2_SRC_EXT_QUEUE_HPP

#include "ext/view.hpp"
#include <concurrent_queue.h>


_EXT_BEGIN


using namespace Concurrency;

template <typename T>
using queue = concurrent_queue<T>;


#define queue_view_iterator typename queue<T>::iterator

// an `ext::queue_view<T>` is a view whose iterator is the iterator of an `ext::queue<T>` with template arguments. it
// differs from the base `ext::view<T>` because there is a custom constructor that converts the normal `ext::queue<T>`
// to the 'ext::queue_view<T>`
template <typename T>
struct queue_view : public view<queue_view_iterator>
{
    using view<queue_view_iterator>::view;

    explicit queue_view(queue<T>&& other)
            : view<queue_view_iterator>{std::move(other.unsafe_begin()), std::move(other.unsafe_end())}
    {}

    explicit queue_view(const queue<T>& other)
            : view<queue_view_iterator>{other.unsafe_begin(), other.unsafe_end()}
    {}
};


_EXT_END


#endif //SBROWSER2_SRC_EXT_QUEUE_HPP
