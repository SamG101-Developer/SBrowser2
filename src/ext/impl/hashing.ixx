module;
#include "ext/macros/namespaces.hpp"
#include <function2/function2.hpp>
#include <tuplet/tuple.hpp>
#include <type_traits>

export module ext.core:hashing;

import :any;
import :concepts;
import :boolean;
import :functional;
import :map;
import :number;
import :set;
import :string;
import :tuple;
import :type_traits;


_EXT_BEGIN
    template <_EXT iterable Rng>
    auto hash_range(Rng&& range) -> size_t;
_EXT_END


_STD_BEGIN
    export template <>
    struct hash<_EXT any>
    {constexpr auto operator()(const _EXT any& value) const noexcept -> size_t {return *value.m_hash;}};

    export template <>
    struct hash<_EXT boolean>
    {constexpr auto operator()(const _EXT boolean& value) const noexcept -> size_t {return value ? 1 : 0;}};

    export template <typename ...Ts> // TODO
    struct hash<_EXT function<Ts...>>
    {constexpr auto operator()(_EXT function_view<Ts...> value) const noexcept -> size_t {return 0;}};

    export template <typename T>
    struct hash<_EXT number<T>>
    {constexpr auto operator()(const _EXT number<T>& value) const noexcept -> size_t {return _STD hash<T>{}(*value);}};

    export template <_EXT pure_iterable T>
    struct hash<T>
    {constexpr auto operator()(_EXT view_of_t<T> value) const noexcept -> size_t {return _EXT hash_range(value);}};

    export template <typename ...Ts> // TODO
    struct hash<_EXT tuple<Ts...>>
    {constexpr auto operator()(const _EXT tuple<Ts...>& value) const noexcept -> size_t {return 0;}};
_STD_END
