module;
#include <tuplet/tuple.hpp>

_EXT_BEGIN
    using namespace tuplet;
_EXT_END

_EXT_LITERALS_BEGIN
    using namespace tuplet::literals;
_EXT_LITERALS_END


export module ext.tuple;
import ext.functional;
import std.core;

_EXT_DETAIL_BEGIN
    export template <class T, class Tuple, size_t... Indices>
    constexpr auto make_from_tuple(Tuple&& tuple, std::index_sequence<Indices...>) -> T
    {return T{ext::get<Indices>(std::forward<Tuple>(tuple))...};}

    export template <size_t... Is, typename T, typename F, typename Iterable>
    constexpr auto tuple_foreach(std::index_sequence<Is...>, T&& tuple, F&& function, Iterable&& iterable) -> void
    {(iterable.push_back(function(ext::get<Is>(std::forward<T>(tuple)))), ...);}
_EXT_DETAIL_END


_EXT_BEGIN
    export template <class T, class Tuple>
    constexpr auto make_from_tuple(Tuple&& tuple) -> T
    {
        return detail::make_from_tuple<T>(
                std::forward<Tuple>(tuple),
                std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
    }

    export template <typename T, typename F, typename Iterable>
    constexpr auto tuple_foreach(T&& tuple, F&& function, Iterable&& iterable = nullptr) -> void
    {
        detail::tuple_foreach(
                std::make_index_sequence<std::tuple_size_v<std::decay_t<T>>>{},
                std::forward<T>(tuple), std::forward<F>(function), std::forward<Iterable>(iterable));
    }

    export template <size_t, typename T>
    using _repeat_type = T;

    export template <typename T, size_t ...Is>
    auto make_repeat_tuple(std::index_sequence<Is...>)
    {return ext::tuple<_repeat_type<Is, T>...>{};}

    export template <typename T, size_t N>
    auto make_repeat_tuple()
    {return make_repeat_tuple<T>(std::make_index_sequence<N>{});}
_EXT_END


/*
 * https://stackoverflow.com/questions/37093920/function-to-generate-a-tuple-given-a-size-n-and-a-type-t
 * https://stackoverflow.com/a/37094024/10862918
 * https://stackoverflow.com/users/2756719/t-c
 * 15/11/2022 16:00
 */
