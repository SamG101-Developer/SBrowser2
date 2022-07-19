#pragma once
#ifndef SBROWSER2_MAP_LIKE_HPP
#define SBROWSER2_MAP_LIKE_HPP

#include "ext/keywords.hpp"
#include "ext/optional.hpp"
#include "ext/map.hpp"


_EXT_BEGIN

template <typename _Tx1, typename _Tx2>
class map_like
{
public cpp_operators:
    virtual auto operator[](const _Tx1& _Key) -> _Tx2 = 0;
};

_EXT_END


#endif //SBROWSER2_MAP_LIKE_HPP
