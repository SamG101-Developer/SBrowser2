#pragma once
#ifndef SBROWSER2_NUMBER_HPP
#define SBROWSER2_NUMBER_HPP

#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/random.hpp"
#include "ext/string.hpp"
#include <limits>
#include <stdexcept>

using longlong   = long long;
using uchar      = unsigned char;
using ushort     = unsigned short;
using uint       = unsigned int;
using ulong      = unsigned long;
using ulonglong  = unsigned long long;
using longdouble = long double;


#define DEFINE_BINARY_NUMBER_OPERATOR(op)                                                                                      \
    template <ext::arithmetic T, ext::arithmetic U>                                                                            \
    constexpr auto operator op (const _EXT number<T>& lhs, const _EXT number<U>& rhs) -> _EXT number<std::common_type_t<T, U>> \
    {return {*lhs op *rhs};}                                                                                                   \
                                                                                                                               \
    template <ext::arithmetic T, ext::arithmetic U>                                                                            \
    constexpr auto operator op (const _EXT number<T>& lhs, const U& rhs) -> _EXT number<std::common_type_t<T, U>>              \
    {return {*lhs op rhs};}                                                                                                    \
                                                                                                                               \
    template <ext::arithmetic T, ext::arithmetic U>                                                                            \
    constexpr auto operator op (const T& lhs, const _EXT number<U>& rhs) -> T                                                  \
    {return {lhs op *rhs};}                                                                                                    \
                                                                                                                               \
    template <ext::arithmetic T, ext::arithmetic U>                                                                            \
    constexpr auto operator op##=(_EXT number<T>& lhs, const _EXT number<U>& rhs) -> _EXT number<T>&                           \
    {*lhs op##= *rhs; return lhs;}                                                                                             \
                                                                                                                               \
    template <ext::arithmetic T, ext::arithmetic U>                                                                            \
    constexpr auto operator op##=(_EXT number<T>& lhs, const U& rhs) -> _EXT number<T>&                                        \
    {*lhs op##= rhs; return lhs;}                                                                                              \
                                                                                                                               \
    template <ext::arithmetic T, ext::arithmetic U>                                                                            \
    constexpr auto operator op##=(T& lhs, const _EXT number<U>& rhs) -> T&                                                     \
    {lhs op##= *rhs; return lhs;}                                                                                              \


#define DEFINE_BINARY_NUMBER_COMPARISON(op)                                                   \
    template <ext::arithmetic T, ext::arithmetic U>                                           \
    constexpr auto operator op (const ext::number<T>& lhs, const ext::number<U>& rhs) -> bool \
    {return {*lhs op *rhs};}                                                                  \
                                                                                              \
    template <ext::arithmetic T, ext::arithmetic U>                                           \
    constexpr auto operator op (const ext::number<T>& lhs, const U& rhs) -> bool              \
    {return {*lhs op rhs};}                                                                   \
                                                                                              \
    template <ext::arithmetic T, ext::arithmetic U>                                           \
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
    constexpr operator bool() const {return n != 0;}

    template <arithmetic U>
    auto as() const {return ext::number<U>{static_cast<U>(n)};}

    static auto inf() -> number
    {return std::numeric_limits<T>::infinity();}

    static auto nan() -> number
    {return std::numeric_limits<T>::quiet_NaN();}

    static auto min() -> number
    {return std::numeric_limits<T>::min();}

    static auto max() -> number
    {return std::numeric_limits<T>::max();}

    template <typename U, typename V>
    static auto random(U&& minimum = ext::number<T>::min(), V&& maximum = ext::number<T>::max()) -> number
    {return ext::random::get(std::forward<U>(minimum), std::forward<V>(maximum));}

private:
    T n;
};

_EXT_END


_STD_BEGIN
template <ext::arithmetic T>
class numeric_limits<ext::number<T>> : public numeric_limits<T>
{
public:
    _EXT_NODISCARD static constexpr auto (min)() noexcept -> T {
        return std::numeric_limits<T>::min();
    }

    _EXT_NODISCARD static constexpr auto (max)() noexcept -> T {
        return std::numeric_limits<T>::max();
    }

    _EXT_NODISCARD static constexpr auto lowest() noexcept -> T {
        return std::numeric_limits<T>::lowest();
    }

    _EXT_NODISCARD static constexpr auto epsilon() noexcept -> T {
        return std::numeric_limits<T>::epsilon();
    }

    _EXT_NODISCARD static constexpr auto round_error() noexcept -> T {
        return std::numeric_limits<T>::round_error();
    }

    _EXT_NODISCARD static constexpr auto denorm_min() noexcept -> T {
        return std::numeric_limits<T>::denorm_min();
    }

    _EXT_NODISCARD static constexpr auto infinity() noexcept -> T {
        return std::numeric_limits<T>::infinity();
    }

    _EXT_NODISCARD static constexpr auto quiet_NaN() noexcept -> T {
        return std::numeric_limits<T>::quiet_NaN();
    }

    _EXT_NODISCARD static constexpr auto signaling_NaN() noexcept -> T {
        return std::numeric_limits<T>::signaling_NaN();
    }
};
_STD_END


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
    return std::round(*ext::number{std::move(value / multiplier)}) * std::forward<U>(multiplier);
}


template <typename T>
auto absolute(T&& value)
{
    return value < 0 ? -value : value;
}


auto is_numeric_string(const string& string) -> boolean
{
    try
    {
        static_cast<void>(std::stod(string));
        return true;
    }

    catch (std::invalid_argument)
    {
        return false;
    }
}


template <typename T>
auto to_string(const number<T>& number)
{
    return std::to_string(*number);
}


template <typename ...Args>
auto is_inf(Args&&... numbers)
{
    return ((numbers == std::numeric_limits<std::remove_reference_t<Args>>::infinity()) || ...);
}


template <typename ...Args>
auto is_nan(Args&&... numbers)
{
    return ((numbers == std::numeric_limits<std::remove_reference_t<Args>>::quiet_NaN()) || ...);
}


template <typename ...Args>
auto is_inf_or_nan(Args&&... numbers)
{
    return is_inf(std::forward<Args>(numbers)...) || is_nan(std::forward<Args>(numbers)...);
}


template <typename T>
auto abs(T number) -> T
{
    return number * ((number > 0) - (number < 0));
}

_EXT_END


_EXT_LITERALS_BEGIN
auto operator""_n(char number) {return ext::number<char>{number};}
auto operator""_n(ulonglong number) {return ext::number<ulonglong>{number};}
auto operator""_n(longdouble number) {return ext::number<longdouble>{number};}
_EXT_LITERALS_END


_EXT_SHORTHAND_BEGIN
template <typename T> using nv = const number<T>&;
_EXT_SHORTHAND_END


#endif //SBROWSER2_NUMBER_HPP
