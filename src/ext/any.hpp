#pragma once
#ifndef SBROWSER2_ANY_HPP
#define SBROWSER2_ANY_HPP

namespace ext {class any;}

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

    template <typename _Ty> any(const _Ty& _Other) : _Val(_Other) {_Is_numeric = is_template_base_of_v<_Ty, ext::number>;}
    template <typename _Ty> any(_Ty&& _Other) noexcept : _Val(std::forward<_Ty>(_Other)) {_Is_numeric = is_template_base_of_v<_Ty, ext::number>;}
    template <typename _Ty> auto operator=(const _Ty& _Other) -> any&;
    template <typename _Ty> auto operator=(_Ty&& _Other) noexcept -> any&;

public cpp_methods:
    [[nodiscard]] auto type() const -> const type_info& {return _Val.type();}
    [[nodiscard]] auto is_numeric() const -> ext::boolean {return _Is_numeric;}
    [[nodiscard]] auto is_empty() const -> ext::boolean {return not _Val.has_value();}
    [[nodiscard]] auto has_value() const -> ext::boolean {return _Val.has_value();}
    template <typename _Ty> auto to() const -> const _Ty&;

public cpp_operators:
    auto operator==(const any& _Other) const -> ext::boolean {return &_Other._Val == &_Val;}

private cpp_properties:
    std::any _Val;
    ext::boolean _Is_numeric;
};


template <typename _Ty>
auto ext::any::operator=(const _Ty& _Other) -> ext::any&
{
    _Val = _Other;
    _Is_numeric = is_template_base_of_v<_Ty, ext::number>;
    return *this;
}


template <typename _Ty>
auto ext::any::operator=(_Ty&& _Other) noexcept -> any&
{
    _Val = std::forward<_Ty>(_Other);
    _Is_numeric = is_template_base_of_v<_Ty, ext::number>;
    return *this;
}


template <typename _Ty>
inline auto ext::any::to() const -> const _Ty&
{
    // types that are empty or contain a void are mapped to a nullptr or a new object for the _Ty type
    if (is_empty() or type() == typeid(void))
    {
        if constexpr(std::is_pointer_v<_Ty>) return nullptr;
        return _Ty{};
    }

    // otherwise cast the object as the correct type
    return std::any_cast<_Ty>(_Val);
}


#endif //SBROWSER2_ANY_HPP
