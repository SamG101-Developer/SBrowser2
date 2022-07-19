#pragma once
#ifndef SBROWSER2_SRC_EXT_QUEUE_HPP
#define SBROWSER2_SRC_EXT_QUEUE_HPP

#include "ext/keywords.hpp"
#include <concurrent_queue.h>


_EXT_BEGIN

template <typename _Vt>
using queue = Concurrency::concurrent_queue<_Vt>;

template <typename _Vt>
using queue_view = const _EXT queue<_Vt>&;

_EXT_END


#endif //SBROWSER2_SRC_EXT_QUEUE_HPP
