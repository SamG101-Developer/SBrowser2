#ifndef SBROWSER2_RANGES_HPP
#define SBROWSER2_RANGES_HPP

// TODO : add constraints to range views / actions / algorithms, like in range-v3 library

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "ext/type_traits.hpp"

#include <range/v3/range/conversion.hpp>
#include <range/v3/action.hpp>
#include <range/v3/action/remove.hpp>
#include <range/v3/action/transform.hpp>
#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/drop_while.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/remove.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/take_while.hpp>
#include <range/v3/view/transform.hpp>

namespace ranges::views {enum filter_compare_t {EQ, NE, LT, LE, GT, GE};}

namespace ranges::views {struct lowercase_fn;}
namespace ranges::views {struct uppercase_fn;}
namespace ranges::views {struct split_string_fn;}
namespace ranges::views {struct take_until_fn;}
namespace ranges::views {struct drop_until_fn;}
namespace ranges::views {struct transform_if_fn;}
namespace ranges::views {template <typename _Tx> struct cast_all_to_fn;}
namespace ranges::views {template <filter_compare_t comparison> struct filter_eq_fn;}

namespace ranges::actions {struct lowercase_fn;}
namespace ranges::actions {struct uppercase_fn;}
namespace ranges::actions {struct transform_if_fn;}
namespace ranges::actions {template <typename _Tx> struct cast_all_to_fn;}

namespace ranges {struct contains_all_fn;}
namespace ranges {struct first_where_fn;}
namespace ranges {struct last_where_fn;}


/* VIEWS */
struct ranges::views::lowercase_fn
{
    constexpr auto operator()() const
    {
        // a lowercase conversion works by returning a transform adaptor that takes each item as a char type, converts
        // it to a lowercase char, and returns the character back
        return ranges::views::transform([](char c) {return std::tolower(c);});
    }
};


struct ranges::views::uppercase_fn
{
    constexpr auto operator()() const
    {
        // an uppercase conversion works by returning a transform adaptor that takes each item as a char type, converts
        // it to an uppercase char, and returns the character back
        return ranges::views::transform([](char c) {return std::toupper(c);});
    }
};


struct ranges::views::split_string_fn
{
    constexpr auto operator()(char delimiter) const
    {
        // a string split function works by returning a split-transform adaptor that splits the range by the delimiter;
        // this produces a range of ranges: splitting "hello world" by a " " becomes {{"h", "e", "l", "l", "o"}, {"0",
        // "o", "r", "l", "d"}}, with each item a character from the string, so using the transform adaptor, convert
        // each subrange into a string, to get {"hello", "world"}
        return ranges::views::split(delimiter) | ranges::views::transform([](range_v3_view auto&& sub_range) {return sub_range | ranges::to<_EXT string>();});
    }
};


struct ranges::views::take_until_fn
{
    constexpr auto operator()(auto&& _Pred) const
    {
        // a take_until adaptor works by taking items from a range until a condition is met - semantically the same as
        // take_while, but allowing the opposite method; for example, instead of
        // `take_while([](int i){... return !odd_number(i);}`, it can be written as `take_until(odd_number);`
        return ranges::views::take_while([_Pred = std::forward<decltype(_Pred)>(_Pred)](auto&& _Elem) {return !_Pred(std::forward<decltype(_Elem)>(_Elem));});
    }
};


struct ranges::views::drop_until_fn
{
    constexpr auto operator()(auto&& _Pred) const
    {
        // a drop_until adaptor works by dropping items from a range until a condition is met - semantically the same as
        // drop_while, but allowing the opposite method; for example, instead of
        // `drop_while([](int i){... return !odd_number(i);}`, it can be written as `drop_until(odd_number);`
        return ranges::views::drop_while([_Pred = std::forward<decltype(_Pred)>(_Pred)](auto&& _Elem) {return !_Pred(std::forward<decltype(_Elem)>(_Elem));});
    }
};


