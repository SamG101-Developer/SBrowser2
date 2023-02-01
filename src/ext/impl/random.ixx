module;
#include "ext/macros/namespaces.hpp"
#include <effolkronium/random.hpp>


export module ext.core:random;


_EXT_BEGIN
    namespace random
    {
        template <typename T> auto random_int(T&& min = std::numeric_limits<T>::min(), T&& max = std::numeric_limits<T>::max()) -> T;
    }
_EXT_END
