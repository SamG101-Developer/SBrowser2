#pragma once
#ifndef SBROWSER2_SRC_EXT_QUEUE_HPP
#define SBROWSER2_SRC_EXT_QUEUE_HPP

#include "ext/keywords.hpp"
#include "ext/allocator.hpp"
#include "ext/vector.hpp"
#include <plf/plf_queue.h>


_EXT_BEGIN
    template <typename T, typename Allocator = _EXT allocator<T>>
    using queue = plf::queue<T, plf::speed, Allocator>;
_EXT_END


_EXT_BEGIN
    template <size_t N, typename T>
    auto multi_peek(_EXT queue<T>& queue) -> _EXT vector<T>
    {
        auto v = _EXT vector<T>{};
        for (auto x = 0; x < N; ++x)
            v.template emplace_back(*(&queue.front() + x));
        return v;
    }
_EXT_END


_EXT_SECURE_BEGIN
    template <typename T>
    using queue = _EXT queue<T, _EXT secure::allocator<T>>;
_EXT_SECURE_END


#endif //SBROWSER2_SRC_EXT_QUEUE_HPP
