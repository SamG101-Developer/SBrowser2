#pragma once
#ifndef SBROWSER2_OPTIONAL_HPP
#define SBROWSER2_OPTIONAL_HPP

namespace ext {template <typename _Tx> class optional;}

#include <optional>
#include <ext/keywords.hpp>

namespace ext {constexpr auto null = std::nullopt_t::_Tag{};};


template <typename _Tx>
class ext::optional final
{
public:
    optional(const optional&) = delete;
    optional(optional&&) noexcept = default;
    auto operator=(const optional&) -> optional& = delete;
    auto operator=(optional&&) noexcept -> optional& = default;

    optional() = default;
    explicit optional(const _Tx& _Val) : _Opt(std::make_optional<_Tx>(_Val)) {}
    explicit optional(_Tx&& _Val) noexcept : _Opt(std::make_optional<_Tx>(std::forward<_Tx>(_Val))) {}
    auto operator=(const _Tx& _Val) -> optional& {_Opt.emplace(_Val); return *this;};
    auto operator=(_Tx&& _Val) -> optional& {_Opt.emplace(std::forward<_Tx>(_Val)); return *this;};

    auto operator=(const std::nullopt_t&) -> optional& {_Opt.reset();}

public:
    [[nodiscard]] constexpr auto empty() const -> bool {return not _Opt.has_value();}
    [[nodiscard]] constexpr auto has_value() const -> bool {return _Opt.has_value();}

    constexpr auto value() const -> const _Tx& {return _Opt.value();}

    constexpr auto value_or(_Tx&& _Other     ) const ->       _Tx  {return _Opt.value_or(std::forward<_Tx>(_Other));}
    constexpr auto value_or(const _Tx& _Other) const -> const _Tx& {return _Opt.value_or(_Other);}

    constexpr auto not_value_or(_Tx&& _Other     ) const -> const _Tx& {return empty() ? null : std::forward<_Tx>(_Other);}
    constexpr auto not_value_or(const _Tx& _Other) const -> const _Tx& {return empty() ? null : _Other;}

private:
    std::optional<_Tx> _Opt;
};

#endif //SBROWSER2_OPTIONAL_HPP
