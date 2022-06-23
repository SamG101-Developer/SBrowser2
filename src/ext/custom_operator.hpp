#pragma once
#ifndef SBROWSER2_CUSTOM_OPERATOR_HPP
#define SBROWSER2_CUSTOM_OPERATOR_HPP

#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdexcept>
#include <javascript/environment/realms.hpp>
#include <javascript/interop/annotations.hpp>


#define custom_operator(name)                                  \
    const struct name ## _ {} name;                            \
                                                               \
    template <typename L>                                      \
    struct name ## _proxy                                      \
    {                                                          \
        explicit name ## _proxy(const L& t) : t_(t) {}         \
        const L& t_;                                           \
    };                                                         \
                                                               \
    template <typename L, typename R>                          \
    auto name ## _method(const L& a, const R& b);              \
                                                               \
    template <typename L>                                      \
    auto operator<(const L& lhs, const name ## _ rhs)          \
    {                                                          \
        return name ## _proxy<L>{lhs};                         \
    };                                                         \
                                                               \
    template <typename L, typename R>                          \
    auto operator>(const name ## _proxy<L>& lhs, const R& rhs) \
    {                                                          \
        return name ## _method<L, R>(lhs.t_, rhs);             \
    };                                                         \
                                                               \
    template <typename L, typename R>                          \
    auto name ## _method(const L& a, const R& b)


// binary operators
custom_operator(try_or)
{
    try {return a();}
    catch_all {return b;}
}

#define try_or <try_or>


// prefix unary operators
custom_operator(clamp)
{
    auto r = std::clamp(b.min(), b.max(), b);
    static_cast<void>(r);
}
#define js_clamp 0 <clamp>

custom_operator(enforce_range)
{
    if (b < b.min() || b > b.max())
        throw std::out_of_range{"Number out of range"};
}
#define js_enforce_range 0 <enforce_range>


// postfix unary operators


// annotation operators
#define new_object
#define same_object
#define unscopable // TODO -> link to JS @@unscopable


#define ce_reaction_method_def \
    auto _ce_method = [&]

#define ce_reaction_method_exe                                                                                                                                                   \
    {                                                                                                                                                                            \
        using stack_t = dom::detail::customization_internals::custom_element_reactions_stack;                                                                                    \
        auto custom_element_reactions_stack = javascript::environment::realms::realm<dom::nodes::window*>::relevant_realm(this).get<stack_t*>("custom_element_reactions_stack"); \
        custom_element_reactions_stack->emplace();                                                                                                                               \
        JS_EXCEPTION_HANDLER;                                                                                                                                                    \
        auto value = _ce_method();                                                                                                                                               \
        auto* queue = custom_element_reactions_stack->top();                                                                                                                     \
        custom_element_reactions_stack->pop();                                                                                                                                   \
        if (JS_EXCEPTION_HAS_THROWN) JS_EXCEPTION_RETHROW;                                                                                                                       \
        return value;                                                                                                                                                            \
    }


#endif //SBROWSER2_CUSTOM_OPERATOR_HPP
