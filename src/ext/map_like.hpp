#pragma once
#ifndef SBROWSER2_MAP_LIKE_HPP
#define SBROWSER2_MAP_LIKE_HPP

#include "ext/keywords.hpp"
#include "ext/map.hpp"


_EXT_BEGIN

/**
 * The `map_like` class is inherited as a mixin into any other class that wishes to use the [] operator to retrieve data
 * in some form. This can be from another map, a set of attributes, calling another method etc, so a pure virtual method
 * is defined, forcing the [] operator to be implemented.
 * @tparam K The type that the keys of the map are
 * @tparam V The type that the vals of the map are
 */
template <typename K, typename V>
class map_like
{
public cpp_operators:
    virtual auto operator[](const K& key) -> V& = 0;
};


/**
 * The `map_like_linked` class is an extension to the inherited `map_like` class, as there is a constructor that allows
 * for a reference to a map to be linked to, and the [] operator is defined to access this linked map. In other words,
 * it is syntactic sugar for using the `map_like` class, and defining the [] operator in every class to use a `map`
 * attribute
 * @tparam K The type that the keys of the map are
 * @tparam V The type that the vals of the map are
 */
template <typename K, typename V>
class map_like_linked : public map_like<K, V>
{
public constructors:
    explicit map_like_linked(map<K, V>* container = nullptr)
            : m_linked_map(container ?: std::make_unique<map<K, V>>())
    {}

public cpp_operators:
    auto operator[](const K& key) -> V& override {return m_linked_map.at(key);}

private cpp_properties:
    std::unique_ptr<map<K, V>> m_linked_map;
};

_EXT_END


#endif //SBROWSER2_MAP_LIKE_HPP