struct ranges::views::transform_if_fn // TODO : optimize so if isn't in for 'transform(...)' call
{
    template <type_is_not<_EXT boolean> _Fy0, typename _Fy1>
    constexpr auto operator()(_Fy0&& _PredIf, _Fy1&& _PredTransform) const
    {
        // a transform_if adaptor works by transforming each element, if it matches a method passed in as the 'PredIf'
        // statement. the return type of the '_PredTransform' method must be the same as the current element type in the
        // container / view, as there is no guarantee that very element will be transformed, so some elements will be
        // left in their original form
        return ranges::views::transform(
                [_PredIf = std::forward<_Fy0>(_PredIf), _PredTransform = std::forward<_Fy1>(_PredTransform)]<typename T>(T&& _Elem)
                {return _PredIf() ? _PredTransform(std::forward<T>(_Elem)) : std::forward<T>(_Elem);});
    }

    template <typename _Fy1>
    constexpr auto operator()(const _EXT boolean&& _PredIf, _Fy1&& _PredTransform) const
    {
        // a transform_if adaptor works by transforming each element, if '_PredIf' is a true boolean value
        return ranges::views::transform(
                [&_PredIf, _PredTransform = std::forward<_Fy1>(_PredTransform)]<typename T>(T&& _Elem)
                {return _PredIf ? _PredTransform(std::forward<T>(_Elem)) : std::forward<T>(_Elem);});
    }
};


template <typename _Tx>
struct ranges::views::cast_all_to_fn
{
    constexpr auto operator()(_EXT boolean_view remove_nullptr = true) const // TODO : apply parameter
    {
        // a cast_to_all adaptor works by taking a type, and dynamically casting all the elements in the range to
        // another type, and then removing all the instances of nullptr
        return ranges::views::transform([](auto* pointer) {return dynamic_cast<_Tx>(pointer);}) | ranges::views::remove(nullptr);
    }
};


template <ranges::views::filter_compare_t comparison>
struct ranges::views::filter_eq_fn
{
    // TODO : make sure that T is an attribute of V below? (does this static check already exist?)
    template <typename T, typename U>
    constexpr auto operator()(T&& attribute, U&& value) const
    {
        // a filter that allows for comparison of an attribute or method call from each object in the range; for
        // example, the first line is simplified into the second line (syntactic sugar)
        //      elements = node->children() | ranges::views::filter([](node* child) {return child->node_type == node::ELEMENT_NODE;}
        //      elements = node->children() | ranges::views::filter_eq(&node::node_type, node::ELEMENT_NODE);
        constexpr_return_if(comparison == EQ) ranges::views::filter(
                [attribute = std::forward<T>(attribute), value = std::forward<U>(value)]<typename V>
                (V&& candidate) {return std::mem_fn(std::forward<T>(attribute))(std::forward<V>(candidate)) == std::forward<U>(value);});

        else constexpr_return_if(comparison == NE) ranges::views::filter(
                [attribute = std::forward<T>(attribute), value = std::forward<U>(value)]<typename V>
                (V&& candidate) {return std::mem_fn(std::forward<T>(attribute))(std::forward<V>(candidate)) != std::forward<U>(value);});

        else constexpr_return_if(comparison == LT) ranges::views::filter(
                [attribute = std::forward<T>(attribute), value = std::forward<U>(value)]<typename V>
                (V&& candidate) {return std::mem_fn(std::forward<T>(attribute))(std::forward<V>(candidate)) < std::forward<U>(value);});

        else constexpr_return_if(comparison == LE) ranges::views::filter(
                [attribute = std::forward<T>(attribute), value = std::forward<U>(value)]<typename V>
                (V&& candidate) {return std::mem_fn(std::forward<T>(attribute))(std::forward<V>(candidate)) <= std::forward<U>(value);});

        else constexpr_return_if(comparison == GT) ranges::views::filter(
                [attribute = std::forward<T>(attribute), value = std::forward<U>(value)]<typename V>
                (V&& candidate) {return std::mem_fn(std::forward<T>(attribute))(std::forward<V>(candidate)) > std::forward<U>(value);});

        else constexpr_return_if(comparison == GE) ranges::views::filter(
                [attribute = std::forward<T>(attribute), value = std::forward<U>(value)]<typename V>
                (V&& candidate) {return std::mem_fn(std::forward<T>(attribute))(std::forward<V>(candidate)) >= std::forward<U>(value);});
    }
};


/* ACTIONS */
struct ranges::actions::lowercase_fn
{
    constexpr auto operator()() const
    {
        return ranges::actions::transform([](char c) {return std::tolower(c);});
    }

    constexpr auto operator()(range_v3_view auto&& _Range) const
    {
        return _Range |= ranges::actions::lowercase_fn()();
    }
};


