module;
#include "ext/macros/namespaces.hpp"
#include <xmemory>
#include <cryptopp/secblock.h>


export module ext.allocator;

_EXT_BEGIN
    export template <typename T>
    using allocator = std::allocator<T>;
_EXT_END


_EXT_SECURE_BEGIN
    export template <typename T, bool A = false>
    using allocator = CryptoPP::AllocatorWithCleanup<T, A>;
_EXT_SECURE_END
