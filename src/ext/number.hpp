#pragma once
#ifndef SBROWSER2_NUMBER_HPP
#define SBROWSER2_NUMBER_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "ext/detail/infinity.hpp"
#include "boolean.hpp"

#include <algorithm>
#include <limits>
#include <ostream>
#include <string>
#include <type_traits>
#include <utility>


_EXT_BEGIN

template <typename _Tx> // TODO : change typename to 'primitive_number'
class number final
{
public aliases:
    using primitive_t = _Tx;

public friends:
    template <typename _Vt> friend class number;

public constructors:
    number() = default;
    template <typename _Ty> constexpr number(_Ty _Primitive);
    template <typename _Ty> auto operator=(_Ty _Primitive) -> number&;

    template <typename _Ty> explicit number(const number<_Ty>& _Other);
    template <typename _Ty> explicit number(number<_Ty>&& _Other) noexcept;
    template <typename _Ty> auto operator=(const number<_Ty>& _Other) -> number&;
    template <typename _Ty> auto operator=(number<_Ty>&& _Other) noexcept -> number&;
    
public cpp_methods:
    auto min() const -> number<_Tx> {return std::numeric_limits<_Tx>::min();}
    auto max() const -> number<_Tx> {return std::numeric_limits<_Tx>::max();}

public cpp_static_methods:
    static auto INF() -> detail::infinity<_Tx> {return detail::infinity<_Tx>{};};

public cpp_operators:
    // conversion operators
    explicit operator std::string() const {return std::to_string(_Val);}

    auto operator+(auto&& other) const {return number{_Val + std::forward<_Tx>(other)};}
    auto operator-(auto&& other) const {return number{_Val - std::forward<_Tx>(other)};}
    auto operator*(auto&& other) const {return number{_Val * std::forward<_Tx>(other)};}
    auto operator/(auto&& other) const {return number{_Val / std::forward<_Tx>(other)};}
    auto operator%(auto&& other) const {return number{_Val % std::forward<_Tx>(other)};}
    auto operator|(auto&& other) const {return number{_Val | std::forward<_Tx>(other)};}
    auto operator&(auto&& other) const {return number{_Val & std::forward<_Tx>(other)};}
    auto operator<<(auto&& other) const {return number{_Val << std::forward<_Tx>(other)};}
    auto operator>>(auto&& other) const {return number{_Val >> std::forward<_Tx>(other)};}

    auto operator+=(auto&& other) {_Val += std::forward<_Tx>(other); return *this;}
    auto operator-=(auto&& other) {_Val -= std::forward<_Tx>(other); return *this;}
    auto operator*=(auto&& other) {_Val *= std::forward<_Tx>(other); return *this;}
    auto operator/=(auto&& other) {_Val /= std::forward<_Tx>(other); return *this;}
    auto operator%=(auto&& other) {_Val %= std::forward<_Tx>(other); return *this;}
    auto operator|=(auto&& other) {_Val |= std::forward<_Tx>(other); return *this;}
    auto operator&=(auto&& other) {_Val &= std::forward<_Tx>(other); return *this;}
    auto operator<<=(auto&& other) {_Val <<= std::forward<_Tx>(other); return *this;}
    auto operator>>=(auto&& other) {_Val >>= std::forward<_Tx>(other); return *this;}

    auto operator==(const auto& other) const -> bool {return _Val == other;}
    auto operator<=>(const auto& other) const {return _Val <=> other;}

    auto operator++() -> number& {++_Val; return *this;}
    auto operator--() -> number& {--_Val; return *this;}

    template <typename _Ty> operator number<_Ty>() const {return number<_Ty>(_Val);}
    template <typename _Ty> constexpr operator _Ty() const {return _Val;}

private:
    auto operator*() const -> _Tx {return _Val;}

private cpp_properties:
    _Tx _Val;
};


template <typename _Vt>
using number_view = const number<_Vt>&;

_EXT_END


template <typename _Tx>
template <typename _Ty>
constexpr _EXT number<_Tx>::number(_Ty _Primitive)
        : _Val(_Primitive)
{}


template <typename _Tx>
template <typename _Ty>
auto _EXT number<_Tx>::operator=(_Ty _Primitive) -> number&
{
    _Val = _Primitive;
    return *this;
}


template <typename _Tx>
template <typename _Ty>
_EXT number<_Tx>::number(const _EXT number<_Ty>& _Other)
        : _Val(*_Other)
{}


template <typename _Tx>
template <typename _Ty>
_EXT number<_Tx>::number(_EXT number<_Ty>&& _Other) noexcept
        : _Val(*std::move(_Other))
{}


template <typename _Tx>
template <typename _Ty>
auto _EXT number<_Tx>::operator=(const _EXT number<_Ty>& _Other) -> number&
{
    _Val = *_Other;
    return *this;
}


template <typename _Tx>
template <typename _Ty>
auto _EXT number<_Tx>::operator=(_EXT number<_Ty>&& _Other) noexcept -> number&
{
    _Val = *std::move(_Other);
    return *this;
}


_EXT_BEGIN

template <bool _InclusiveLo, bool _InclusiveHi>
auto is_between(auto&& _Val, auto&& _Lo, auto&& _Hi) -> _EXT boolean
{
    auto _Condition1 = _InclusiveLo ? _Val >= _Lo : _Val > _Lo; // default to >
    auto _Condition2 = _InclusiveHi ? _Val <= _Hi : _Val < _Hi; // default to <
    return _Condition1 && _Condition2;
}


template <typename T, typename U, typename ...V>
auto min(T&& _Val0, U&& _Val1, V&&... _Vals)
{
    if constexpr(sizeof...(_Vals) == 0) return _Val0 < _Val1 ? _Val0 : number{_Val1};
    else return _EXT min(_EXT min(std::forward<T>(_Val0), std::forward<U>(_Val1)), std::forward<V>(_Vals)...);
}


template <typename T, typename U, typename ...V>
auto max(T&& _Val0, U&& _Val1, V&&... _Vals)
{
    if constexpr(sizeof...(_Vals) == 0) return _Val0 > _Val1 ? _Val0 : number{_Val1};
    else return _EXT max(_EXT max(std::forward<T>(_Val0), std::forward<U>(_Val1)), std::forward<V>(_Vals)...);
}


template <typename T, typename U>
auto round(T&& _Val, U&& _Mult)
{
    return std::round(std::move(_Val / _Mult)) * std::forward<U>(_Mult);
}


auto is_numeric_string(const _EXT string& _Str) -> _EXT boolean
{
    try {auto _Num = std::stod(_Str); return _EXT boolean::TRUE();}
    catch_specific (std::invalid_argument) {return _EXT boolean::FALSE();}
}


_EXT_END


#endif //SBROWSER2_NUMBER_HPP
