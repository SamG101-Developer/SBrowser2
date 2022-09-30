#pragma once
#ifndef SBROWSER2_MAP_LIKE_HPP
#define SBROWSER2_MAP_LIKE_HPP

#include <memory>

#include "ext/keywords.hpp"
#include "ext/map.hpp"

#include "dom_object_private.hpp"
#include "dom_object.hpp"


_EXT_BEGIN

template <typename K, typename V>
struct map_like_private : virtual dom_object_private {};


template <typename K, typename V>
struct map_like_linked_private : map_like_private<K, V>
{
    std::unique_ptr<ext::map<K, V>> map;
};


template <typename K, typename V>
class map_like : public virtual dom_object
{
public constructors:
    MAKE_PIMPL_TEMPLATED(map_like, K, V);

    explicit map_like()
    {
        INIT_PIMPL_TEMPLATED(map_like, K, V);
    }

    virtual auto operator[](const K& key) -> V& = 0;
    virtual auto operator[](const K& key) const -> V& {return (*this)[key];}
};


template <typename K, typename V>
class map_like_linked : public map_like<K, V>
{
public constructors:
    MAKE_PIMPL_TEMPLATED(map_like_linked, K, V);

    explicit map_like_linked(map<K, V>* container = nullptr)
    {
        INIT_PIMPL_TEMPLATED(map_like_linked, K, V);
        ACCESS_PIMPL_TEMPLATED(map_like_linked, K, V);
        d->map = container ? std::unique_ptr<map<K, V>>{container} : std::make_unique<map<K, V>>();
    }

    auto operator[](const K& key) -> V& override
    {
        ACCESS_PIMPL_TEMPLATED(map_like_linked, K, V);
        return d->map.at(key);
    }

    auto operator[](const K& key) const -> V& override
    {
        ACCESS_PIMPL_TEMPLATED(map_like_linked, K, V);
        return d->map.at(key);
    }
};

_EXT_END


#endif //SBROWSER2_MAP_LIKE_HPP
