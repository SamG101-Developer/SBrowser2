module;
#include "ext/macros/namespaces.hpp"
#include <ankerl/unordered_dense.h>


export module ext.core:map;
import :tuple;
import :vector;


_EXT_BEGIN
    export template <typename Key, typename Val>
    using map = ankerl::unordered_dense::map<Key, Val, ankerl::unordered_dense::hash<Key>, std::equal_to<Key>, _EXT vector<_EXT pair<Key, Val>>>;

    export template <typename Key, typename Val>
    using multi_map = ankerl::unordered_dense::map<Key, Val, ankerl::unordered_dense::hash<Key>, std::equal_to<Key>, _EXT vector<_EXT pair<Key, Val>>>;
_EXT_END

_EXT_SECURE_BEGIN
    export template <typename Key, typename Val>
    using map = ankerl::unordered_dense::map<Key, Val, ankerl::unordered_dense::hash<Key>, std::equal_to<Key>, _EXT secure::vector<_EXT pair<Key, Val>>>;

    export template <typename Key, typename Val, typename Allocator = _EXT secure::vector<_EXT pair<Key, Val>>>
    using multi_map = ankerl::unordered_dense::map<Key, Val, ankerl::unordered_dense::hash<Key>, std::equal_to<Key>, _EXT secure::vector<_EXT pair<Key, Val>>>;
_EXT_SECURE_END
