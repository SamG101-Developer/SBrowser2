#pragma once
#ifndef SBROWSER2_PAIR_HPP
#define SBROWSER2_PAIR_HPP

#include "ext/boolean.hpp"
#include "ext/tuple.hpp"
#include "ext/view.hpp"
#include <iterator>


_EXT_BEGIN


template <typename K, typename V>
using pair_view_iterator = std::conditional_t<(sizeof(K) > sizeof(V)), K*, V*>;

template <typename K, typename V>
class pair_view : public view<pair_view_iterator<K, V>>
{
public constructors:
    using view<pair_view_iterator<K, V>>::view;

    explicit pair_view(pair<K, V>&& other)
            : view<pair_view_iterator<K, V>>{std::make_move_iterator(&other.first), std::make_move_iterator(&other.second)}
    {}

    explicit pair_view(const pair<K, V>& other)
            : view<pair_view_iterator<K, V>>{&other.first, &other.second}
    {}
};


template <typename K, typename V>
constexpr auto make_pair(K&& key, V&& val)
{
    return ext::pair<
            std::remove_cvref_t<K>,
            std::remove_cvref_t<V>
            >{std::forward<K>(key), std::forward<V>(val)};
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
