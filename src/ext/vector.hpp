#pragma once
#ifndef SBROWSER2_VECTOR_HPP
#define SBROWSER2_VECTOR_HPP

#include "ext/allocator.hpp"
#include <veque.hpp>


_EXT_BEGIN
    template <typename T>
    using vector = veque::veque<T, veque::fast_resize_traits, _EXT allocator<T>>;

    template <typename T>
    using frozen_vector = const vector<T>;
_EXT_END


_EXT_SECURE_BEGIN
    template <typename T>
    using vector = veque::veque<T, veque::fast_resize_traits, _EXT secure::allocator<T>>;

    template <typename T>
    using frozen_vector = const vector<T>;
_EXT_SECURE_END


#endif //SBROWSER2_VECTOR_HPP
