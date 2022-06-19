#pragma once
#ifndef SBROWSER2_OPTIONAL_HPP
#define SBROWSER2_OPTIONAL_HPP

namespace ext {template <typename _Tx> class optional;}

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

    explicit optional(const _Tx& _Val) : _Opt(std::make_optional<_Tx>(_Val)) {}
    explicit optional(_Tx&& _Val) noexcept : _Opt(std::make_optional<_Tx>(std::forward<_Tx>(_Val))) {}
    auto operator=(const _Tx& _Val) -> optional& {_Opt.emplace(_Val); return *this;};
    auto operator=(_Tx&& _Val) -> optional& {_Opt.emplace(std::forward<_Tx>(_Val)); return *this;};

//    auto operator=(const std::nullopt_t&) -> optional& {_Opt.reset();}

public cpp_methods:
    [[nodiscard]] constexpr auto empty() const -> bool {return not _Opt.has_value();}
    [[nodiscard]] constexpr auto has_value() const -> bool {return _Opt.has_value();}

    constexpr auto value() const -> const _Tx& {return _Opt.value();}

    constexpr auto value_or(_Tx&& _Other     ) const ->       _Tx  {return _Opt.value_or(std::forward<_Tx>(_Other));}
    constexpr auto value_or(const _Tx& _Other) const -> const _Tx& {return _Opt.value_or(_Other);}

    template <typename _Ty> constexpr auto value_to_or(_Ty&& _Other     ) const -> _Ty requires std::is_same_v<std::remove_cvref_t<_Tx>, ext::any> {return not empty() ? _Other : value().template to<_Ty>();};
    template <typename _Ty> constexpr auto value_to_or(const _Ty& _Other) const -> _Ty requires std::is_same_v<std::remove_cvref_t<_Tx>, ext::any> {return not empty() ? _Other : value().template to<_Ty>();};

    constexpr auto not_value_or(_Tx&& _Other     ) const -> const _Tx& {return empty() ? null : std::move(_Other);}
    constexpr auto not_value_or(const _Tx& _Other) const -> const _Tx& {return empty() ? null : _Other;}
    
public cpp_operators:
    auto operator->() const -> auto {return _Opt.operator->();}

private cpp_properties:
    std::optional<_Tx> _Opt;
};

#endif //SBROWSER2_OPTIONAL_HPP
