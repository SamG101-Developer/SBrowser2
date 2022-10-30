#pragma once
#ifndef SBROWSER2_SRC_EXT_BIT_HPP
#define SBROWSER2_SRC_EXT_BIT_HPP

#include "ext/keywords.hpp"


_EXT_BEGIN
    enum class where_t {MOST_SIGNIFICANT, LEAST_SIGNIFICANT};

    template <typename T, typename U>
    auto set_bits(T& input, U what_to, where_t where)
    {}
_EXT_END


#endif //SBROWSER2_SRC_EXT_BIT_HPP
