module;
#include "ext/macros/namespaces.hpp"
#include <tl/expected.hpp>

export module ext.expected;


_EXT_BEGIN
    export struct failure_t {};
    export inline constexpr failure_t failure {};

    export template <typename T, typename E = failure_t>
    using expected = tl::expected<T, E>;
_EXT_END