#pragma once
#ifndef SBROWSER2_SRC_EXT_STACK_HPP
#define SBROWSER2_SRC_EXT_STACK_HPP

#include "ext/keywords.hpp"
#include "ext/allocator.hpp"
#include <plf/plf_stack.h>


_EXT_BEGIN
    template <typename T, typename Allocator = _EXT allocator<T>>
    using stack = plf::stack<T, Allocator>;
_EXT_END


_EXT_SECURE_BEGIN
    template <typename T>
    using stack = plf::stack<T, _EXT secure::allocator<T>>;
_EXT_SECURE_END


#endif //SBROWSER2_SRC_EXT_STACK_HPP
