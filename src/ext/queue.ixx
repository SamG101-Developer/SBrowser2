module;
#include "ext/macros/namespaces.hpp"
#include <plf/plf_queue.h>


export module ext.queue;
import ext.allocator;
import ext.vector;


_EXT_BEGIN
    export template <typename T>
    using queue = plf::queue<T, plf::speed, _EXT allocator<T>>;
_EXT_END

_EXT_SECURE_BEGIN
    export template <typename T>
    using queue = plf::queue<T, plf::speed, _EXT secure::allocator<T>>;
_EXT_SECURE_END