struct ranges::actions::uppercase_fn
{
    constexpr auto operator()() const
    {
        return ranges::actions::transform([](char c) {return std::toupper(c);});
    }

    constexpr auto operator()(range_v3_view auto&& _Range) const
    {
        return _Range |= ranges::actions::uppercase_fn()();
    }
};


struct ranges::actions::transform_if_fn
{
    template <typename _Fy0, typename _Fy1>
    constexpr auto operator()(_Fy0&& _PredIf, _Fy1&& _PredTransform) const
    {
        // a transform_if adaptor works by transforming each element, if it matches a method passed in as the 'PredIf'
        // statement. the return type of the '_PredTransform' method must be the same as the current element type in the
        // container / view, as there is no guarantee that very element will be transformed, so some elements will be
        // left in their original form
        return ranges::actions::transform(
                [_PredIf = std::forward<_Fy0>(_PredIf), _PredTransform = std::forward<_Fy1>(_PredTransform)]<typename T>(T&& _Elem)
                {return _PredIf() ? _PredTransform(std::forward<T>(_Elem)) : std::forward<T>(_Elem);});
    }

    template <typename _Fy1>
    constexpr auto operator()(const _EXT boolean&& _PredIf, auto&& _PredTransform) const
    {
        // a transform_if adaptor works by transforming each element, if 'PredIf' is a true boolean value
        return ranges::actions::transform(
                [&_PredIf, _PredTransform = std::forward<_Fy1>(_PredTransform)]<typename T>(T&& _Elem)
                {return _PredIf ? _PredTransform(std::forward<T>(_Elem)) : std::forward<T>(_Elem);});
    }
};


template <typename _Tx>
struct ranges::actions::cast_all_to_fn
{
    constexpr auto operator()(_EXT boolean_view remove_nullptr = true) const // TODO : apply parameter
    {
        return ranges::actions::transform([](auto* pointer) {return dynamic_cast<_Tx>(pointer);}) | ranges::actions::remove(nullptr);
    }
};


/* ALGORITHMS */
struct ranges::contains_all_fn
{
    constexpr auto operator()(auto&& _Range1, auto&& _Range2) const
    {
        return ranges::all_of(
                std::forward<decltype(_Range2)>(_Range2),
                [_Range1 = std::forward<decltype(_Range1)>(_Range1)](auto&& _Item2) {ranges::contains(std::forward<decltype(_Range1)>(_Range1), std::forward<decltype(_Item2)>(_Item2));});
    }
};


struct ranges::first_where_fn
{
    template <typename Rng1, typename Fx>
    constexpr auto operator()(Rng1&& range1, Fx&& function) const
    {
        auto filtered = range1 | ranges::views::filter(std::forward<Fx>(function));
        return filtered.begin();
    }
};


struct ranges::last_where_fn
{
    template <typename Rng1, typename Fx>
    constexpr auto operator()(Rng1&& range1, Fx&& function) const
    {
        auto filtered = range1 | ranges::views::filter(std::forward<Fx>(function));
        return filtered.end();
    }
};


namespace ranges::views {constexpr split_string_fn split_string;}
namespace ranges::views {constexpr lowercase_fn lowercase;}
namespace ranges::views {constexpr uppercase_fn uppercase;}
namespace ranges::views {constexpr take_until_fn take_until;}
namespace ranges::views {constexpr drop_until_fn drop_until;}
namespace ranges::views {constexpr transform_if_fn transform_if;}
namespace ranges::views {template <typename _Tx> constexpr cast_all_to_fn<_Tx> cast_all_to;}
namespace ranges::views {template <filter_compare_t comparison> constexpr filter_eq_fn<comparison> filter_eq;}

namespace ranges::actions {constexpr lowercase_fn lowercase;}
namespace ranges::actions {constexpr uppercase_fn uppercase;}
namespace ranges::actions {constexpr transform_if_fn transform_if;}
namespace ranges::actions {template <typename _Tx> constexpr cast_all_to_fn<_Tx> cast_all_to;}

namespace ranges {constexpr contains_all_fn contains_all;}
namespace ranges {constexpr first_where_fn first_where;}
namespace ranges {constexpr last_where_fn last_where;}


#endif //SBROWSER2_RANGES_HPP
