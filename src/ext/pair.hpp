#pragma once
#ifndef SBROWSER2_PAIR_HPP
#define SBROWSER2_PAIR_HPP

#include "ext/boolean.hpp"
#include "ext/tuple.hpp"


_EXT_BEGIN

template <typename T, typename U>
using pair_view = const pair<std::reference_wrapper<T>, std::reference_wrapper<U>>&;

template <typename _Vt0, typename _Vt1>
constexpr auto make_pair(_Vt0&& _First, _Vt1&& _Second)
{
    return ext::pair<
            std::remove_cvref_t<_Vt0>,
            std::remove_cvref_t<_Vt1>
            >{std::forward<_Vt0>(_First), std::forward<_Vt1>(_Second)};
}

auto pair_key_matches = []<typename _Ty0, typename _Ty1>(const pair<_Ty0, _Ty1>& _Pair, _Ty0&& _Key) -> ext::boolean
{
    return _Pair.first == std::forward<_Ty0>(_Key);
};


auto pair_val_matches = []<typename _Ty0, typename _Ty1>(const pair<_Ty0, _Ty1>& _Pair, _Ty1&& _Val) -> ext::boolean
{
    return _Pair.second == std::forward<_Ty0>(_Val);
};

_EXT_END


#endif //SBROWSER2_PAIR_HPP
