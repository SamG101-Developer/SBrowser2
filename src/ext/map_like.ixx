module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/namespaces.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include <memory>

export module ext.map_like;
import apis._.dom_object;
import apis._.dom_object_private;
import ext.map;
import ext.tuple;
import js.env.module_type;


DEFINE_PRIVATE_CLASS_T(ext, map_like, typename K, typename V) : virtual dom_object_private
{
    MAKE_QIMPL_T(map_like, K, V);
};


DEFINE_PRIVATE_CLASS_T(ext, map_like_linked, typename K, typename V) : map_like_private<K, V>
{
    MAKE_QIMPL_T(map_like_linked, K, V);
    std::unique_ptr<ext::map<K, V>> map;
};


DEFINE_PUBLIC_CLASS_T(ext, map_like, typename K, typename V)
        : virtual public dom_object
{
public constructors:
    MAKE_PIMPL_T(map_like, K, V);
    MAKE_V8_AVAILABLE(ALL);

    explicit map_like()
    {INIT_PIMPL;}

    virtual auto operator[](const K& key) -> V& = 0;
    virtual auto operator[](const K& key) const -> V& {return (*this)[key];}
};


DEFINE_PUBLIC_CLASS_T(ext, map_like_linked, typename K, typename V)
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
