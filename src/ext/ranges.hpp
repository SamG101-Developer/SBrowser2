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

#include <range/v3/view/any_view.hpp>
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

#define RANGE_ADAPTOR_OPERATOR(...) \
    constexpr auto operator()(__VA_ARGS__) const

#define RANGE_ADAPTOR_STRUCT(name, code) \
    struct name##_fn {code};             \
    auto name = name##_fn{}

#define RANGE_ADAPTOR_STRUCT_T(name, templates, code) \
    template <templates>                              \
    struct name##_fn {code};                          \
    template <templates>


namespace ranges {enum class filter_compare_t {EQ, NE, LT, LE, GT, GE};}


/* VIEWS */
namespace ranges::views
{
    // A lowercase conversion works by returning a transform adaptor that takes each item as a char type, converts
    // it to a lowercase char, and returns the character back.
    RANGE_ADAPTOR_STRUCT(lowercase,
        RANGE_ADAPTOR_OPERATOR()
        {return ranges::views::transform([](char c) {return std::tolower(c);});});


    // An uppercase conversion works by returning a transform adaptor that takes each item as a char type, converts
    // it to an uppercase char, and returns the character back.
    RANGE_ADAPTOR_STRUCT(uppercase,
        RANGE_ADAPTOR_OPERATOR()
        {return ranges::views::transform([](char c) {return std::toupper(c);});});


    // A string split function works by returning a split-transform adaptor that splits the range by the delimiter;
    // this produces a range of ranges: splitting "hello world" by a " " becomes {{"h", "e", "l", "l", "o"}, {"0",
    // "o", "r", "l", "d"}}, with each item a character from the string, so using the transform adaptor, convert
    // each sub-range into a string, to get {"hello", "world"}.
    RANGE_ADAPTOR_STRUCT(split_string,
        RANGE_ADAPTOR_OPERATOR(char delimiter) // TOOD : ...Args -> allow multiple delimiters
        {
            return ranges::views::split(delimiter) | ranges::views::transform(
                    [](_EXT range_v3_view auto&& sub_range)
                    {return sub_range | ranges::to<_EXT string>();});
        });


    // A take_until adaptor works by taking items from a range until a condition is met -- semantically the same as
    // take_while, but allowing the opposite method; for example, instead of
    // `take_while([](int i){... return !odd_number(i);}`, it can be written as `take_until(odd_number);`.
    RANGE_ADAPTOR_STRUCT(take_until,
        template <_EXT callable F>
        RANGE_ADAPTOR_OPERATOR(F&& predicate)
        {
            return ranges::views::take_while(
                    [f = std::forward<F>(predicate)]<_EXT callable T>(T&& element) mutable
                    {return !f(std::forward<T>(element));});
        });


    // A drop_until adaptor works by dropping items from a range until a condition is met -- semantically the same as
    // drop_while, but allowing the opposite method; for example, instead of
    // `drop_while([](int i){... return !odd_number(i);}`, it can be written as `drop_until(odd_number);`.
    RANGE_ADAPTOR_STRUCT(drop_until,
        template <_EXT callable F>
        RANGE_ADAPTOR_OPERATOR(F&& predicate)
        {
            return ranges::views::drop_while(
                    [f = std::forward<F>(predicate)]<typename T>(T&& element) mutable
                    {return !f(std::forward<T>(element));});
        });


    // Transform a container of objects into an attribute belonging to that object -- syntactic sugar for
    //      ranges::views::transform(nodes, [](dom::nodes::node* node) {return node->text_content();});
    //      ranges::views::transform_to_attr(nodes, &node::text_content);
    // For mapping a object to multiple attributes, a tuple is returned, contianing all the attrbute values.
    RANGE_ADAPTOR_STRUCT(transform_to_attr,
        template <typename T>
        RANGE_ADAPTOR_OPERATOR(T&& attribute)
        {
            return ranges::views::transform(
                    [attribute = std::forward<T>(attribute)]<typename U>(U&& element) mutable
                    {return std::mem_fn(std::forward<T>(attribute))(std::forward<U>(element));});
        }

        template <typename ...Args>
        RANGE_ADAPTOR_OPERATOR(Args&&... attributes)
        {
            return ranges::views::transform(
                    [...attributes = std::forward<Args>(attributes)]<typename U>(U&& element) mutable
                    {return std::make_tuple(std::mem_fn(std::forward<Args>(attributes))(std::forward<U>(element))...);});
        });


