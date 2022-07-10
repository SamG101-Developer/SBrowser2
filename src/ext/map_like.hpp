#pragma once
#ifndef SBROWSER2_MAP_LIKE_HPP
#define SBROWSER2_MAP_LIKE_HPP

namespace ext {template <typename _Tx1, typename _Tx2> class map_like;}

#include <ext/keywords.hpp>
#include <ext/optional.hpp>
#include <ext/map.hpp>


template <typename _Tx1, typename _Tx2>
class ext::map_like
{
public cpp_operators:
    virtual auto operator[](const _Tx1& _Key) -> _Tx2 = 0;
};


#endif //SBROWSER2_MAP_LIKE_HPP
