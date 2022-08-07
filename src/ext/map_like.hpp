#pragma once
#ifndef SBROWSER2_MAP_LIKE_HPP
#define SBROWSER2_MAP_LIKE_HPP

#include "ext/keywords.hpp"
#include "ext/optional.hpp"
#include "ext/map.hpp"


_EXT_BEGIN

/**
 * The `map_like` class is inherited as a mixin into any other class that wishes to use the [] operator to retrieve data
 * in some form. This can be from another map, a set of attributes, calling another method etc, so a pure virtual method
 * is defined, forcing the [] operator to be implemented.
 * @tparam _Tx1 The type that the keys of the map are
 * @tparam _Tx2 The type that the vals of the map are
 */
template <typename _Tx1, typename _Tx2>
class map_like
{
public cpp_operators:
    virtual auto operator[](const _Tx1& _Key) -> _Tx2 = 0;
};


/**
 * The `map_like_linked` class is an extension to the inherited `nap_like` clas, as there is a constructor that allows
 * for a reference to a map to be linked to, and the [] operator is defined to access this linked map. In other words,
 * it is syntactic sugar for using the `map_like` class, and defining the [] operator in every class to use a `map`
 * attribute
 * @tparam _Tx1 The type that the keys of the map are
 * @tparam _Tx2 The type that the vals of the map are
 */
template <typename _Tx1, typename _Tx2>
class map_like_linked : public map_like<_Tx1, _Tx2>
{
public constructors:
    explicit map_like_linked(map<_Tx1, _Tx2>& map)
            : m_linked_map(map)
    {}

public cpp_operators:
    auto operator[](const _Tx1& _Key) -> _Tx2 override {return m_linked_map.at(_Key);}

private cpp_properties:
    const map<_Tx1, _Tx2>& m_linked_map;
};

_EXT_END


#endif //SBROWSER2_MAP_LIKE_HPP