    // A transform_if adaptor works by transforming each element, if it matches a method passed in as the 'PredIf'
    // statement. The return type of the '_PredTransform' method must be the same as the current element type in the
    // container / view, as there is no guarantee that very element will be transformed, so some elements will be
    // left in their original form. A transform_if adaptor works by transforming each element, if '_PredIf' is a true
    // boolean value.
    RANGE_ADAPTOR_STRUCT(transform_if,
        template <_EXT callable F0 COMMA _EXT callable F1>
        RANGE_ADAPTOR_OPERATOR(F0&& predicate_if, F1&& predicate_transform)
        {
            return predicate_if()
                    ? ranges::views::transform([f = std::forward<F1>(predicate_transform)]<typename T>(T&& element) mutable {return f(std::forward<T>(element));})
                    : ranges::views::transform(_EXT identity{});
        }

        template <_EXT callable F>
        RANGE_ADAPTOR_OPERATOR(_EXT boolean predicate_if, F&& predicate_transform)
        {
            return predicate_if
                    ? ranges::views::transform([f = std::forward<F>(predicate_transform)]<typename T>(T&& element) mutable {f(std::forward<T>(element));})
                    : ranges::views::transform(_EXT identity{});
        });


    RANGE_ADAPTOR_STRUCT(transform_to_object,
        template <typename T COMMA typename ...Args>
        RANGE_ADAPTOR_OPERATOR(Args&&... other_args)
        {
            return ranges::views::transform(
                    [...other_args = std::forward<Args...>(other_args)]<typename U>(U&& arg) mutable
                    {
                        constexpr_return_if(_EXT is_unique<T>) std::make_unique<T>(std::forward<U>(arg), std::forward<Args>(other_args)...);
                        constexpr_return_if(std::is_pointer_v<T>) new T{std::forward<U>(arg), std::forward<Args>(other_args)...};
                        return T{std::forward<U>(arg), std::forward<Args>(other_args)...};
                    });
        });


    // A cast_to_all adaptor works by taking a type, and dynamically casting all the elements in the range to
    // another type, and then removing all the instances of nullptr.
    RANGE_ADAPTOR_STRUCT_T(cast_all_to, _EXT is_pointer T,
        RANGE_ADAPTOR_OPERATOR(_EXT boolean&& remove_nullptr = true)
        {
            return ranges::views::transform([](auto* pointer) {return dynamic_cast<T>(pointer);}) | ranges::views::remove(nullptr);
        })
        auto cast_all_to = cast_all_to_fn<T>{};


    // A filter that allows for comparison of an attribute or method call from each object in the range; for
    // example, the first line is simplified into the second line (syntactic sugar)
    //      elements = node->children() | ranges::views::filter([](node* child) {return child->node_type == node::ELEMENT_NODE;};
    //      elements = node->children() | ranges::views::filter<EQ>(&node::node_type, node::ELEMENT_NODE);
    RANGE_ADAPTOR_STRUCT_T(filter_eq, filter_compare_t Comparison = filter_compare_t::EQ,
        template <typename T COMMA typename U COMMA typename F>
        RANGE_ADAPTOR_OPERATOR(T&& attribute, U&& value, F&& predicate = _EXT identity{})
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
        }) auto filter_eq = filter_eq_fn<Comparison>{};


    RANGE_ADAPTOR_STRUCT_T(transformed_filter, filter_compare_t Comparison = filter_compare_t::EQ,
        template <typename F COMMA typename T>
        RANGE_ADAPTOR_OPERATOR(F&& function, T&& value)
        {
            using enum filter_compare_t;

            constexpr_return_if(Comparison == EQ) ranges::views::filter(
                    [function = std::forward<F>(function), value = std::forward<T>(value)]<typename U>
                    (U&& candidate) mutable {return function(std::forward<U>(candidate)) == std::forward<T>(value);});

            constexpr_return_if(Comparison == NE) ranges::views::filter(
                    [function = std::forward<F>(function), value = std::forward<T>(value)]<typename U>
                    (U&& candidate) mutable {return function(std::forward<U>(candidate)) != std::forward<T>(value);});

            // TODO ...
        }) auto transformed_filter = transformed_filter_fn<Comparison>{};


    RANGE_ADAPTOR_STRUCT(transpose,
        RANGE_ADAPTOR_OPERATOR()
        {
            return ranges::views::transform(
                    []<template <typename> typename Container, typename T>(Container<T>&&)
                    {}); // TODO
        });


    RANGE_ADAPTOR_STRUCT(remove_at_index,
        RANGE_ADAPTOR_OPERATOR(_EXT number<size_t> r_index)
        {
            return ranges::views::enumerate
                    | ranges::views::remove_if([r_index = r_index](auto&& pair) mutable {return pair.first == r_index;})
                    | ranges::views::values;
        });
}


