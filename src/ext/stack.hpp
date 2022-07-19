#ifndef SBROWSER2_SRC_EXT_STACK_HPP
#define SBROWSER2_SRC_EXT_STACK_HPP

#include "ext/keywords.hpp"
#include <plf_stack.h>


_EXT_BEGIN

template <typename _Vt>
using stack = plf::stack<_Vt>;

_EXT_END


#endif //SBROWSER2_SRC_EXT_STACK_HPP
