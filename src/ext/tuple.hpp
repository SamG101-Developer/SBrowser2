#ifndef SBROWSER2_SRC_EXT_TUPLE_HPP
#define SBROWSER2_SRC_EXT_TUPLE_HPP

#include <functional>
#include <initializer_list>
#include <iterator>
#include <type_traits>

#include <tuplet/tuple.hpp>


_EXT_BEGIN
    using namespace tuplet;
_EXT_END


_EXT_DETAIL_BEGIN

template <class T, class Tuple, size_t... Indices>
constexpr auto make_from_tuple(Tuple&& tuple, std::index_sequence<Indices...>) -> T
{
    return T{ext::get<Indices>(std::forward<Tuple>(tuple))...};
}


template <size_t... Is, typename T, typename F, typename Iterable>
constexpr auto tuple_foreach(std::index_sequence<Is...>, T&& tuple, F&& function, Iterable&& iterable) -> void
{
    (iterable.push_back(function(ext::get<Is>(std::forward<T>(tuple)))), ...);
}

_EXT_DETAIL_END


_EXT_BEGIN

template <class T, class Tuple>
_EXT_NODISCARD constexpr auto make_from_tuple(Tuple&& tuple) -> T
{
    return detail::make_from_tuple<T>(
            std::forward<Tuple>(tuple),
            std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
}


template <typename T, typename F, typename Iterable>
constexpr auto tuple_foreach(T&& tuple, F&& function, Iterable&& iterable = nullptr) -> void
{
    detail::tuple_foreach(
            std::make_index_sequence<std::tuple_size_v<std::decay_t<T>>>{},
            std::forward<T>(tuple),
            std::forward<F>(function),
            std::forward<Iterable>(iterable));
}

_EXT_END


#endif //SBROWSER2_SRC_EXT_TUPLE_HPP
