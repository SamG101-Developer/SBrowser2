export module ext.expected;

#include "ext/keywords.hpp"
#include <tl/expected.hpp>


_EXT_BEGIN
    export struct failure_t {};
    export static constexpr failure_t failure {};

    export template <typename T, typename E = failure_t>
    using expected = tl::expected<T, E>;
_EXT_END
