#pragma once
#ifndef SBROWSER2_ANY_HPP
#define SBROWSER2_ANY_HPP

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/concepts.hpp"
#include "ext/keywords.hpp"
#include <any>


_EXT_BEGIN


class any;

template <typename _Tx>
concept not_any = !type_is<_Tx, any>;


/**
 * The `any` class is an abstraction that sits on top of teh `std:any` class, and adds methods for easier conversion and
 * some other type checks such as if the current value stored in the `any` object is an arithmetic type etc.
 */
class any final
{
public constructors:
    any() = default;
    ~any() = default;

    any(const any&) = delete;
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
    template <typename _Ty> auto to() const -> _Ty;

public cpp_operators:
    auto operator==(const any& other) const -> bool;
    template <not_any T> auto operator==(T&& other) const -> bool;

private cpp_properties:
    std::any internal_any;
    boolean is_arithmetic;
};


using any_view = const any&;


template <not_any T>
any::any(T&& value) noexcept
        : internal_any(std::forward<T>(value))
        , is_arithmetic(type_is_any_specialization<T, number>)
{
    // the perfect forwarding (non-copy / -move) constructor initializes the `_Any` attribute to the value (forwarded),
    // and the `_IsArithmetic` attribute is set if the `value` is any of the `number<T>` class specializations
}


template <not_any T>
auto any::operator=(const T& value) -> any&
{
    internal_any = value;
    is_arithmetic = type_is_any_specialization<T, number>;
    return *this;
}


template <not_any T>
auto any::operator=(T&& value) noexcept -> any&
{
    internal_any = std::forward<decltype(value)>(value);
    is_arithmetic = type_is_any_specialization<T, number>;
    return *this;
}


auto any::type() const -> const type_info&
{
    // get the `type_info` type of the object being stored in the internal `std::any` object (identical method
    // forwarding)
    return internal_any.type();
}


auto any::is_arithmetic_type() const -> boolean
{
    // get if the object  being stored in the internal `std::any` object is arithmetic or not - this is determined by a
    // flag that is set whenever the value of the `any` object is set / mutated
    return is_arithmetic;
}


auto any::is_empty() const -> boolean
{
    return !internal_any.has_value();
}


auto any::has_value() const -> boolean
{
    return internal_any.has_value();
}


template <typename _Ty>
auto any::to() const -> _Ty
{
    return std::any_cast<_Ty>(internal_any);
}


auto any::operator==(const ext::any& other) const -> bool
{
    return &other.internal_any == &internal_any;
}


template <not_any T>
auto any::operator==(T&& other) const -> bool
{
    return std::forward<T>(other) == to<T>();
}


_EXT_END


#endif //SBROWSER2_ANY_HPP
