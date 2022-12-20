module;
#include "ext/macros/namespaces.hpp"
#include <xmemory>


export module ext.core:allocator;
#include <cryptopp/secblock.h>


_EXT_BEGIN
    export template <typename T>
    using allocator = std::allocator<T>;
_EXT_END


_EXT_SECURE_BEGIN
    export template <typename T, bool A = false>
    using allocator = CryptoPP::AllocatorWithCleanup<T, A>;
_EXT_SECURE_END
