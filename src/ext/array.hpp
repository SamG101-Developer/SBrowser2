#ifndef SBROWSER2_SRC_EXT_ARRAY_HPP
#define SBROWSER2_SRC_EXT_ARRAY_HPP

#include "ext/keywords.hpp"
#include <array>


_EXT_BEGIN

template <typename T, size_t N>
using array = std::array<T, N>;

_EXT_END

#endif //SBROWSER2_SRC_EXT_ARRAY_HPP
