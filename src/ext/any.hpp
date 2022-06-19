#pragma once
#ifndef SBROWSER2_ANY_HPP
#define SBROWSER2_ANY_HPP

namespace ext {class any;}
namespace ext {using any_view = const any&;}

#include <any>
#include <ext/boolean.hpp>
#include <ext/number.hpp>
#include <ext/type_traits.hpp>
#include <ext/keywords.hpp>


class ext::any final
{
public constructors:
    any() = default;
    ~any() = default;

    any(const any&) = default;
    any(any&&) noexcept = default;
    auto operator=(const any&) -> any& = default;
    auto operator=(any&&) noexcept -> any& = default;

    template <typename _Ty> any(const _Ty& _Val) : _Any(_Val) {_IsNumeric = is_template_base_of_v<_Ty, ext::number>;}
    template <typename _Ty> any(_Ty&& _Val) noexcept : _Any(std::forward<_Ty>(_Val)) {_IsNumeric = is_template_base_of_v<_Ty, ext::number>;}
    template <typename _Ty> auto operator=(const _Ty& _Val) -> any&;
    template <typename _Ty> auto operator=(_Ty&& _Val) noexcept -> any&;

public cpp_methods:
    [[nodiscard]] auto type() const -> const type_info& {return _Any.type();}
    [[nodiscard]] auto is_numeric() const -> ext::boolean {return _IsNumeric;}
    [[nodiscard]] auto is_empty() const -> ext::boolean {return not _Any.has_value();}
    [[nodiscard]] auto has_value() const -> ext::boolean {return _Any.has_value();}
    template <typename _Ty> auto to() const -> _Ty {return std::any_cast<_Ty>(_Any);};

public cpp_operators:
    auto operator==(const any& _Other) const -> ext::boolean {return &_Other._Any == &_Any;}

private cpp_properties:
    std::any _Any;
    ext::boolean _IsNumeric;
};


template <typename _Ty>
auto ext::any::operator=(const _Ty& _Val) -> ext::any&
{
    _Any = _Val;
    _IsNumeric = is_template_base_of_v<_Ty, ext::number>;
    return *this;
}


template <typename _Ty>
auto ext::any::operator=(_Ty&& _Val) noexcept -> any&
{
    _Any = std::forward<_Ty>(_Val);
    _IsNumeric = is_template_base_of_v<_Ty, ext::number>;
    return *this;
}


#endif //SBROWSER2_ANY_HPP
