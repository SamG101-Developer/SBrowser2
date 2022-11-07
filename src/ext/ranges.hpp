#ifndef SBROWSER2_RANGES_HPP
#define SBROWSER2_RANGES_HPP

// TODO : add constraints to range views / actions / algorithms, like in range-v3 library.
// TODO : comment MACROS

#include "ext/boolean.hpp"
#include "ext/casting.hpp"
#include "ext/concepts.hpp"
#include "ext/functional.hpp"
#include "ext/pair.hpp"
#include "ext/string.hpp"
#include "ext/type_traits.hpp"
#include "ext/variadic.hpp"

#include <range/v3/range/conversion.hpp>

#include <range/v3/action.hpp>
#include <range/v3/action/remove.hpp>
#include <range/v3/action/remove_if.hpp>
#include <range/v3/action/transform.hpp>

#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/contains.hpp>

#include <range/v3/view/any_view.hpp>
#include <range/v3/view/drop_while.hpp>
#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/map.hpp>
#include <range/v3/view/remove.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/take_while.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/view.hpp>


#define RANGE_VIEW_STRUCT(name, code) \
    struct name##_fn {code};          \
    RANGES_INLINE_VARIABLE(name##_fn, name)

#define RANGE_VIEW_STRUCT_T(name, code) \
    struct name##_fn {code};

#define RANGE_ACTION_STRUCT(name, code) \
    struct name##_fn {code};            \
    RANGES_INLINE_VARIABLE(name##_fn, name)

#define RANGE_VIEW_CLOSURE_STRUCT(name, code) \
    struct name##_fn {code};                  \
    RANGES_INLINE_VARIABLE(view_closure<name##_fn>, name)

#define RANGE_VIEW_CLOSURE_STRUCT_T(name, code) \
    struct name##_fn {code};

#define RANGE_ACTION_CLOSURE_STRUCT(name, code) \
    struct name##_fn {code};                    \
    RANGES_INLINE_VARIABLE(action_closure<name##_fn>, name)

#define RANGE_ACTION_CLOSURE_STRUCT_T(name, code) \
    struct name##_fn {code};

#define RANGE_ALGORITHM_STRUCT(name, code) \
    RANGES_FUNC_BEGIN(name)                \
        code                               \
    RANGES_FUNC_END(name)


namespace ranges {enum class filter_compare_t {EQ, NE, LT, LE, GT, GE};}


/* TRAITS */
namespace ranges
{
    template <typename Rng>
    struct range_traits
    {
        using iterator_type = decltype(ranges::any_view(std::declval<Rng>()).begin());
        using value_type = typename iterator_type::value_type;
    };

    template <typename Rng>
    using lowercase_view = transform_view<Rng, decltype(_EXT to_lower)>;

    template <typename Rng>
    using uppercase_view = transform_view<Rng, decltype(_EXT to_upper)>;

    template <typename Rng, typename T>
    using cast_view = transform_view<Rng, _EXT function<T(typename range_traits<Rng>::value_type)>>;

    template <typename Rng>
    using underlying_view = transform_view<Rng, _EXT function<typename range_traits<Rng>::value_type::pointer()>>;

    template <typename Rng>
    using transpose_view = transform_view<Rng, decltype(_EXT identity)>;
}


/* VIEWS */
namespace ranges::views
{
    // A lowercase conversion works by returning a transform adaptor that takes each item as a char type, converts
    // it to a lowercase char, and returns the character back.
    RANGE_VIEW_CLOSURE_STRUCT(lowercase,
            template <typename Rng>
            auto operator()(Rng&& rng) const -> lowercase_view<all_t<Rng>>
            {return {all(std::forward<Rng>(rng)) COMMA _EXT to_lower};})


    // An uppercase conversion works by returning a transform adaptor that takes each item as a char type, converts
    // it to an uppercase char, and returns the character back.
    RANGE_VIEW_CLOSURE_STRUCT(uppercase,
            template <typename Rng>
            auto operator()(Rng&& rng) const -> uppercase_view<all_t<Rng>>
            {return {all(std::forward<Rng>(rng)) COMMA _EXT to_upper};})


    // A string split function works by returning a split-transform adaptor that splits the range by the delimiter;
    // this produces a range of ranges: splitting "hello world" by a " " becomes {{"h", "e", "l", "l", "o"}, {"0",
    // "o", "r", "l", "d"}}, with each item a character from the string, so using the transform adaptor, convert
    // each sub-range into a string, to get {"hello", "world"}.
    RANGE_VIEW_STRUCT(split_string,
            template <_EXT type_is<char> ...Args>
            constexpr auto operator()(Args... delimiter) const // NOTE: deliberately not Args&&...
            {return (ranges::views::split(delimiter) | ...) | ranges::views::transform(ranges::to<_EXT string>);})


    // A take_until adaptor works by taking items from a range until a condition is met -- semantically the same as
    // take_while, but allowing the opposite method; for example, instead of
    // `take_while([](int i){... return !odd_number(i);}`, it can be written as `take_until(odd_number);`.
    RANGE_VIEW_STRUCT(take_until,
            template <_EXT callable F>
            constexpr auto operator()(F&& pred) const
            {return ranges::views::take_while(_EXT negate_function{std::forward<F>(pred)});})


    // A drop_until adaptor works by dropping items from a range until a condition is met -- semantically the same as
    // drop_while, but allowing the opposite method; for example, instead of
    // `drop_while([](int i){... return !odd_number(i);}`, it can be written as `drop_until(odd_number);`.
    RANGE_VIEW_STRUCT(drop_until,
            template <_EXT callable F>
            constexpr auto operator()(F&& pred) const
            {return ranges::views::drop_while(_EXT negate_function{std::forward<F>(pred)});})


    // Transform a container of objects into an attribute belonging to that object -- syntactic sugar for
    //      ranges::views::transform(nodes, [](dom::nodes::node* node) {return node->text_content();});
    //      ranges::views::transform_to_attr(nodes, &node::text_content);
    // For mapping a object to multiple attributes, a tuple is returned, containing all the attribute values.
    RANGE_VIEW_STRUCT(transform_to_attr,
            template <typename Attr COMMA _EXT callable F>
            constexpr auto operator()(Attr&& attr, F&& proj = _EXT identity) const
            {
        return ranges::views::transform(
                [attr = std::forward<Attr>(attr), f = std::forward<F>(proj)]<typename U>(U&& element) mutable
                {return std::mem_fn(std::forward<Attr>(attr))(f(std::forward<U>(element)));});
            }

            template <typename ...Attrs COMMA _EXT callable F>
            constexpr auto operator()(Attrs&&... attrs, F&& proj) const
            {
        return ranges::views::transform(
                [...attrs = std::forward<Attrs>(attrs), f = std::forward<F>(proj)]<typename U>(U&& element) mutable
                {return _EXT make_tuple(std::mem_fn(std::forward<Attrs>(attrs))(f(std::forward<U>(element)))...);});
            })


    // A transform_if adaptor works by transforming each element, if it matches a method passed in as the 'PredIf'
    // statement. The return type of the '_PredTransform' method must be the same as the current element type in the
    // container / view, as there is no guarantee that very element will be transformed, so some elements will be
    // left in their original form. A transform_if adaptor works by transforming each element, if '_PredIf' is a true
    // boolean value.
    RANGE_VIEW_STRUCT(transform_if,
            template <_EXT callable F0 COMMA _EXT callable F1>
            constexpr auto operator()(F0&& pred_if, F1&& pred_transform) const
            {
        decltype(auto) pred = pred_if() ? std::forward<F1>(pred_transform) : _EXT identity;
        return ranges::views::transform(std::move(pred));
            }

            template <_EXT callable F>
            constexpr auto operator()(_EXT boolean pred_if, F&& pred_transform) const
            {
        decltype(auto) pred = pred_if ? std::forward<F>(pred_transform) : _EXT identity;
        return ranges::views::transform(std::move(pred));
            })


    RANGE_VIEW_STRUCT(transform_to_object,
            template <typename T COMMA typename ...Args>
            constexpr auto operator()(Args&&... other_args) const
            {
        return ranges::views::transform(
                [...other_args = std::forward<Args...>(other_args)]<typename U>(U&& arg) mutable
                {
            static_assert (!_EXT is_pointer<T>, "Use a smart pointer or regular object ('new' not permitted)");
            if constexpr(_EXT is_unique<T>) return std::make_unique<T>(std::forward<U>(arg), std::forward<Args>(other_args)...);
            else return T{std::forward<U>(arg), std::forward<Args>(other_args)...};
                });
            })


    // A cast_to_all adaptor works by taking a type, and dynamically casting all the elements in the range to
    // another type, and then removing all the instances of nullptr.
    template <_EXT is_pointer T>
    RANGE_VIEW_CLOSURE_STRUCT_T(cast,
            template <typename Rng>
            auto operator()(Rng&& rng) const -> cast_view<all_t<Rng> COMMA T>
            {return {all(std::forward<Rng>(rng)) COMMA dom_cast<T>};}) // TODO | ranges::views::remove(nullptr)
    template <_EXT is_pointer T>
    inline constexpr auto cast = view_closure<cast_fn<T>>{};


    RANGE_VIEW_CLOSURE_STRUCT(underlying,
            template <typename Rng>
            auto operator()(Rng&& rng) const -> underlying_view<all_t<Rng>>
            {return {all(std::forward<Rng>(rng)) COMMA range_traits<Rng>::value_type::get};})


    // A filter that allows for comparison of an attribute or method call from each object in the range; for
    // example, the first line is simplified into the second line (syntactic sugar)
    //      elements = node->children() | ranges::views::filter([](node* child) {return child->node_type == node::ELEMENT_NODE;};
    //      elements = node->children() | ranges::views::filter<EQ>(&node::node_type, node::ELEMENT_NODE);
    template <filter_compare_t Comparison = filter_compare_t::EQ>
    RANGE_VIEW_STRUCT_T(filter_eq,
            template <typename Attr COMMA typename T COMMA typename F>
            constexpr auto operator()(Attr&& attribute, T&& value, F&& proj = _EXT identity) const // TODO -> Attr to general typename (for any method), then specialiaze is_member_function for Attr
            {
        using enum filter_compare_t;

        constexpr_return_if(Comparison == EQ) ranges::views::filter(
                [attribute = std::forward<Attr>(attribute), value = std::forward<T>(value), f = std::forward<F>(proj)]<typename V>
                (V&& candidate) mutable {return std::mem_fn(std::forward<Attr>(attribute)(f(std::forward<V>(candidate)))) == std::forward<T>(value);});

        else constexpr_return_if(Comparison == NE) ranges::views::filter(
                [attribute = std::forward<Attr>(attribute), value = std::forward<T>(value), f = std::forward<F>(proj)]<typename V>
                (V&& candidate) mutable {return std::mem_fn(std::forward<Attr>(attribute)(f(std::forward<V>(candidate)))) != std::forward<T>(value);});

        else constexpr_return_if(Comparison == LT) ranges::views::filter(
                [attribute = std::forward<Attr>(attribute), value = std::forward<T>(value), f = std::forward<F>(proj)]<typename V>
                (V&& candidate) mutable {return std::mem_fn(std::forward<Attr>(attribute)(f(std::forward<V>(candidate)))) < std::forward<T>(value);});

        else constexpr_return_if(Comparison == LE) ranges::views::filter(
                [attribute = std::forward<Attr>(attribute), value = std::forward<T>(value), f = std::forward<F>(proj)]<typename V>
                (V&& candidate) mutable {return std::mem_fn(std::forward<Attr>(attribute)(f(std::forward<V>(candidate)))) <= std::forward<T>(value);});

        else constexpr_return_if(Comparison == GT) ranges::views::filter(
                [attribute = std::forward<Attr>(attribute), value = std::forward<T>(value), f = std::forward<F>(proj)]<typename V>
                (V&& candidate) mutable {return std::mem_fn(std::forward<Attr>(attribute)(f(std::forward<V>(candidate)))) > std::forward<T>(value);});

        else constexpr_return_if(Comparison == GE) ranges::views::filter(
                [attribute = std::forward<Attr>(attribute), value = std::forward<T>(value), f = std::forward<F>(proj)]<typename V>
                (V&& candidate) mutable {return std::mem_fn(std::forward<Attr>(attribute)(f(std::forward<V>(candidate)))) >= std::forward<T>(value);});
            })
    template <filter_compare_t Comparison>
    inline constexpr auto filter_eq = filter_eq_fn<Comparison>{};


    RANGE_VIEW_CLOSURE_STRUCT(transpose,
            template <typename Rng>
            constexpr auto operator()(Rng&& rng) const -> transpose_view<all_t<Rng>>
            {return {all(std::forward<Rng>(rng)) COMMA _EXT identity};}) // TODO : impl with ranges::views::elements<N>(...)


    RANGE_VIEW_STRUCT(remove_at_index,
            constexpr auto operator()(_EXT number<size_t> r_index) const
            {
        return ranges::views::enumerate
                | ranges::views::remove_if(BIND_BACK(_EXT pair_key_matches, r_index))
                | ranges::views::values;
            })

    RANGE_VIEW_STRUCT(for_each_if,
            template <_EXT callable F COMMA _EXT callable T COMMA _EXT callable U>
            constexpr auto operator()(F&& predicate, T&& truth_function, U&& false_function) const
            {
        return predicate()
                ? ranges::views::for_each(std::forward<T>(truth_function))
                : ranges::views::for_each(std::forward<U>(false_function));
            })

    RANGE_VIEW_STRUCT(parse_csv,
            constexpr auto operator()() const
            {
        return ranges::views::transform(BIND_BACK(ranges::views::split, ','))
                | ranges::views::transform([](auto&& pair) {return _EXT make_pair(std::move(pair.front()), std::move(pair.back()));});
            })
}


/* ACTIONS */
namespace ranges::actions
{
    RANGE_ACTION_CLOSURE_STRUCT(lowercase,
            constexpr auto operator()() const
            {return ranges::actions::transform(_EXT to_lower);})

    RANGE_ACTION_CLOSURE_STRUCT(uppercase,
            constexpr auto operator()() const
            {return ranges::actions::transform(_EXT to_upper);})

    RANGE_ACTION_STRUCT(replace,
            template <typename T COMMA _EXT callable F>
            constexpr auto operator()(T&& old_value, T&& new_value, F&& proj = _EXT identity) const
            {
        return ranges::actions::transform(
                [old_value = std::forward<T>(old_value), new_value = std::forward<T>(new_value), f = std::forward<F>(proj)](T&& current_value) mutable
                {return f(std::forward<T>(current_value)) == std::forward<T>(old_value) ? std::forward<T>(new_value) : std::forward<T>(current_value);});
            })

    RANGE_ACTION_STRUCT(replace_if,
            template <_EXT callable F COMMA typename T>
            constexpr auto operator()(F&& pred, T&& new_value) const
            {
        return ranges::actions::transform(
                [f = std::forward<F>(pred), new_value = std::forward<T>(new_value)](T&& current_value) mutable
                {return f(std::forward<T>(current_value)) ? std::forward<T>(new_value) : std::forward<T>(current_value);});
            })

    RANGE_ACTION_STRUCT(remove_at_index,
            constexpr auto operator()(_EXT number<size_t> r_index) const
            {
        return ranges::views::enumerate
                | ranges::actions::remove_if(BIND_FRONT(_EXT pair_key_matches, r_index))
                | ranges::views::values;
            })

    RANGE_ACTION_STRUCT(filter,
            template <_EXT callable F>
            constexpr auto operator()(F&& pred) const
            {return ranges::actions::remove_if(_EXT negate_function{std::forward<F>(pred)});})

    template <_EXT is_pointer T>
    RANGE_ACTION_CLOSURE_STRUCT_T(cast,
            template <typename Rng>
            auto operator()(Rng&& rng) const -> Rng
            {return {all(std::forward<Rng>(rng)) COMMA dom_cast<T>};}) // TODO | ranges::views::remove(nullptr)
    template <_EXT is_pointer T>
    inline constexpr auto cast = action_closure<cast_fn<T>>{};

    RANGE_ACTION_STRUCT(remove_key,
            template <typename K COMMA _EXT callable F>
            constexpr auto operator()(K&& key, F&& proj = _EXT identity) const
            {
        return ranges::make_action_closure(BIND_BACK(remove_key_fn{}, std::forward<K>(key), std::forward<F>(proj)));
            }

            template <typename Rng COMMA typename K COMMA _EXT callable F>
            constexpr auto operator()(Rng&& rng, K&& key, F&& proj = _EXT identity)
            {
        auto keys = rng | ranges::views::keys;
        auto iterator = ranges::remove(keys, std::forward<K>(key), std::forward<F>(proj));
        auto iterator_distance = ranges::distance(ranges::begin(keys), iterator);
        decltype(auto) removed_value = std::move(rng[std::forward<K>(key)]);
        ranges::erase(std::forward<Rng>(rng), ranges::begin(std::forward<Rng>(rng)) + iterator_distance, ranges::end(std::forward<Rng>(rng)));
        return std::move(removed_value);

        // TODO : return type won't work for chaining
        // TODO : simpler: ranges::actions::remove(ext::make_pair(key, range[key])) ? (maybe get pair type somehow)
            })
}


/* ALGORITHMS */
namespace ranges
{
    RANGE_ALGORITHM_STRUCT(contains_any,
            template <typename R0 COMMA typename R1>
            constexpr auto operator()(R0&& range0, R1&& range1) const
            {
        return ranges::any_of(std::forward<R1>(range1),
                [range0 = std::forward<R0>(range0)]<typename T>(T&& item1) mutable
                {return ranges::contains(std::forward<R0>(range0), std::forward<T>(item1));});
            })


    RANGE_ALGORITHM_STRUCT(contains_all,
            template <typename R0 COMMA typename R1>
            constexpr auto operator()(R0&& range0, R1&& range1)
            {
        return ranges::all_of(std::forward<R1>(range1),
                [range0 = std::forward<R0>(range0)]<typename T>(T&& item1) mutable
                {return ranges::contains(std::forward<R0>(range0), std::forward<T>(item1));});
            })


    RANGE_ALGORITHM_STRUCT(not_contains,
            template <typename R COMMA typename T COMMA _EXT callable F>
            constexpr auto operator()(R&& range, T&& value, F&& proj = _EXT identity)
            {return !ranges::contains(std::forward<R>(range), proj(std::forward<T>(value)));})


    RANGE_ALGORITHM_STRUCT(first_where,
            template <typename R COMMA _EXT callable F>
            constexpr auto operator()(R&& range, F&& pred) const
            {return ranges::begin(range | ranges::views::filter(std::forward<F>(pred)));})


    RANGE_ALGORITHM_STRUCT(last_where,
            template <typename R COMMA _EXT callable F>
            constexpr auto operator()(R&& range, F&& pred) const
            {return ranges::end(range | ranges::views::filter(std::forward<F>(pred)));})

    RANGE_ALGORITHM_STRUCT(index_of,
            template <typename Rng COMMA typename T>
            constexpr auto operator()(Rng&& rng, T&& element) const -> _EXT number<size_t>
            {
        return ranges::contains(std::forward<Rng>(rng), std::forward<T>(element))
                ? ranges::distance(rng.front(), ranges::find(std::forward<Rng>(rng), std::forward<T>(element)))
                : -1;
            })
}


/* OTHER */
namespace ranges
{
    template <category C = category::none, typename ...Args>
    auto make_any_view(Args&&... args) -> any_view<_EXT nth_variadic_type_t<0, Args...>, C>;

    template <typename Ref, ranges::category C = ranges::category::none>
    using any_helpful_view = ranges::any_view<Ref, ranges::category::forward | ranges::category::sized | C>;

    template <category C = category::none, typename ...Args>
    auto make_any_helpful_view(Args&&... args) -> any_helpful_view<_EXT nth_variadic_type_t<0, Args...>, C>;
}


#endif //SBROWSER2_RANGES_HPP
