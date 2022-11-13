#pragma once
#ifndef SBROWSER2_VECTOR_HPP
#define SBROWSER2_VECTOR_HPP

#include "ext/allocator.hpp"
#include <veque.hpp>
#include <cryptopp/secblock.h>


_EXT_BEGIN
    template <typename T, typename Allocator = std::allocator<T>>
    using vector = veque::veque<T, veque::fast_resize_traits, Allocator>;
_EXT_END


_EXT_SECURE_BEGIN
    template <typename T>
    using vector = vector<T, _EXT secure::allocator<T>>;
_EXT_SECURE_END


#endif //SBROWSER2_VECTOR_HPP
