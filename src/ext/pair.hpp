#pragma once
#ifndef SBROWSER2_PAIR_HPP
#define SBROWSER2_PAIR_HPP

#include "ext/boolean.hpp"
#include "ext/keywords.hpp"
#include <tuplet/tuple.hpp>


_EXT_BEGIN

template <typename _Vt0, typename _Vt1>
using pair = tuplet::pair<_Vt0, _Vt1>;

template <typename _Vt0, typename _Vt1>
using pair_view = const _EXT pair<_Vt0, _Vt1>&;

template <typename _Vt0, typename _Vt1>
constexpr auto make_pair(_Vt0&& _First, _Vt1&& _Second)
{
    return ext::pair<
            std::remove_cvref_t<_Vt0>,
            std::remove_cvref_t<_Vt1>
            >{std::forward<_Vt0>(_First), std::forward<_Vt1>(_Second)};
}

auto pair_key_matches = []<typename _Ty0, typename _Ty1>(const _EXT pair<_Ty0, _Ty1>& _Pair, _Ty0&& _Key) -> ext::boolean
{
    return _Pair.first == std::forward<_Ty0>(_Key);
};


auto pair_val_matches = []<typename _Ty0, typename _Ty1>(const _EXT pair<_Ty0, _Ty1>& _Pair, _Ty1&& _Val) -> ext::boolean
{
    return _Pair.second == std::forward<_Ty0>(_Val);
};

_EXT_END


#endif //SBROWSER2_PAIR_HPP
