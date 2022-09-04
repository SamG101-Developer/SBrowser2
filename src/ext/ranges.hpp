#ifndef SBROWSER2_RANGES_HPP
#define SBROWSER2_RANGES_HPP

// TODO : add constraints to range views / actions / algorithms, like in range-v3 library

#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/functional.hpp"
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
#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/map.hpp>
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
namespace ranges::views {struct transform_to_attr_fn;}
namespace ranges::views {struct transform_if_fn;}
namespace ranges::views {template <typename T> struct transform_to_obj_fn;}
namespace ranges::views {template <typename T> struct cast_all_to_fn;}
namespace ranges::views {template <filter_compare_t Comparison> struct filter_eq_fn;}
namespace ranges::views {struct transpose_fn;}
namespace ranges::views {struct remove_at_index_fn;}

namespace ranges::actions {struct lowercase_fn;}
namespace ranges::actions {struct uppercase_fn;}
namespace ranges::actions {struct transform_if_fn;}
namespace ranges::actions {template <typename T> struct cast_all_to_fn;}
namespace ranges::actions {struct replace_fn;}
namespace ranges::actions {struct remove_at_index_fn;}

namespace ranges {struct contains_any_fn;}
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
        // each sub-range into a string, to get {"hello", "world"}
        return ranges::views::split(delimiter) | ranges::views::transform([](range_v3_view auto&& sub_range) {return sub_range | ranges::to<_EXT string>();});
    }
};


struct ranges::views::take_until_fn
{
    template <callable F>
    constexpr auto operator()(F&& predicate) const
    {
        // a take_until adaptor works by taking items from a range until a condition is met - semantically the same as
        // take_while, but allowing the opposite method; for example, instead of
        // `take_while([](int i){... return !odd_number(i);}`, it can be written as `take_until(odd_number);`
        return ranges::views::take_while(
                [predicate = std::forward<F>(predicate)]<typename T>
                (T&& element) {return !predicate(std::forward<T>(element));});
    }
};


struct ranges::views::drop_until_fn
{
    template <callable F>
    constexpr auto operator()(F&& predicate) const
    {
        // a drop_until adaptor works by dropping items from a range until a condition is met - semantically the same as
        // drop_while, but allowing the opposite method; for example, instead of
        // `drop_while([](int i){... return !odd_number(i);}`, it can be written as `drop_until(odd_number);`
        return ranges::views::drop_while(
                [predicate = std::forward<F>(predicate)]<typename T>
                (T&& element) {return !predicate(std::forward<T>(element));});
    }
};


struct ranges::views::transform_to_attr_fn
{
    template <typename T>
    constexpr auto operator()(T&& attribute) const
    {
        // transform a container of objects into an attribute belonging to that object - syntactic sugar for
        //      ranges::views::transform(nodes, [](dom::nodes::node* node) {return node->text_content();})
        //      ranges::views::transform_to_attr(nodes, &node::text_content);
        return ranges::views::transform(
                [attribute = std::forward<T>(attribute)]<typename U>
                (U&& element) mutable {return std::mem_fn(std::forward<T>(attribute))(std::forward<U>(element));});
    }
};


struct ranges::views::transform_if_fn // TODO : optimize so if isn't in for 'transform(...)' call
{
    template <typename F0, typename F1>
    constexpr auto operator()(F0&& predicate_if, F1&& predicate_transform) const
    {
        // a transform_if adaptor works by transforming each element, if it matches a method passed in as the 'PredIf'
        // statement. the return type of the '_PredTransform' method must be the same as the current element type in the
        // container / view, as there is no guarantee that very element will be transformed, so some elements will be
        // left in their original form
        return ranges::views::transform(
                [predicate_if = std::forward<F0>(predicate_if), predicate_transform = std::forward<F1>(predicate_transform)]<typename T>
                (T&& element) mutable {return predicate_if() ? predicate_transform(std::forward<T>(element)) : std::forward<T>(element);});
    }

    template <typename F1>
    constexpr auto operator()(_EXT boolean&& predicate_if, F1&& predicate_transform) const
    {
        // a transform_if adaptor works by transforming each element, if '_PredIf' is a true boolean value
        return ranges::views::transform(
                [&predicate_if, predicate_transform = std::forward<F1>(predicate_transform)]<typename T>
                (T&& element) mutable {return predicate_if ? predicate_transform(std::forward<T>(element)) : std::forward<T>(element);});
    }
};


template <typename T>
struct ranges::views::transform_to_obj_fn
{
    constexpr auto operator()() const
    {
        return ranges::views::transform(
                []<typename ...Args>(Args&&... args) mutable
                {
                    constexpr_return_if(std::is_pointer_v<T>) new T{std::forward<Args>(args)...};
                    return T{std::forward<Args>(args)...};
                });
    }
};


