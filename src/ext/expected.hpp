#pragma once
#ifndef SBROWSER2_SRC_EXT_EXPECTED_HPP
#define SBROWSER2_SRC_EXT_EXPECTED_HPP

#include "ext/keywords.hpp"
#include <tl/expected.hpp>


_EXT_BEGIN
    struct failure_t {};

    template <typename T, typename E = failure_t>
    using expected = tl::expected<T, E>;
_EXT_END


#endif //SBROWSER2_SRC_EXT_EXPECTED_HPP
