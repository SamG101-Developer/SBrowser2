export module ext.promise;

#include "ext/keywords.hpp"


_EXT_BEGIN
    export template <typename T>
    struct promise {private: promise() = default;};
_EXT_END


#endif //SBROWSER2_SRC_EXT_PROMISE_HPP
