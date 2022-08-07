#pragma once
#ifndef SBROWSER2_OPTIONAL_HPP
#define SBROWSER2_OPTIONAL_HPP

#include "ext/keywords.hpp"
#include <optional>


_EXT_BEGIN


constexpr std::nullopt_t null {std::nullopt_t::_Tag{}};


template <typename _Tx>
class optional final
{
public constructors:
    optional() = default;

    optional(const optional&) = delete;
    optional(optional&&) noexcept = default;
    auto operator=(const optional&) -> optional& = delete;
    auto operator=(optional&&) noexcept -> optional& = delete;

    explicit optional(const _Tx& value) : _Opt{std::make_optional<_Tx>(value)} {}
    explicit optional(_Tx&& value) noexcept : _Opt{std::make_optional<_Tx>(std::forward<_Tx>(value))} {}
    auto operator=(const _Tx& value) -> optional& {_Opt.emplace(value); return *this;}
    auto operator=(_Tx&& value) -> optional& {_Opt.emplace(std::forward<_Tx>(value)); return *this;}

    optional(const std::nullopt_t&) {}
    auto operator=(const std::nullopt_t&) -> optional& {_Opt.reset();}

public cpp_methods:
    [[nodiscard]] constexpr auto empty() const -> boolean {return not _Opt.has_value();}
    [[nodiscard]] constexpr auto has_value() const -> boolean {return _Opt.has_value();}

    constexpr auto value() const;
    constexpr auto value_or(_Tx&& _Other) const;
    constexpr auto not_value_or(_Tx&& _Other) const;
    template <typename _Tx1> constexpr auto value_to_or(_Tx1&& _Other) const -> _Tx1 requires (type_is<_Tx, any>);

    template <typename _Tx1> auto has_value_and_equals(_Tx1&& _Other) const -> boolean;
    template <typename _Tx1> auto has_value_and_not_equals(_Tx1&& _Other) const -> boolean;
    template <typename _Tx1> auto empty_or_equals(_Tx1&& _Other) const -> boolean;
    template <typename _Tx1> auto empty_or_not_equals(_Tx1&& _Other) const -> boolean;
    
public cpp_operators:
    auto operator->() const -> auto {return value();}
    template <typename _Ty> // TODO : constrain against ext::optional<_Tx>
    auto operator==(_Ty&& _Other) const -> ext::boolean {return has_value_and_equals(std::forward<_Ty>(_Other));}

private cpp_properties:
    std::optional<_Tx> _Opt;
};


template <typename _Ty>
constexpr auto optional<_Ty>::value() const
{
    return _Opt.value();
}


template <typename _Ty>
constexpr auto optional<_Ty>::value_or(_Ty&& _Other) const
{
    return _Opt.value_or(std::forward<_Ty>(_Other));
}


template <typename _Ty>
constexpr auto optional<_Ty>::not_value_or(_Ty&& _Other) const
{
    return empty() ? null : std::forward<_Ty>(_Other);
}


template <typename _Ty>
template <typename _Ty1>
constexpr auto optional<_Ty>::value_to_or(_Ty1&& _Other) const -> _Ty1 requires (type_is<_Ty, any>)
{
    return empty() ? std::forward<_Ty1>(_Other) : value().template to<_Ty1>();
}


template <typename _Ty>
template <typename _Ty1>
auto optional<_Ty>::has_value_and_equals(_Ty1&& _Other) const -> boolean
{
    return has_value() && value() == std::forward<_Ty1>(_Other);
}


template <typename _Ty>
template <typename _Ty1>
auto optional<_Ty>::has_value_and_not_equals(_Ty1&& _Other) const -> boolean
{
    return has_value() && value() != std::forward<_Ty1>(_Other);
}


template <typename _Ty>
template <typename _Ty1>
auto optional<_Ty>::empty_or_equals(_Ty1&& _Other) const -> boolean
{
    return empty() || value() == std::forward<_Ty1>(_Other);
}


template <typename _Ty>
template <typename _Ty1>
auto optional<_Ty>::empty_or_not_equals(_Ty1&& _Other) const -> boolean
{
    return empty() || value() != std::forward<_Ty1>(_Other);
}

_EXT_END


#endif //SBROWSER2_OPTIONAL_HPP
