#pragma once
#ifndef SBROWSER2_SRC_EXT_QUEUE_HPP
#define SBROWSER2_SRC_EXT_QUEUE_HPP

#include "ext/keywords.hpp"
#include <plf/plf_queue.h>


_EXT_BEGIN

template <typename T>
using queue = plf::queue<T, plf::speed>;

_EXT_END


#endif //SBROWSER2_SRC_EXT_QUEUE_HPP
