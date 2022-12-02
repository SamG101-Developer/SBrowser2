export module ext.map;

import ext.pair;
import ext.vector;

#include <ankerl/unordered_dense.h>
#include <cryptopp/secblock.h>


_EXT_BEGIN
    template <typename Key, typename Val, typename Allocator = _EXT vector<_EXT pair<Key, Val>>>
    using map = ankerl::unordered_dense::map<Key, Val, ankerl::unordered_dense::hash<Key>, std::equal_to<Key>, Allocator>;

    template <typename Key, typename Val, typename Allocator = _EXT vector<_EXT pair<Key, Val>>>
    using multi_map = ankerl::unordered_dense::map<Key, Val, ankerl::unordered_dense::hash<Key>, std::equal_to<Key>, Allocator>;
_EXT_END


_EXT_SECURE_BEGIN
    template <typename Key, typename Val>
    using map = _EXT map<Key, Val, _EXT secure::vector<_EXT pair<Key, Val>>>;

    template <typename Key, typename Val, typename Allocator = _EXT secure::vector<_EXT pair<Key, Val>>>
    using multi_map = _EXT map<Key, Val, _EXT secure::vector<_EXT pair<Key, Val>>>;
_EXT_SECURE_END


// TODO : for unordered_map, create custom equality check to allow for duplicate key emplacing, but allow finding


#endif //SBROWSER2_MAP_HPP
