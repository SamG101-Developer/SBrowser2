#pragma once
#ifndef SBROWSER2_OPTIONAL_HPP
#define SBROWSER2_OPTIONAL_HPP

#include "ext/keywords.hpp"
#include <optional>


_EXT_BEGIN

template <typename _Tx>
class optional final
{
public constructors:
    optional() = default;

    optional(const optional&) = delete;
    optional(optional&&) noexcept = default;
    auto operator=(const optional&) -> optional& = delete;
    auto operator=(optional&&) noexcept -> optional& = default;

    explicit optional(const _Tx& _Val) : _Opt{std::make_optional<_Tx>(_Val)} {}
    explicit optional(_Tx&& _Val) noexcept : _Opt{std::make_optional<_Tx>(std::forward<_Tx>(_Val))} {}
    auto operator=(const _Tx& _Val) -> optional& {_Opt.emplace(_Val); return *this;}
    auto operator=(_Tx&& _Val) -> optional& {_Opt.emplace(std::forward<_Tx>(_Val)); return *this;}

    optional(const std::nullopt_t&) {}
    auto operator=(const std::nullopt_t&) -> optional& {_Opt.reset();}

public cpp_methods:
    [[nodiscard]] constexpr auto empty() const -> _EXT boolean {return not _Opt.has_value();}
    [[nodiscard]] constexpr auto has_value() const -> _EXT boolean {return _Opt.has_value();}

    constexpr auto value() const;
    constexpr auto value_or(auto&& _Other) const;
    constexpr auto not_value_or(auto&& _Other) const;
    template <typename _Tx1> constexpr auto value_to_or(_Tx1&& _Other) const -> _Tx1 requires (type_is<_Tx, _EXT any>);

    auto has_value_and_equals(auto&& _Other) const -> _EXT boolean {return has_value() && value() == _Other;}
    auto has_value_and_not_equals(auto&& _Other) const -> _EXT boolean {return has_value() && value() != _Other;}
    auto empty_or_equals(auto&& _Other) const -> _EXT boolean {return empty() || value() == _Other;}
    auto empty_or_not_equals(auto&& _Other) const -> _EXT boolean {return empty() || value() != _Other;}
    
public cpp_operators:
    auto operator->() const -> auto {return value();}
    template <typename _Ty> // TODO : constrain against ext::optional<_Tx>
    auto operator==(_Ty&& _Other) const -> ext::boolean {return has_value_and_equals(std::forward<_Ty>(_Other));}

private cpp_properties:
    std::optional<_Tx> _Opt;
};


constexpr std::nullopt_t null {std::nullopt_t::_Tag{}};

_EXT_END


template <typename _Ty>
constexpr auto _EXT optional<_Ty>::value() const
{
    return _Opt.value();
}


template <typename _Ty>
constexpr auto _EXT optional<_Ty>::value_or(auto&& _Other) const
{
    return _Opt.value_or(std::forward<_Ty>(_Other));
}


template <typename _Ty>
constexpr auto _EXT optional<_Ty>::not_value_or(auto&& _Other) const
{
    return empty() ? null : std::forward<_Ty>(_Other);
}


template <typename _Ty>
template <typename _Ty1>
constexpr auto _EXT optional<_Ty>::value_to_or(_Ty1&& _Other) const -> _Ty1 requires (type_is<_Ty, _EXT any>)
{
    return empty() ? std::forward<_Ty1>(_Other) : value().template to<_Ty1>();
}


#endif //SBROWSER2_OPTIONAL_HPP
