module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/namespaces.hpp"
#include "ext/macros/macros.hpp"
#include "javascript/macros/expose.hpp"
#include <memory>

export module ext.mixins:map_like;
import ext.core;
import apis.dom_object;
import apis.dom_object_private;
import js.env.module_type;

namespace ext
{
    export template <typename K, typename V> class map_like_private;
    export template <typename K, typename V> class map_like_linked_private;
    export template <typename K, typename V> class map_like;
    export template <typename K, typename V> class map_like_linked;
    export template <typename K, typename V> using async_map_like = map_like<K, V>;
    export template <typename K, typename V> using async_map_like_linked = map_like_linked<K, V>;
}


template <typename K, typename V>
class ext::map_like_private
        : virtual dom_object_private
{
public:
    MAKE_QIMPL_T(map_like, K, V);
};


template <typename K, typename V>
class ext::map_like_linked_private
        : map_like_private<K, V>
{
public:
    MAKE_QIMPL_T(map_like_linked, K, V);

public:
    std::unique_ptr<ext::map<K, V>> map;
};


template <typename K, typename V>
class ext::map_like
        : virtual public dom_object
{
public constructors:
    explicit map_like() {INIT_PIMPL;}
    MAKE_PIMPL_T(map_like, K, V);
    MAKE_V8_AVAILABLE(ALL);

public:
    virtual auto operator[](const K& key) -> V& = 0;
    virtual auto operator[](const K& key) const -> V& {return (*this)[key];}
};


template <typename K, typename V>
class ext::map_like_linked
        : public map_like<K, V>
{
public constructors:
    MAKE_PIMPL_T(map_like_linked, K, V);
    MAKE_V8_AVAILABLE(ALL);

    explicit map_like_linked(map<K, V>* container = nullptr)
    {
        INIT_PIMPL; ACCESS_PIMPL;
        d->map = container ? std::unique_ptr<map<K, V>>{container} : std::make_unique<map<K, V>>();
    }

public:
    auto operator[](const K& key) -> V& override
    {
        ACCESS_PIMPL;
        return d->map->at(key);
    }

    auto operator[](const K& key) const -> V& override
    {
        ACCESS_PIMPL;
        return d->map->at(key);
    }
};
