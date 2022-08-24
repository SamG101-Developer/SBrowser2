#ifndef SBROWSER2_SRC_EXT_TUPLE_HPP
#define SBROWSER2_SRC_EXT_TUPLE_HPP

#include "ext/vector.hpp"
#include "ext/variant.hpp"
#include "ext/view.hpp"

#include <functional>
#include <iterator>
#include <tuplet/tuple.hpp>

#include <range/v3/view/any_view.hpp>


_EXT_BEGIN

using namespace tuplet;

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
