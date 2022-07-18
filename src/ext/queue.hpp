#ifndef SBROWSER2_SRC_EXT_QUEUE_HPP
#define SBROWSER2_SRC_EXT_QUEUE_HPP

#include <concurrent_queue.h>

namespace ext {template <typename _Vt> using queue = Concurrency::concurrent_queue<_Vt>;}


#endif //SBROWSER2_SRC_EXT_QUEUE_HPP
