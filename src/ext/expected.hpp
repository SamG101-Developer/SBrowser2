#pragma once
#ifndef SBROWSER2_SRC_EXT_EXPECTED_HPP
#define SBROWSER2_SRC_EXT_EXPECTED_HPP

#include "ext/keywords.hpp"
#include <tl/expected.hpp>


_EXT_BEGIN

using tl::expected;


struct failure_t {};
auto failure = failure_t{};

_EXT_END


#endif //SBROWSER2_SRC_EXT_EXPECTED_HPP
