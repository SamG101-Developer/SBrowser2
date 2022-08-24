#pragma once
#ifndef SBROWSER2_CUSTOM_OPERATOR_HPP
#define SBROWSER2_CUSTOM_OPERATOR_HPP

#include "javascript/environment/realms_2.hpp"
#include "javascript/interop/annotations.hpp"
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <thread>
#include <stdexcept>


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
    if (b < b.min() || b > b.max()) throw std::out_of_range{"Number out of range"};
}
#define js_enforce_range 0 <enforce_range>


custom_operator(go)
{
    std::jthread _thread{b};
}
#define go 0 <go>


// postfix unary operators


// annotation operators
#define new_object
#define same_object
#define unscopable // TODO -> link to JS @@unscopable


#define ce_reactions_method_def \
    auto _ce_method = [&]{;


#define ce_reactions_method_exe                                                                                                   \
    };                                                                                                                            \
    {                                                                                                                             \
        using _stack_t = dom::detail::custom_element_reactions_stack_t;                                                           \
        JS_REALM_GET_RELEVANT(this)                                                                                               \
        auto _ce_reactions_stack = javascript::environment::realms_2::get<_stack_t>(this_relevant_global_object, "ce_reactions"); \
        _ce_reactions_stack->emplace();                                                                                           \
                                                                                                                                  \
        JS_EXCEPTION_HANDLER;                                                                                                     \
        auto _value = _ce_method();                                                                                               \
        auto _queue = _ce_reactions_stack->top();                                                                                 \
        _ce_reactions_stack->pop();                                                                                               \
                                                                                                                                  \
        if (JS_EXCEPTION_HAS_THROWN)                                                                                              \
            JS_EXCEPTION_RETHROW;                                                                                                 \
                                                                                                                                  \
        return _value;                                                                                                            \
    }


#define HTML_CONSTRUCTOR     \
    {                        \
        JS_REALM_GET_CURRENT \
    }


#define async_method_def(_ret_t)   \
    std::promise<_ret_t> _promise; \
    std::thread([](){

#define async_method_exe \
    };                   \
    {                    \
        return _promise; \
    }


#endif //SBROWSER2_CUSTOM_OPERATOR_HPP
