#pragma once
#ifndef SBROWSER2_SRC_EXT_QUEUE_HPP
#define SBROWSER2_SRC_EXT_QUEUE_HPP

#include "ext/view.hpp"
#include <concurrent_queue.h>


_EXT_BEGIN


using namespace Concurrency;

template <typename _Vt>
using queue = concurrent_queue<_Vt>;


// an `ext::queue_view<T>` is a view whose iterator is the iterator of an `ext::queue<T>` with template arguments. it
// differs from the base `ext::view<T>` because there is a custom constructor that converts the normal `ext::queue<T>`
// to the 'ext::queue_view<T>`
template <typename _Tx>
struct queue_view : public view<typename queue<_Tx>::iterator>
{
    using view<typename queue<_Tx>::iterator>::view;

    explicit queue_view(const queue<_Tx>& other)
            : view<typename queue<_Tx>::iterator>{other.unsafe_begin(), other.unsafe_end()}
    {}
};


_EXT_END


#endif //SBROWSER2_SRC_EXT_QUEUE_HPP
