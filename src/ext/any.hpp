#pragma once
#ifndef SBROWSER2_ANY_HPP
#define SBROWSER2_ANY_HPP

namespace ext {class any;}
namespace ext {using any_view = const any&;}

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/type_traits.hpp"
#include "ext/keywords.hpp"
#include <any>


template <typename _Tx>
concept not_any = !type_is<_Tx, ext::any>;


class ext::any final
{
public constructors:
    any() = default;
    ~any() = default;

    any(const any&) = default;
    any(any&&) noexcept = default;
    auto operator=(const any&) -> any& = default;
    auto operator=(any&&) noexcept -> any& = default;

    any(auto&& _Val) noexcept;
    auto operator=(const auto& _Val) -> any&;
    auto operator=(auto&& _Val) noexcept -> any&;

public cpp_methods:
    [[nodiscard]] auto type() const -> const type_info& {return _Any.type();}
    [[nodiscard]] auto is_numeric() const -> ext::boolean {return _IsNumeric;}
    [[nodiscard]] auto is_empty() const -> ext::boolean {return not _Any.has_value();}
    [[nodiscard]] auto has_value() const -> ext::boolean {return _Any.has_value();}
    template <typename _Ty> auto to() const -> _Ty {return std::any_cast<_Ty>(_Any);};

public cpp_operators:
    auto operator==(const any& _Other) const -> bool {return &_Other._Any == &_Any;}
    template <not_any T> auto operator==(T&& _Other) const -> bool {return std::forward<T>(_Other) == to<T>();}

private cpp_properties:
    std::any _Any;
    ext::boolean _IsNumeric;
};


ext::any::any(auto&& _Val) noexcept
        : _Any(std::forward<decltype(_Val)>(_Val))
        , _IsNumeric(inherit_template<ext::number, decltype(_Val)>)
{}


auto ext::any::operator=(const auto& _Val) -> ext::any&
{
    _Any = _Val;
    _IsNumeric = inherit_template<ext::number, decltype(_Val)>;
    return *this;
}


auto ext::any::operator=(auto&& _Val) noexcept -> any&
{
    _Any = std::forward<decltype(_Val)>(_Val);
    _IsNumeric = inherit_template<ext::number, decltype(_Val)>;
    return *this;
}


#endif //SBROWSER2_ANY_HPP
