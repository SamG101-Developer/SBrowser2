module;
#include "ext/macros/namespaces.hpp"
#include <plf/plf_stack.h>


export module ext.core:stack;
import :allocator;


_EXT_BEGIN
    export template <typename T>
    using stack = plf::stack<T, _EXT allocator<T>>;
_EXT_END

_EXT_SECURE_BEGIN
    export template <typename T>
    using stack = plf::stack<T, _EXT secure::allocator<T>>;
_EXT_SECURE_END
