#pragma once
#ifndef SBROWSER2_CUSTOM_OPERATOR_HPP
#define SBROWSER2_CUSTOM_OPERATOR_HPP

#include <algorithm>
#include <cmath>
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

custom_operator(try_or) {try {return a();} catch(...) {return b;}}
#define try_or <try_or>


// prefix unary operators

custom_operator(clamp) {std::clamp(b.min(), b.max(), b);}
#define clamp 0 <clamp>

custom_operator(enforce_range) {if (b < b.min() or b > b.max()) throw std::out_of_range{"Number out of range"};}
#define enforce_range 0 <enforce_range>


// postfix unary operators

//
//


// annotation operators
#define new_object
#define same_object
#define unscopabe // TODO -> link to JS @@unscopable



#endif //SBROWSER2_CUSTOM_OPERATOR_HPP
