module;
#include "ext/macros/namespaces.hpp"

export module ext.pair;
import ext.boolean;
import ext.tuple;


_EXT_BEGIN
    export template <typename K, typename V>
    constexpr auto make_pair(K&& key, V&& val)
    {return _EXT pair<std::remove_cvref_t<K>, std::remove_cvref_t<V>>{std::forward<K>(key), std::forward<V>(val)};}

    export auto pair_key_matches =
            []<typename K, typename V>(const _EXT pair<K, V>& pair, K&& key) -> ext::boolean
            {return pair.first == std::forward<K>(key);};

    export auto pair_val_matches =
            []<typename K, typename V>(const _EXT pair<K, V>& pair, V&& val) -> ext::boolean
            {return pair.second == std::forward<V>(val);};

    export auto get_pair_key =
            []<typename K, typename V>(const _EXT pair<K, V>& pair) -> decltype(pair.first)
            {return pair.first;};

    export auto get_pair_value =
            []<typename K, typename V>(const _EXT pair<K, V>& pair) -> decltype(pair.second)
            {return pair.second;};

    export auto identity_pair =
            []<typename K, typename V>(const _EXT pair<K, V>& pair) -> ext::boolean
            {return pair.first == pair.second;};
_EXT_END
