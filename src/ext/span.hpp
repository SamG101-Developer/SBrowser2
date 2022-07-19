#pragma once
#ifndef SBROWSER2_SRC_EXT_SPAN_HPP
#define SBROWSER2_SRC_EXT_SPAN_HPP

#include "ext/keywords.hpp"
#include <range/v3/span.hpp>


_EXT_BEGIN

template <typename _Vt>
using span = ranges::span<_Vt>;

_EXT_END


#endif //SBROWSER2_SRC_EXT_SPAN_HPP
