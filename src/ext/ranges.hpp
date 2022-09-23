#ifndef SBROWSER2_RANGES_HPP
#define SBROWSER2_RANGES_HPP

// TODO : add constraints to range views / actions / algorithms, like in range-v3 library.

#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/functional.hpp"
#include "ext/string.hpp"
#include "ext/type_traits.hpp"
#include "range/v3/action/remove_if.hpp"

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

namespace ranges::views {enum class filter_compare_t {EQ, NE, LT, LE, GT, GE};}


/* VIEWS */
namespace ranges::views
{
    // A lowercase conversion works by returning a transform adaptor that takes each item as a char type, converts
    // it to a lowercase char, and returns the character back.
    auto lowercase = []
    {
        return ranges::views::transform([](char c) {return std::tolower(c);});
    };


    // An uppercase conversion works by returning a transform adaptor that takes each item as a char type, converts
    // it to an uppercase char, and returns the character back.
    auto uppercase = []
    {
        return ranges::views::transform([](char c) {return std::toupper(c);});
    };


    // A string split function works by returning a split-transform adaptor that splits the range by the delimiter;
    // this produces a range of ranges: splitting "hello world" by a " " becomes {{"h", "e", "l", "l", "o"}, {"0",
    // "o", "r", "l", "d"}}, with each item a character from the string, so using the transform adaptor, convert
    // each sub-range into a string, to get {"hello", "world"}.
    auto split_string = [](char delimiter)
    {
        return ranges::views::split(delimiter) | ranges::views::transform([](range_v3_view auto&& sub_range) {return sub_range | ranges::to<_EXT string>();});
    };


    // A take_until adaptor works by taking items from a range until a condition is met -- semantically the same as
    // take_while, but allowing the opposite method; for example, instead of
    // `take_while([](int i){... return !odd_number(i);}`, it can be written as `take_until(odd_number);`.
    auto take_until = []<typename F>(F&& predicate)
    {
        return ranges::views::take_while(
                [predicate = std::forward<F>(predicate)]<callable T>(T&& element) mutable
                {return !predicate(std::forward<T>(element));});
    };


    // A drop_until adaptor works by dropping items from a range until a condition is met -- semantically the same as
    // drop_while, but allowing the opposite method; for example, instead of
    // `drop_while([](int i){... return !odd_number(i);}`, it can be written as `drop_until(odd_number);`.
    auto drop_until = []<callable F>(F&& predicate)
    {
        return ranges::views::drop_while(
                [predicate = std::forward<F>(predicate)]<typename T>(T&& element) mutable
                {return !predicate(std::forward<T>(element));});
    };


    // Transform a container of objects into an attribute belonging to that object -- syntactic sugar for
    //      ranges::views::transform(nodes, [](dom::nodes::node* node) {return node->text_content();});
    //      ranges::views::transform_to_attr(nodes, &node::text_content);
    // NOTE: this is only for ext::property<T>, not normal attributes -- TODO: specialize for this
    auto transform_to_attr = []<typename T>(T&& attribute)
    {
        return ranges::views::transform(
                [attribute = std::forward<T>(attribute)]<typename U>(U&& element) mutable
                {return std::mem_fn(std::forward<T>(attribute))(std::forward<U>(element));});};


    // A transform_if adaptor works by transforming each element, if it matches a method passed in as the 'PredIf'
    // statement. The return type of the '_PredTransform' method must be the same as the current element type in the
    // container / view, as there is no guarantee that very element will be transformed, so some elements will be
    // left in their original form. A transform_if adaptor works by transforming each element, if '_PredIf' is a true
    // boolean value.
    auto transform_if = []<typename F0, callable F1>(F0&& predicate_if, F1&& predicate_transform)
    {
        if constexpr (callable<F0>)
            return ranges::views::transform(
                    [predicate_if = std::forward<F0>(predicate_if), predicate_transform = std::forward<F1>(predicate_transform)]<typename T>(T&& element) mutable
                    {return predicate_if() ? predicate_transform(std::forward<T>(element)) : std::forward<T>(element);});
        else
            return ranges::views::transform(
                    [&predicate_if, predicate_transform = std::forward<F1>(predicate_transform)]<typename T>(T&& element) mutable
                    {return predicate_if ? predicate_transform(std::forward<T>(element)) : std::forward<T>(element);});
    };


    auto transform_to_obj = []<typename T, typename ...Args>(Args&&... other_args)
    {
        return ranges::views::transform(
                [...other_args = std::forward<Args...>(other_args)]<typename U>(U&& arg) mutable
                {
                    if constexpr (std::is_pointer_v<T>)
                        return new T{std::forward<U>(arg), std::forward<Args>(other_args)...};
                    else
                        return T{std::forward<U>(arg), std::forward<Args>(other_args)...};
                });
    };


    // A cast_to_all adaptor works by taking a type, and dynamically casting all the elements in the range to
    // another type, and then removing all the instances of nullptr.
    auto cast_all_to = []<typename T>(_EXT boolean&& remove_nullptr = true)
    {
        return ranges::views::transform([](auto* pointer) {return dynamic_cast<T>(pointer);}) | ranges::views::remove(nullptr);
    };


