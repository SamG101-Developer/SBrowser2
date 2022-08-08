#pragma once
#ifndef SBROWSER2_NUMBER_HPP
#define SBROWSER2_NUMBER_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "ext/detail/infinity.hpp"
#include "boolean.hpp"

#include <algorithm>
#include <limits>
#include <ostream>
#include <string>
#include <type_traits>
#include <utility>


_EXT_BEGIN

template <typename T> // TODO : change typename to 'primitive_number'
class number final
{
public aliases:
    using primitive_t = T;

public friends:
    template <typename U> friend class number;

public constructors:
    number() = default;
    template <typename U> constexpr number(U primitive);
    template <typename U> auto operator=(U primitive) -> number&;

    template <typename U> explicit number(const number<U>& other);
    template <typename U> explicit number(number<U>&& other) noexcept;
    template <typename U> auto operator=(const number<U>& other) -> number&;
    template <typename U> auto operator=(number<U>&& other) noexcept -> number&;
    
public cpp_methods:
    auto min() const -> number<T> {return std::numeric_limits<T>::min();}
    auto max() const -> number<T> {return std::numeric_limits<T>::max();}

public cpp_static_methods:
    static auto INF() -> detail::infinity<T> {return detail::infinity<T>{};};

public cpp_operators:
    // conversion operators
    explicit operator std::string() const {return std::to_string(internal_number);}

    auto operator+(auto&& other) const {return number{internal_number + std::forward<T>(other)};}
    auto operator-(auto&& other) const {return number{internal_number - std::forward<T>(other)};}
    auto operator*(auto&& other) const {return number{internal_number * std::forward<T>(other)};}
    auto operator/(auto&& other) const {return number{internal_number / std::forward<T>(other)};}
    auto operator%(auto&& other) const {return number{internal_number % std::forward<T>(other)};}
    auto operator|(auto&& other) const {return number{internal_number | std::forward<T>(other)};}
    auto operator&(auto&& other) const {return number{internal_number & std::forward<T>(other)};}
    auto operator<<(auto&& other) const {return number{internal_number << std::forward<T>(other)};}
    auto operator>>(auto&& other) const {return number{internal_number >> std::forward<T>(other)};}

    auto operator+=(auto&& other) {internal_number += std::forward<T>(other); return *this;}
    auto operator-=(auto&& other) {internal_number -= std::forward<T>(other); return *this;}
    auto operator*=(auto&& other) {internal_number *= std::forward<T>(other); return *this;}
    auto operator/=(auto&& other) {internal_number /= std::forward<T>(other); return *this;}
    auto operator%=(auto&& other) {internal_number %= std::forward<T>(other); return *this;}
    auto operator|=(auto&& other) {internal_number |= std::forward<T>(other); return *this;}
    auto operator&=(auto&& other) {internal_number &= std::forward<T>(other); return *this;}
    auto operator<<=(auto&& other) {internal_number <<= std::forward<T>(other); return *this;}
    auto operator>>=(auto&& other) {internal_number >>= std::forward<T>(other); return *this;}

    auto operator==(const auto& other) const -> bool {return internal_number == other;}
    auto operator<=>(const auto& other) const {return internal_number <=> other;}

    auto operator++() -> number& {++internal_number; return *this;}
    auto operator--() -> number& {--internal_number; return *this;}

    template <typename U> operator number<U>() const {return number<U>(internal_number);}
    template <typename U> constexpr operator U() const {return internal_number;}

private:
    auto operator*() const -> T {return internal_number;}

private cpp_properties:
    T internal_number;
};


template <typename U>
using number_view = const number<U>&;


template <typename T>
template <typename U>
constexpr number<T>::number(U primitive)
        : internal_number(primitive)
{}


template <typename T>
template <typename U>
auto number<T>::operator=(U primitive) -> number&
{
    internal_number = primitive;
    return *this;
}


template <typename T>
template <typename U>
number<T>::number(const number<U>& other)
        : internal_number(*other)
{}


template <typename T>
template <typename U>
number<T>::number(number<U>&& other) noexcept
        : internal_number(*std::move(other))
{}


template <typename T>
template <typename U>
auto number<T>::operator=(const number<U>& other) -> number&
{
    internal_number = *other;
    return *this;
}


template <typename T>
template <typename U>
auto number<T>::operator=(number<U>&& other) noexcept -> number&
{
    internal_number = *std::move(other);
    return *this;
}


template <bool InclusiveLo, bool InclusiveHi>
auto is_between(auto&& value, auto&& lo, auto&& hi) -> boolean
{
    auto condition1 = InclusiveLo ? value >= lo : value > lo; // default to >
    auto condition2 = InclusiveHi ? value <= hi : value < hi; // default to <
    return condition1 && condition2;
}


template <typename T, typename U, typename ...V>
auto min(T&& value0, U&& value1, V&&... values)
{
    if constexpr(sizeof...(values) == 0) return value0 < value1 ? value0 : number{value1};
    else return min(min(std::forward<T>(value0), std::forward<U>(value1)), std::forward<V>(values)...);
}


template <typename T, typename U, typename ...V>
auto max(T&& value0, U&& value1, V&&... values)
{
    if constexpr(sizeof...(values) == 0) return value0 > value1 ? value0 : number{value1};
    else return max(max(std::forward<T>(value0), std::forward<U>(value1)), std::forward<V>(values)...);
}


template <typename T, typename U>
auto round(T&& value, U&& multiplier)
{
    return std::round(std::move(value / multiplier)) * std::forward<U>(multiplier);
}


auto is_numeric_string(const string& string) -> boolean
{
    try {static_cast<void>(std::stod(string)); return boolean::TRUE();}
    catch_specific (std::invalid_argument) {return boolean::FALSE();}
}


template <typename U>
auto to_string(number_view<U> number)
{
    return std::to_string((U)number);
}


_EXT_END


#endif //SBROWSER2_NUMBER_HPP
