#pragma once
#ifndef SBROWSER2_OPTIONAL_HPP
#define SBROWSER2_OPTIONAL_HPP

#include "ext/keywords.hpp"
#include <optional>


_EXT_BEGIN

constexpr std::nullopt_t null {std::nullopt_t::_Tag{}};


template <typename T>
class optional final
{
public constructors:
    optional() = default;

    optional(const optional&) = delete;
    optional(optional&&) noexcept = default;
    auto operator=(const optional&) -> optional& = delete;
    auto operator=(optional&&) noexcept -> optional& = delete;

    explicit optional(const T& value) : internal_optional{std::make_optional<T>(value)} {}
    explicit optional(T&& value) noexcept : internal_optional{std::make_optional<T>(std::forward<T>(value))} {}
    auto operator=(const T& value) -> optional& {internal_optional.emplace(value); return *this;}
    auto operator=(T&& value) -> optional& {internal_optional.emplace(std::forward<T>(value)); return *this;}

    optional(const std::nullopt_t&) {}
    auto operator=(const std::nullopt_t&) -> optional& {internal_optional.reset();}

public cpp_methods:
    [[nodiscard]] constexpr auto empty() const -> boolean {return not internal_optional.has_value();}
    [[nodiscard]] constexpr auto has_value() const -> boolean {return internal_optional.has_value();}

    constexpr auto value() const;
    constexpr auto value_or(T&& other) const;
    constexpr auto not_value_or(T&& other) const;
    template <typename U> constexpr auto value_to_or(U&& other) const -> U requires (type_is<T, any>);

    template <typename U> auto has_value_and_equals(U&& other) const -> boolean;
    template <typename U> auto has_value_and_not_equals(U&& other) const -> boolean;
    template <typename U> auto empty_or_equals(U&& other) const -> boolean;
    template <typename U> auto empty_or_not_equals(U&& other) const -> boolean;
    
public cpp_operators:
    auto operator->() const -> auto {return value();}
    template <typename T> // TODO : constrain against ext::optional<T>
    auto operator==(T&& other) const -> ext::boolean {return has_value_and_equals(std::forward<T>(other));}

private cpp_properties:
    std::optional<T> internal_optional;
};


template <typename T>
constexpr auto optional<T>::value() const
{
    return internal_optional.value();
}


template <typename T>
constexpr auto optional<T>::value_or(T&& other) const
{
    return internal_optional.value_or(std::forward<T>(other));
}


template <typename T>
constexpr auto optional<T>::not_value_or(T&& other) const
{
    return empty() ? null : std::forward<T>(other);
}


template <typename T>
template <typename U>
constexpr auto optional<T>::value_to_or(U&& other) const -> U requires (type_is<T, any>)
{
    return empty() ? std::forward<U>(other) : value().template to<U>();
}


template <typename T>
template <typename U>
auto optional<T>::has_value_and_equals(U&& other) const -> boolean
{
    return has_value() && value() == std::forward<U>(other);
}


template <typename T>
template <typename U>
auto optional<T>::has_value_and_not_equals(U&& other) const -> boolean
{
    return has_value() && value() != std::forward<U>(other);
}


template <typename T>
template <typename U>
auto optional<T>::empty_or_equals(U&& other) const -> boolean
{
    return empty() || value() == std::forward<U>(other);
}


template <typename T>
template <typename U>
auto optional<T>::empty_or_not_equals(U&& other) const -> boolean
{
    return empty() || value() != std::forward<U>(other);
}

_EXT_END


#endif //SBROWSER2_OPTIONAL_HPP