    // A filter that allows for comparison of an attribute or method call from each object in the range; for
    // example, the first line is simplified into the second line (syntactic sugar)
    //      elements = node->children() | ranges::views::filter([](node* child) {return child->node_type == node::ELEMENT_NODE;};
    //      elements = node->children() | ranges::views::filter<EQ>(&node::node_type, node::ELEMENT_NODE);
    auto filter_eq = []<ranges::views::filter_compare_t Comparison, typename T, typename U, typename F>(T&& attribute, U&& value, F&& predicate = _EXT identity{})
    {
        using enum filter_compare_t;

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
    };


    auto transpose = []
    {
        return ranges::views::transform(
                []<template <typename> typename Container, typename T>(Container<T>&)
                {}); // TODO
    };


    auto remove_at_index = [](_EXT number<size_t>&& r_index)
    {
        return ranges::views::enumerate
                | ranges::views::remove_if([r_index = r_index](auto&& pair) mutable {return pair.first == r_index;})
                | ranges::views::values;
    };
}


/* ACTIONS */
namespace ranges::actions
{
    auto lowercase = []
    {
        return ranges::actions::transform([](char c) {return std::tolower(c);});
    };

    auto uppercase = []
    {
        return ranges::actions::transform([](char c) {return std::toupper(c);});
    };


    // A transform_if adaptor works by transforming each element, if it matches a method passed in as the 'PredIf'
    // statement. The return type of the '_PredTransform' method must be the same as the current element type in the
    // container / view, as there is no guarantee that very element will be transformed, so some elements will be
    // left in their original form. A transform_if adaptor works by transforming each element, if '_PredIf' is a true
    // boolean value.
    auto transform_if = []<typename F0, callable F1>(F0&& predicate_if, F1&& predicate_transform)
    {
        if constexpr (callable<F0>)
            return ranges::actions::transform(
                    [predicate_if = std::forward<F0>(predicate_if), predicate_transform = std::forward<F1>(predicate_transform)]<typename T>(T&& element) mutable
                    {return predicate_if() ? predicate_transform(std::forward<T>(element)) : std::forward<T>(element);});
        else
            return ranges::actions::transform(
                    [&predicate_if, predicate_transform = std::forward<F1>(predicate_transform)]<typename T>(T&& element) mutable
                    {return predicate_if ? predicate_transform(std::forward<T>(element)) : std::forward<T>(element);});
    };


    // A cast_to_all adaptor works by taking a type, and dynamically casting all the elements in the range to
    // another type, and then removing all the instances of nullptr.
    auto cast_all_to = []<typename T>(_EXT boolean&& remove_nullptr = true)
    {
        return ranges::actions::transform([](auto* pointer) {return dynamic_cast<T>(pointer);}) | ranges::views::remove(nullptr);
    };


    auto replace = []<typename T, callable F>(T&& old_value, T&& new_value, F&& predicate = _EXT identity{}) mutable
    {
        return ranges::actions::transform(
                [old_value = std::forward<T>(old_value), new_value = std::forward<T>(new_value), predicate = std::forward<F>(predicate)]<typename U>(U&& current_value) mutable
                {return predicate(current_value) == old_value ? std::forward<T>(new_value) : std::forward<U>(current_value);});
    };


    auto replace_if = []<callable F, typename T>(F&& pred, T&& new_value)
    {
        return ranges::actions::transform(
                [pred = std::forward<F>(pred), new_value = std::forward<T>(new_value)]<typename U>(U&& current_value) mutable
                {return pred(std::forward<U>(current_value)) ? std::forward<T>(new_value) : std::forward<U>(current_value);});
    };


    auto remove_at_index = [](_EXT number<size_t>&& r_index)
    {
        return ranges::views::enumerate
                | ranges::actions::remove_if([r_index = r_index](auto&& pair) mutable {return pair.first == r_index;})
                | ranges::views::values;
    };

    auto filter = []<callable F>(F&& predicate)
    {
        return ranges::actions::remove_if(_EXT negate_function{std::move(predicate)});
    };
}


/* ALGORITHMS */
namespace ranges
{
    auto contains_any_fn = []<typename R0, typename R1>(R0&& range0, R1&& range1)
    {
        return ranges::any_of(std::forward<R1>(range1),
                [range0 = std::forward<R0>(range0)]<typename T>(T&& item1) mutable
                {return ranges::contains(std::forward<R0>(range0), std::forward<T>(item1));});
    };


    auto contains_all = []<typename R0, typename R1>(R0&& range0, R1&& range1)
    {
        return ranges::all_of(std::forward<R1>(range1),
                [range0 = std::forward<R0>(range0)]<typename T>(T&& item1) mutable
                {return ranges::contains(std::forward<R0>(range0), std::forward<T>(item1));});
    };


    auto first_where = []<typename R, callable F>(R&& range, F&& pred)
    {
        auto filtered = range | ranges::views::filter(std::forward<F>(pred));
        return filtered.begin();
    };


    auto last_where = []<typename R, typename F>(R&& range, F&& function)
    {
        auto filtered = range | ranges::views::filter(std::forward<F>(function));
        return filtered.end();
    };
};


#endif //SBROWSER2_RANGES_HPP
