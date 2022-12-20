module;
#include "ext/macros/namespaces.hpp"


export module ext.core:expected;
#include <tl/expected.hpp>


_EXT_BEGIN
    export struct failure_t {};
    export inline constexpr failure_t failure {};

    export template <typename T, typename E = failure_t>
    using expected = tl::expected<T, E>;
_EXT_END
