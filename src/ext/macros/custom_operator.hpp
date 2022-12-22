#ifndef SBROWSER2_SRC_EXT_MACROS_CUSTOM_OPERATOR_HPP
#define SBROWSER2_SRC_EXT_MACROS_CUSTOM_OPERATOR_HPP

#include <thread>
#include <stdexcept>
#include <algorithm>


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
    catch (...) {return b;}
}

#define _TRY_OR <try_or>


// prefix unary operators
custom_operator(clamp)
{
    auto r = std::clamp(b.min(), b.max(), b);
    static_cast<void>(r);
}
#define _JS_CLAMP 0 <clamp>


custom_operator(enforce_range)
{
    if (b < b.min() || b > b.max())
        throw std::out_of_range{"Number out of range"};
}
#define _JS_ENFORCE_RANGE 0 <enforce_range>


custom_operator(go)
{
    std::jthread _thread{b};
}
#define _GO 0 <go>


// postfix unary operators



#define _CE_REACTIONS_METHOD_DEF \
    auto _ce_method = [&]{


// TODO : if the function '_ce_method(...)' doesn't have a return value then branch and complete with no return
#define _CE_REACTIONS_METHOD_EXE                                                                   \
    };                                                                                             \
    {                                                                                              \
        using _stack_t = dom::detail::custom_element_reactions_stack_t;                            \
        auto _e = js::env::env::relevant(this);                                                    \
        auto _ce_reactions_stack = js::env::get_slot<_stack_t*>(_e, js::env::slots::CE_REACTIONS); \
        _ce_reactions_stack->queues.emplace();                                                     \
                                                                                                   \
        JS_EXCEPTION_HANDLER;                                                                      \
        auto _value = _ce_method();                                                                \
        auto _queue = _ce_reactions_stack->queues.top();                                           \
        _ce_reactions_stack->queues.pop();                                                         \
                                                                                                   \
        if (JS_EXCEPTION_HAS_THROWN)                                                               \
            JS_EXCEPTION_RETHROW;                                                                  \
                                                                                                   \
        return _value;                                                                             \
    }


#define _HTML_CONSTRUCTOR

#endif //SBROWSER2_SRC_EXT_MACROS_CUSTOM_OPERATOR_HPP
