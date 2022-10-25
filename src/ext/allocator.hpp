#pragma once
#ifndef SBROWSER2_SRC_EXT_ALLOCATOR_HPP
#define SBROWSER2_SRC_EXT_ALLOCATOR_HPP

#include "ext/keywords.hpp"
#include <xmemory>
#include <cryptopp/secblock.h>


_EXT_BEGIN
    template <typename T>
    using allocator = std::allocator<T>;
_EXT_END


_EXT_SECURE_BEGIN
    template <typename T, bool A = false>
    using allocator = CryptoPP::AllocatorWithCleanup<T, A>;
_EXT_SECURE_END


#endif //SBROWSER2_SRC_EXT_ALLOCATOR_HPP
