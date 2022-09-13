#pragma once
#ifndef SBROWSER2_ANY_HPP
#define SBROWSER2_ANY_HPP

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/concepts.hpp"
#include "ext/keywords.hpp"
#include <any>
#include <type_traits>


_EXT_BEGIN


class any;

template <typename T>
concept not_any = !type_is<T, any>;


/**
 * The `any` class is an abstraction that sits on top of teh `std:any` class, and adds methods for easier conversion and
 * some other type checks such as if the current value stored in the `any` object is an arithmetic type etc. It also
 * holds a hash of the current object for keying in maps / vectors, and comparisons.
 */
class any final
{
public friends:
     friend struct std::hash<ext::any>;

public constructors:
    any() = default;
    ~any() = default;

    any(const any&) = default;
    any(any&&) noexcept = default;
    auto operator=(const any&) -> any& = delete;
    auto operator=(any&&) noexcept -> any& = default;

    template <not_any T> any(T&& value) noexcept;
    template <not_any T> auto operator=(const T& value) -> any&;
    template <not_any T> auto operator=(T&& value) noexcept -> any&;

public cpp_methods:
    [[nodiscard]] auto type() const -> const type_info&;
    [[nodiscard]] auto is_arithmetic_type() const -> boolean;
    [[nodiscard]] auto is_empty() const -> boolean;
    [[nodiscard]] auto has_value() const -> boolean;
    template <typename T> auto to() const -> T;
    template <is_rvalue_reference T> auto to() const -> T;
    template <typename T> auto try_to() const -> ext::boolean;

public cpp_operators:
    auto operator==(const any& other) const -> bool;
    template <not_any T> auto operator==(T&& other) const -> bool;

private cpp_properties:
    std::any m_any;
    boolean m_is_arithmetic;
    ext::number<size_t> m_hash = 0;
};


template <not_any T>
any::any(T&& value) noexcept
        : m_any{std::forward<T>(value)}
        , m_is_arithmetic{type_is_any_specialization<T, number>}
        // TODO: , m_hash{std::hash<T>{}(std::forward<T>(value))}
{
    // the perfect forwarding (non-copy / -move) constructor initializes the `_Any` attribute to the value (forwarded),
    // and the `_IsArithmetic` attribute is set if the `value` is any of the `number<T>` class specializations
}


template <not_any T>
auto any::operator=(const T& value) -> any&
{
    m_any = value;
    m_is_arithmetic = type_is_any_specialization<T, number>;
    m_hash = std::hash<T>{}(std::forward<T>(value));
    return *this;
}


template <not_any T>
auto any::operator=(T&& value) noexcept -> any&
{
    m_any = std::forward<decltype(value)>(value);
    m_is_arithmetic = type_is_any_specialization<T, number>;
    m_hash = std::hash<T>{}(std::forward<T>(value));
    return *this;
}


auto any::type() const -> const type_info&
{
    // get the `type_info` type of the object being stored in the internal `std::any` object (identical method
    // forwarding)
    return m_any.type();
}


auto any::is_arithmetic_type() const -> boolean
{
    // get if the object  being stored in the internal `std::any` object is arithmetic or not - this is determined by a
    // flag that is set whenever the value of the `any` object is set / mutated
    return m_is_arithmetic;
}


auto any::is_empty() const -> boolean
{
    // the `any` object is empty if it doesn't have a value (check with internal `std::any` object)
    return !m_any.has_value();
}


auto any::has_value() const -> boolean
{
    return m_any.has_value();
}


template <typename T>
auto any::to() const -> T
{
    return std::any_cast<T>(m_any);
}


template <is_rvalue_reference T>
auto any::to() const -> T
{
    return std::move(std::any_cast<T&&>(m_any));
}


template <typename T>
auto any::try_to() const -> ext::boolean
{
    try
    {
        auto try_cast = to<T>();
        static_cast<void>(try_cast);
        return true;
    }
    catch (const std::bad_any_cast& exception)
    {
        return false;
    }
}


auto any::operator==(const ext::any& other) const -> bool
{
    return m_hash == other.m_hash;
}


template <not_any T>
auto any::operator==(T&& other) const -> bool
{
    return std::forward<T>(other) == to<T>();
}


_EXT_END


#endif //SBROWSER2_ANY_HPP
