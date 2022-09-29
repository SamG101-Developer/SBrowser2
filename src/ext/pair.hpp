#pragma once
#ifndef SBROWSER2_PAIR_HPP
#define SBROWSER2_PAIR_HPP

#include "ext/tuple.hpp"
#include "ext/keywords.hpp"


_EXT_BEGIN

template <typename K, typename V>
constexpr auto make_pair(K&& key, V&& val)
{
    return ext::pair<std::remove_cvref_t<K>, std::remove_cvref_t<V>>{std::forward<K>(key), std::forward<V>(val)};
}


auto pair_key_matches = []<typename T, typename U>(const pair<T, U>& pair, T&& key) -> ext::boolean
{return pair.first == std::forward<T>(key);};


auto pair_val_matches = []<typename T, typename U>(const pair<T, U>& pair, U&& val) -> ext::boolean
{return pair.second == std::forward<U>(val);};


auto identity_pair = []<typename T, typename U>(const pair<T, U>& pair) -> ext::boolean
{return pair.first == pair.second;};

_EXT_END


#endif //SBROWSER2_PAIR_HPP
