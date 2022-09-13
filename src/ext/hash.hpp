#ifndef SBROWSER2_SRC_EXT_DETAIL_HASH_HPP
#define SBROWSER2_SRC_EXT_DETAIL_HASH_HPP

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/number.hpp"
#include "ext/tuple.hpp"
#include <type_traits>


_STD_BEGIN

template <>
struct hash<_EXT any>
{constexpr auto operator()(const _EXT any& value) const noexcept -> size_t {return *value.m_hash;}};


template <>
struct hash<_EXT boolean>
{constexpr auto operator()(const _EXT boolean& value) const noexcept -> size_t {return value ? 1 : 0;}};


template <typename ...Ts>
struct hash<_EXT function<Ts...>>
{constexpr auto operator()(const _EXT function<Ts...>& value) const noexcept -> size_t {return _STD hash<size_t>{}(static_cast<size_t>(&value));}};


template <typename K, typename V>
struct hash<_EXT map<K, V>>
{constexpr auto operator()(const _EXT map<K, V>& value) const noexcept -> size_t {return _STD hash<size_t>{}(&value);}};


template <typename T>
struct hash<_EXT number<T>>
{constexpr auto operator()(const _EXT number<T>& value) const noexcept -> size_t {return _STD hash<T>{}(*value);}};


template <typename ...Ts>
struct hash<_EXT tuple<Ts...>>
{constexpr auto operator()(const _EXT tuple<Ts...>& value) const noexcept -> size_t {return 0;}};

_STD_END


#endif //SBROWSER2_SRC_EXT_DETAIL_HASH_HPP
