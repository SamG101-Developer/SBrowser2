#pragma once
#ifndef SBROWSER2_SRC_EXT_EXPECTED_HPP
#define SBROWSER2_SRC_EXT_EXPECTED_HPP

#include "ext/keywords.hpp"
#include <tl/expected.hpp>


_EXT_BEGIN
    MAKE_STRUCT(failure, );

    template <typename T, typename E = failure_fn>
    using expected = tl::expected<T, E>;
_EXT_END


#endif //SBROWSER2_SRC_EXT_EXPECTED_HPP
