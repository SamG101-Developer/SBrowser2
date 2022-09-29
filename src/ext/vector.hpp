#pragma once
#ifndef SBROWSER2_VECTOR_HPP
#define SBROWSER2_VECTOR_HPP

#include "ext/keywords.hpp"
#include <veque.hpp>


_EXT_BEGIN

template <typename T, typename ResizeTraits, typename Allocator>
using vector = veque::veque<T, ResizeTraits, Allocator>;

_EXT_END


#endif //SBROWSER2_VECTOR_HPP
