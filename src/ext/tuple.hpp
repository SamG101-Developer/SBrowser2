#ifndef SBROWSER2_SRC_EXT_TUPLE_HPP
#define SBROWSER2_SRC_EXT_TUPLE_HPP

#include "ext/vector.hpp"
#include "ext/variant.hpp"
#include "ext/view.hpp"

#include <functional>
#include <initializer_list>
#include <iterator>
#include <tuplet/tuple.hpp>

#include <range/v3/view/any_view.hpp>
#include <type_traits>


_EXT_BEGIN


using namespace tuplet;


// Missing from tuplet

namespace detail {
template <class T, class Tuple, size_t... Indices>
constexpr auto make_from_tuple(
        Tuple&& tuple,
        std::index_sequence<Indices...>)
        -> T
{
    return T{ext::get<Indices>(std::forward<Tuple>(tuple))...};
}
}

template <class T, class Tuple>
_EXT_NODISCARD constexpr auto make_from_tuple(
        Tuple&& tuple)
        -> T
{
    return detail::make_from_tuple<T>(
            std::forward<Tuple>(tuple),
            std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
}


//template <typename ...Args>
//auto make_tuple(ranges::any_view<Args...>&& range) -> ext::tuple<Args...>
//{
//    // TODO
//}
//
//
//template <typename T, typename ...Args>
//auto make_tuple(ext::vector<T>&& vector) -> ext::tuple<Args...>
//{
//    // TODO
//}


//template <typename ...Types>
//using tuple_iterator = variant<Types...>*;
//
//template <typename ...Types>
//struct tuple_view : view<tuple_iterator<Types...>>
//{
//    using view<tuple_iterator<Types...>>::view;
//
//    explicit tuple_view(const tuple<Types...>& other)
//            : view<tuple_iterator<Types...>>{}
//    {}
//};


_EXT_END


#endif //SBROWSER2_SRC_EXT_TUPLE_HPP
