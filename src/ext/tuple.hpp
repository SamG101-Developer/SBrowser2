#ifndef SBROWSER2_SRC_EXT_TUPLE_HPP
#define SBROWSER2_SRC_EXT_TUPLE_HPP

#include "ext/variant.hpp"
#include "ext/view.hpp"

#include <functional>
#include <iterator>
#include <tuplet/tuple.hpp>


_EXT_BEGIN

using namespace tuplet;

template <typename ...Ts>
using tuple_view = const tuple<Ts...>&;

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
