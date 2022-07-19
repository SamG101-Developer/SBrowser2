#pragma once
#ifndef SBROWSER2_ANY_HPP
#define SBROWSER2_ANY_HPP

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/concepts.hpp"
#include "ext/keywords.hpp"
#include <any>


_EXT_BEGIN class any; _EXT_END

template <typename _Tx>
concept not_any = !type_is<_Tx, _EXT any>;


_EXT_BEGIN

class any final
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
    [[nodiscard]] auto is_numeric() const -> _EXT boolean {return _IsNumeric;}
    [[nodiscard]] auto is_empty() const -> _EXT boolean {return not _Any.has_value();}
    [[nodiscard]] auto has_value() const -> _EXT boolean {return _Any.has_value();}
    template <typename _Ty> auto to() const -> _Ty {return std::any_cast<_Ty>(_Any);};

public cpp_operators:
    auto operator==(const any& _Other) const -> bool {return &_Other._Any == &_Any;}
    template <not_any T> auto operator==(T&& _Other) const -> bool {return std::forward<T>(_Other) == to<T>();}

private cpp_properties:
    std::any _Any;
    _EXT boolean _IsNumeric;
};


using any_view = const _EXT any&;

_EXT_END


_EXT any::any(auto&& _Val) noexcept
        : _Any(std::forward<decltype(_Val)>(_Val))
        , _IsNumeric(inherit_template<_EXT number, decltype(_Val)>)
{}


auto _EXT any::operator=(const auto& _Val) -> _EXT any&
{
    _Any = _Val;
    _IsNumeric = inherit_template<_EXT number, decltype(_Val)>;
    return *this;
}


auto _EXT any::operator=(auto&& _Val) noexcept -> any&
{
    _Any = std::forward<decltype(_Val)>(_Val);
    _IsNumeric = inherit_template<_EXT number, decltype(_Val)>;
    return *this;
}


#endif //SBROWSER2_ANY_HPP