template <typename T>
struct ranges::views::cast_all_to_fn
{
    constexpr auto operator()(_EXT boolean&& remove_nullptr = true) const // TODO : apply parameter
    {
        // a cast_to_all adaptor works by taking a type, and dynamically casting all the elements in the range to
        // another type, and then removing all the instances of nullptr
        return ranges::views::transform([](auto* pointer) {return dynamic_cast<T>(pointer);}) | ranges::views::remove(nullptr);
    }
};


template <ranges::views::filter_compare_t Comparison>
struct ranges::views::filter_eq_fn
{
    // TODO : make sure that T is an attribute of V below? (does this static check already exist?)
    template <typename T, typename U, typename F>
    constexpr auto operator()(T&& attribute, U&& value, F&& predicate = _EXT identity{}) const
    {
        // a filter that allows for comparison of an attribute or method call from each object in the range; for
        // example, the first line is simplified into the second line (syntactic sugar)
        //      elements = node->children() | ranges::views::filter([](node* child) {return child->node_type == node::ELEMENT_NODE;}
        //      elements = node->children() | ranges::views::filter<EQ>(&node::node_type, node::ELEMENT_NODE);
        constexpr_return_if(Comparison == EQ) ranges::views::filter(
                [attribute = std::forward<T>(attribute), value = std::forward<U>(value), predicate = std::forward<F>(predicate)]<typename V>
                (V&& candidate) mutable {return predicate(std::mem_fn(std::forward<T>(attribute))(std::forward<V>(candidate))) == std::forward<U>(value);});

        else constexpr_return_if(Comparison == NE) ranges::views::filter(
                [attribute = std::forward<T>(attribute), value = std::forward<U>(value), predicate = std::forward<F>(predicate)]<typename V>
                (V&& candidate) mutable {return predicate(std::mem_fn(std::forward<T>(attribute))(std::forward<V>(candidate))) != std::forward<U>(value);});

        else constexpr_return_if(Comparison == LT) ranges::views::filter(
                [attribute = std::forward<T>(attribute), value = std::forward<U>(value), predicate = std::forward<F>(predicate)]<typename V>
                (V&& candidate) mutable {return predicate(std::mem_fn(std::forward<T>(attribute))(std::forward<V>(candidate))) < std::forward<U>(value);});

        else constexpr_return_if(Comparison == LE) ranges::views::filter(
                [attribute = std::forward<T>(attribute), value = std::forward<U>(value), predicate = std::forward<F>(predicate)]<typename V>
                (V&& candidate) mutable {return predicate(std::mem_fn(std::forward<T>(attribute))(std::forward<V>(candidate))) <= std::forward<U>(value);});

        else constexpr_return_if(Comparison == GT) ranges::views::filter(
                [attribute = std::forward<T>(attribute), value = std::forward<U>(value), predicate = std::forward<F>(predicate)]<typename V>
                (V&& candidate) mutable {return predicate(std::mem_fn(std::forward<T>(attribute))(std::forward<V>(candidate))) > std::forward<U>(value);});

        else constexpr_return_if(Comparison == GE) ranges::views::filter(
                [attribute = std::forward<T>(attribute), value = std::forward<U>(value), predicate = std::forward<F>(predicate)]<typename V>
                (V&& candidate) mutable {return predicate(std::mem_fn(std::forward<T>(attribute))(std::forward<V>(candidate))) >= std::forward<U>(value);});
    }
};


struct ranges::views::transpose_fn
{
    constexpr auto operator()() const
    {
        return ranges::views::transform(
                []<template <typename> typename Container, typename T>(Container<T>&)
                {}); // TODO
    }
};


struct ranges::views::remove_at_index_fn
{
    constexpr auto operator()(_EXT number<size_t>&& r_index) const
    {
        return ranges::views::enumerate
                | ranges::views::remove_if([r_index = r_index](auto&& pair) mutable {return pair.first == r_index;})
                | ranges::views::values;
    }
};


/* ACTIONS */
struct ranges::actions::lowercase_fn
{
    constexpr auto operator()() const
    {
        return ranges::actions::transform([](char c) {return std::tolower(c);});
    }

    constexpr auto operator()(range_v3_view auto&& range) const
    {
        return range |= ranges::actions::lowercase_fn()();
    }
};


struct ranges::actions::uppercase_fn
{
    constexpr auto operator()() const
    {
        return ranges::actions::transform([](char c) {return std::toupper(c);});
    }

    constexpr auto operator()(range_v3_view auto&& range) const
    {
        return range |= ranges::actions::uppercase_fn()();
    }
};


struct ranges::actions::transform_if_fn // TODO : optimize so if isn't in for 'transform(...)' call
{
    template <typename F0, typename F1>
    constexpr auto operator()(F0&& predicate_if, F1&& predicate_transform) const
    {
        // a transform_if adaptor works by transforming each element, if it matches a method passed in as the 'PredIf'
        // statement. the return type of the '_PredTransform' method must be the same as the current element type in the
        // container / view, as there is no guarantee that very element will be transformed, so some elements will be
        // left in their original form
        return ranges::actions::transform(
                [predicate_if = std::forward<F0>(predicate_if), predicate_transform = std::forward<F1>(predicate_transform)]<typename T>
                (T&& element) {return predicate_if() ? predicate_transform(std::forward<T>(element)) : std::forward<T>(element);});
    }

