#pragma once
#ifndef SBROWSER2_PAIR_HPP
#define SBROWSER2_PAIR_HPP

#include "ext/boolean.hpp"
#include "ext/tuple.hpp"


_EXT_BEGIN

template <typename Key, typename Val>
using pair_view = const pair<std::reference_wrapper<Key>, std::reference_wrapper<Val>>&;

template <typename Key, typename Val>
constexpr auto make_pair(Key&& key, Val&& val)
{
    return ext::pair<
            std::remove_cvref_t<Key>,
            std::remove_cvref_t<Val>
            >{std::forward<Key>(key), std::forward<Val>(val)};
}

struct pair_key_matches
{
    template <typename T, typename U>
    constexpr auto operator()(const pair<T, U>& pair, T&& key) const -> ext::boolean
    {
        return pair.first == std::forward<T>(key);
    }
};


struct pair_val_matches
{
    template <typename T, typename U>
    constexpr auto operator()(const pair<T, U>& pair, U&& val) const -> ext::boolean
    {
        return pair.second == std::forward<U>(val);
    }
};


struct identity_pair
{
    template <typename T, typename U>
    constexpr auto operator()(const pair<T, U>& pair) const -> ext::boolean
    {
        return pair.first == pair.second;
    }
};

_EXT_END


#endif //SBROWSER2_PAIR_HPP
