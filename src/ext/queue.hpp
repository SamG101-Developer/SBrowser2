#pragma once
#ifndef SBROWSER2_SRC_EXT_QUEUE_HPP
#define SBROWSER2_SRC_EXT_QUEUE_HPP

#include "ext/keywords.hpp"
#include "ext/allocator.hpp"
#include <plf/plf_queue.h>


_EXT_BEGIN
    template <typename T, typename Allocator = _EXT allocator<T>>
    using queue = plf::queue<T, plf::speed, Allocator>;
_EXT_END


_EXT_SECURE_BEGIN
    template <typename T>
    using queue = _EXT queue<T, ext::secure::allocator<T>>;
_EXT_SECURE_END


#endif //SBROWSER2_SRC_EXT_QUEUE_HPP
