#pragma once
#ifndef SBROWSER2_PAIR_HPP
#define SBROWSER2_PAIR_HPP

#include "ext/tuple.hpp"
#include "ext/keywords.hpp"


_EXT_BEGIN
    template <typename K, typename V>
    constexpr auto make_pair(K&& key, V&& val)
    {return _EXT pair<std::remove_cvref_t<K>, std::remove_cvref_t<V>>{std::forward<K>(key), std::forward<V>(val)};}
    
    auto pair_key_matches =
            []<typename K, typename V>(const _EXT pair<K, V>& pair, K&& key) -> ext::boolean
            {return pair.first == std::forward<K>(key);};
    
    auto pair_val_matches =
            []<typename K, typename V>(const _EXT pair<K, V>& pair, V&& val) -> ext::boolean
            {return pair.second == std::forward<V>(val);};
    
    auto get_pair_key =
            []<typename K, typename V>(const _EXT pair<K, V>& pair) -> decltype(pair.first)
            {return pair.first;};
    
    auto get_pair_value =
            []<typename K, typename V>(const _EXT pair<K, V>& pair) -> decltype(pair.second)
            {return pair.second;};
    
    auto identity_pair =
            []<typename K, typename V>(const _EXT pair<K, V>& pair) -> ext::boolean
            {return pair.first == pair.second;};
_EXT_END


#endif //SBROWSER2_PAIR_HPP
