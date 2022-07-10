#pragma once
#ifndef SBROWSER2_OPTIONAL_HPP
#define SBROWSER2_OPTIONAL_HPP

namespace ext {template <typename _Base> class optional;}

#include <optional>
#include <ext/keywords.hpp>

namespace ext {class any;}
namespace ext {auto null = std::nullopt;}


template <typename _Tx>
class ext::optional final
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
    [[nodiscard]] constexpr auto empty() const -> ext::boolean {return not _Opt.has_value();}
    [[nodiscard]] constexpr auto has_value() const -> ext::boolean {return _Opt.has_value();}

    constexpr auto value() const;
    constexpr auto value_or(auto&& _Other) const;
    constexpr auto not_value_or(auto&& _Other) const;
    template <typename _Tx1> constexpr auto value_to_or(auto&& _Other) const -> _Tx1 requires (type_is<_Tx, ext::any>);

    auto has_value_and_equals(auto&& _Other) {return has_value() && value() == _Other;}
    auto has_value_and_not_equals(auto&& _Other) {return has_value() && value() != _Other;}
    auto empty_or_equals(auto&& _Other) {return empty() || value() == _Other;}
    auto empty_or_not_equals(auto&& _Other) {return empty() || value() != _Other;}
    
public cpp_operators:
    auto operator->() const -> auto {return value();}

private cpp_properties:
    std::optional<_Tx> _Opt;
};


template <typename _Ty>
constexpr auto ext::optional<_Ty>::value() const
{
    return _Opt.value();
}


template <typename _Ty>
constexpr auto ext::optional<_Ty>::value_or(auto&& _Other) const
{
    return _Opt.value_or(std::forward<_Ty>(_Other));
}


template <typename _Ty>
constexpr auto ext::optional<_Ty>::not_value_or(auto&& _Other) const
{
    return empty() ? null : std::forward<_Ty>(_Other);
}


template <typename _Ty>
template <typename _Ty1>
constexpr auto ext::optional<_Ty>::value_to_or(auto&& _Other) const -> _Ty1 requires (type_is<_Ty, ext::any>)
{
    return not empty() ? std::forward<_Ty1>(_Other) : value().template to<_Ty1>();
}


#endif //SBROWSER2_OPTIONAL_HPP