    template <typename F1>
    constexpr auto operator()(_EXT boolean&& predicate_if, F1&& predicate_transform) const
    {
        // a transform_if adaptor works by transforming each element, if '_PredIf' is a true boolean value
        return ranges::actions::transform(
                [&predicate_if, predicate_transform = std::forward<F1>(predicate_transform)]<typename T>
                (T&& element) {return predicate_if ? predicate_transform(std::forward<T>(element)) : std::forward<T>(element);});
    }
};


template <typename T>
struct ranges::actions::cast_all_to_fn
{
    constexpr auto operator()(_EXT boolean&& remove_nullptr = true) const // TODO : apply parameter
    {
        return ranges::actions::transform([](auto* pointer) {return dynamic_cast<T>(pointer);}) | ranges::actions::remove(nullptr);
    }
};


struct ranges::actions::replace_fn
{
    template <typename T>
    constexpr auto operator()(T&& old_value, T&& new_value) const
    {
        return ranges::actions::transform(
                [old_value = std::forward<T>(old_value), new_value = std::forward<T>(new_value)]<typename U>
                (U&& current_value) mutable {return current_value == old_value ? std::forward<T>(new_value) : std::forward<U>(current_value);});
    }
};


struct ranges::actions::remove_at_index_fn
{
    constexpr auto operator()(_EXT number<size_t>&& r_index) const
    {
        return ranges::views::enumerate
                | ranges::actions::remove_if([r_index = r_index](auto&& pair) mutable {return pair.first == r_index;})
                | ranges::views::values;
    }
};


/* ALGORITHMS */
struct ranges::contains_any_fn
{
    template <typename R0, typename R1>
    constexpr auto operator()(R0&& range0, R1&& range1) const
    {
        return ranges::any_of(std::forward<R1>(range1),
                [range0 = std::forward<R0>(range0)]<typename T>(T&& item1) mutable
                {return ranges::contains(std::forward<R0>(range0), std::forward<T>(item1));});
    }
};


struct ranges::contains_all_fn
{
    template <typename R0, typename R1>
    constexpr auto operator()(R0&& range0, R1&& range1) const
    {
        return ranges::all_of(std::forward<R1>(range1),
                [range0 = std::forward<R0>(range0)]<typename T>(T&& item1) mutable
                {return ranges::contains(std::forward<R0>(range0), std::forward<T>(item1));});
    }
};


struct ranges::first_where_fn
{
    template <typename R, typename F>
    constexpr auto operator()(R&& range, F&& function) const
    {
        auto filtered = range | ranges::views::filter(std::forward<F>(function));
        return filtered.begin();
    }
};


struct ranges::last_where_fn
{
    template <typename R, typename F>
    constexpr auto operator()(R&& range, F&& function) const
    {
        auto filtered = range | ranges::views::filter(std::forward<F>(function));
        return filtered.end();
    }
};


namespace ranges::views {constexpr lowercase_fn lowercase;}
namespace ranges::views {constexpr uppercase_fn uppercase;}
namespace ranges::views {constexpr split_string_fn split_string;}
namespace ranges::views {constexpr take_until_fn take_until;}
namespace ranges::views {constexpr drop_until_fn drop_until;}
namespace ranges::views {constexpr transform_to_attr_fn transform_to_attr;}
namespace ranges::views {constexpr transform_if_fn transform_if;}
namespace ranges::views {template <typename T> constexpr transform_to_obj_fn<T> transform_to_obj;}
namespace ranges::views {template <typename T> constexpr cast_all_to_fn<T> cast_all_to;}
namespace ranges::views {template <filter_compare_t Comparison> constexpr filter_eq_fn<Comparison> filter_eq;}
namespace ranges::views {constexpr transpose_fn transpose;}
namespace ranges::views {constexpr remove_at_index_fn remove_at_index;}

namespace ranges::actions {constexpr lowercase_fn lowercase;}
namespace ranges::actions {constexpr uppercase_fn uppercase;}
namespace ranges::actions {constexpr transform_if_fn transform_if;}
namespace ranges::actions {template <typename T> constexpr cast_all_to_fn<T> cast_all_to;}
namespace ranges::actions {constexpr replace_fn replace;}
namespace ranges::actions {constexpr remove_at_index_fn remove_at_index;}

namespace ranges {constexpr contains_any_fn contains_any;}
namespace ranges {constexpr contains_all_fn contains_all;}
namespace ranges {constexpr first_where_fn first_where;}
namespace ranges {constexpr last_where_fn last_where;}


#endif //SBROWSER2_RANGES_HPP