/* ACTIONS */
namespace ranges::actions
{
    RANGE_ADAPTOR_STRUCT(lowercase,
            RANGE_ADAPTOR_OPERATOR()
            {return ranges::actions::transform([](char c) {return std::tolower(c);});});

    RANGE_ADAPTOR_STRUCT(uppercase,
            RANGE_ADAPTOR_OPERATOR()
            {return ranges::actions::transform([](char c) {return std::toupper(c);});});

    RANGE_ADAPTOR_STRUCT(replace,
            template <typename T COMMA _EXT callable F>
            RANGE_ADAPTOR_OPERATOR(T&& old_value, T&& new_value, F&& predicate = _EXT identity{})
            {
                return ranges::actions::transform(
                        [old_value = std::forward<T>(old_value), new_value = std::forward<T>(new_value), f = std::forward<F>(predicate)](T&& current_value) mutable
                        {return f(std::forward<T>(current_value)) == std::forward<T>(old_value) ? std::forward<T>(new_value) : std::forward<T>(current_value);});
            });

    RANGE_ADAPTOR_STRUCT(replace_if,
            template <_EXT callable F COMMA typename T>
            RANGE_ADAPTOR_OPERATOR(F&& pred, T&& new_value)
            {
                return ranges::actions::transform(
                        [f = std::forward<F>(pred), new_value = std::forward<T>(new_value)](T&& current_value) mutable
                        {return f(std::forward<T>(current_value)) ? std::forward<T>(new_value) : std::forward<T>(current_value);});
            });


    RANGE_ADAPTOR_STRUCT(remove_at_index,
            RANGE_ADAPTOR_OPERATOR(_EXT number<size_t>&& r_index)
            {
                return ranges::views::enumerate
                        | ranges::actions::remove_if(BIND_FRONT(_EXT pair_key_matches, r_index))
                        | ranges::views::values;
            });

    RANGE_ADAPTOR_STRUCT(filter,
            template <_EXT callable F>
            RANGE_ADAPTOR_OPERATOR(F&& predicate)
            {return ranges::actions::remove_if(_EXT negate_function{std::move(predicate)});});
}


/* ALGORITHMS */
namespace ranges
{
    RANGE_ADAPTOR_STRUCT(contains_any,
            template <typename R0 COMMA typename R1>
            RANGE_ADAPTOR_OPERATOR(R0&& range0, R1&& range1)
            {
                return ranges::any_of(std::forward<R1>(range1),
                        [range0 = std::forward<R0>(range0)]<typename T>(T&& item1) mutable
                        {return ranges::contains(std::forward<R0>(range0), std::forward<T>(item1));});
            });


    RANGE_ADAPTOR_STRUCT(contains_all,
            template <typename R0 COMMA typename R1>
            RANGE_ADAPTOR_OPERATOR(R0&& range0, R1&& range1)
            {
                return ranges::all_of(std::forward<R1>(range1),
                        [range0 = std::forward<R0>(range0)]<typename T>(T&& item1) mutable
                        {return ranges::contains(std::forward<R0>(range0), std::forward<T>(item1));});
            });


    RANGE_ADAPTOR_STRUCT(negate_contains,
            template <typename R COMMA typename T>
            RANGE_ADAPTOR_OPERATOR(R&& range, T&& value)
            {return !ranges::contains(std::forward<R>(range), std::forward<T>(value));});


    RANGE_ADAPTOR_STRUCT(first_where,
            template <typename R COMMA _EXT callable F>
            RANGE_ADAPTOR_OPERATOR(R&& range, F&& pred)
            {return ranges::begin(range | ranges::views::filter(std::forward<F>(pred)));});


    RANGE_ADAPTOR_STRUCT(last_where,
            template <typename R COMMA typename F>
            RANGE_ADAPTOR_OPERATOR(R&& range, F&& function)
            {return ranges::end(range | ranges::views::filter(std::forward<F>(function)));});
}


/* OTHER */
namespace ranges
{
    template <category C = category::input, typename ...Args>
    auto make_any_view(Args&&... args) -> any_view<_EXT nth_variadic_type_t<0, Args...>, C>;

    template <typename Ref, ranges::category C = ranges::category::none>
    using any_helpful_view = ranges::any_view<Ref, ranges::category::forward | ranges::category::sized | C>;
}


#endif //SBROWSER2_RANGES_HPP
