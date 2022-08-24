#pragma once
#ifndef SBROWSER2_NUMBER_HPP
#define SBROWSER2_NUMBER_HPP

#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/string.hpp"
#include <limits>
#include <stdexcept>

#define DEFINE_BINARY_NUMBER_OPERATOR(op)                                                                                      \
    template <arithmetic T, arithmetic U>                                                                                      \
    constexpr auto operator op (const _EXT number<T>& lhs, const _EXT number<U>& rhs) -> _EXT number<std::common_type_t<T, U>> \
    {return {*lhs op *rhs};}                                                                                                   \
                                                                                                                               \
    template <arithmetic T, arithmetic U>                                                                                      \
    constexpr auto operator op (const _EXT number<T>& lhs, const U& rhs) -> _EXT number<std::common_type_t<T, U>>              \
    {return {*lhs op rhs};}                                                                                                    \
                                                                                                                               \
    template <arithmetic T, arithmetic U>                                                                                      \
    constexpr auto operator op (const T& lhs, const _EXT number<U>& rhs) -> T                                                  \
    {return {lhs op *rhs};}                                                                                                    \
                                                                                                                               \
    template <arithmetic T, arithmetic U>                                                                                      \
    constexpr auto operator op##=(_EXT number<T>& lhs, const _EXT number<U>& rhs) -> _EXT number<T>&                           \
    {*lhs op##= *rhs; return lhs;}                                                                                             \
                                                                                                                               \
    template <arithmetic T, arithmetic U>                                                                                      \
    constexpr auto operator op##=(_EXT number<T>& lhs, const U& rhs) -> _EXT number<T>&                                        \
    {*lhs op##= rhs; return lhs;}                                                                                              \
                                                                                                                               \
    template <arithmetic T, arithmetic U>                                                                                      \
    constexpr auto operator op##=(T& lhs, const _EXT number<U>& rhs) -> T&                                                     \
    {lhs op##= *rhs; return lhs;}                                                                                              \


#define DEFINE_BINARY_NUMBER_COMPARISON(op)                                                   \
    template <arithmetic T, arithmetic U>                                                     \
    constexpr auto operator op (const ext::number<T>& lhs, const ext::number<U>& rhs) -> bool \
    {return {*lhs op *rhs};}                                                                  \
                                                                                              \
    template <arithmetic T, arithmetic U>                                                     \
    constexpr auto operator op (const ext::number<T>& lhs, const U& rhs) -> bool              \
    {return {*lhs op rhs};}                                                                   \
                                                                                              \
    template <arithmetic T, arithmetic U>                                                     \
    constexpr auto operator op (const T& lhs, const ext::number<U>& rhs) -> bool              \
    {return {lhs op *rhs};}                                                                   \



_EXT_BEGIN

template <arithmetic T>
class number final
{
public:
    template <arithmetic U>
    friend class _EXT number;

    using value_t = T;

    constexpr number(T val): n(val) {}
    number() = default;
    number(const number&) = default;
    number(number&&) noexcept = default;
    auto operator=(const number&) -> number& = default;
    auto operator=(number&&) noexcept -> number& = default;

    auto operator=(T val) -> number&
    {n = val; return *this;}

    auto operator++() -> number&
    {++n; return *this;}

    auto operator--() -> number&
    {--n; return *this;}

    auto operator-() -> number&
    {n *= -1; return *this;}

    template <arithmetic U>
    auto operator=(const ext::number<U>& val)
    {n = *val;}

    template <arithmetic U>
    operator number<U>() const
    {return {static_cast<U>(n)};}

    constexpr auto operator*() -> T& {return n;}
    constexpr auto operator*() const -> const T& {return n;}

    static auto inf() -> number
    {return std::numeric_limits<T>::infinity();}

    static auto nan() -> number
    {return std::numeric_limits<T>::quiet_NaN();}

private:
    T n;
};

_EXT_END


DEFINE_BINARY_NUMBER_OPERATOR(+)
DEFINE_BINARY_NUMBER_OPERATOR(-)
DEFINE_BINARY_NUMBER_OPERATOR(*)
DEFINE_BINARY_NUMBER_OPERATOR(/)
DEFINE_BINARY_NUMBER_OPERATOR(%)
DEFINE_BINARY_NUMBER_OPERATOR(&)
DEFINE_BINARY_NUMBER_OPERATOR(|)
DEFINE_BINARY_NUMBER_OPERATOR(^)
DEFINE_BINARY_NUMBER_OPERATOR(<<)
DEFINE_BINARY_NUMBER_OPERATOR(>>)

DEFINE_BINARY_NUMBER_COMPARISON(<)
DEFINE_BINARY_NUMBER_COMPARISON(<=)
DEFINE_BINARY_NUMBER_COMPARISON(>)
DEFINE_BINARY_NUMBER_COMPARISON(>=)
DEFINE_BINARY_NUMBER_COMPARISON(==)
DEFINE_BINARY_NUMBER_COMPARISON(!=)


_EXT_BEGIN

template <bool IncludeLo, bool IncludeHi, typename T, typename U, typename V>
auto is_between(T&& value, U&& lo, V&& hi) -> boolean
{
    auto condition1 = IncludeLo ? value >= lo : value > lo; // default to >
    auto condition2 = IncludeHi ? value <= hi : value < hi; // default to <
    return condition1 && condition2;
}


template <typename T, typename U, typename ...V>
auto min(T&& value0, U&& value1, V&&... values)
{
    if constexpr(sizeof...(values) == 0) return value0 < value1 ? value0 : value1;
    else return min(min(std::forward<T>(value0), std::forward<U>(value1)), std::forward<V>(values)...);
}


template <typename T, typename U, typename ...V>
auto max(T&& value0, U&& value1, V&&... values)
{
    if constexpr(sizeof...(values) == 0) return value0 > value1 ? value0 : value1;
    else return max(max(std::forward<T>(value0), std::forward<U>(value1)), std::forward<V>(values)...);
}


template <typename T, typename U>
auto round(T&& value, U&& multiplier)
{
    return std::round(std::move(value / multiplier)) * std::forward<U>(multiplier);
}


template <typename T>
auto absolute(T&& value)
{
    return value < 0 ? -value : value;
}


auto is_numeric_string(const string& string) -> boolean
{
    try {static_cast<void>(std::stod(string)); return boolean::TRUE_();}
    catch_specific (std::invalid_argument) {return boolean::FALSE_();}
}


template <typename U>
auto to_string(const number<U>& number)
{
    return std::to_string((U)number);
}

_EXT_END


_EXT_SHORTHAND_BEGIN
template <typename T> using nv = const number<T>&;
_EXT_SHORTHAND_END


#endif //SBROWSER2_NUMBER_HPP
