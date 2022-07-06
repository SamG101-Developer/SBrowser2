#pragma once
#ifndef SBROWSER2_NUMBER_HPP
#define SBROWSER2_NUMBER_HPP

#include <ext/type_traits.hpp>
namespace ext {template <primitive_numeric _Tx> class number;}
namespace ext {template <primitive_numeric _Vt> using number_view = const number<_Vt>&;}
namespace ext {template <bool _InclusiveLo = false, bool _InclusiveHi = false> auto is_between(auto&& _Val, auto&& _Lo, auto&& _Hi) -> ext::boolean;}
namespace ext {template <typename T, typename U, typename ...V> auto min(T&& first, U&& second, V&&... values);}
namespace ext {template <typename T, typename U, typename ...V> auto max(T&& first, U&& second, V&&... values);}

#include <algorithm>
#include <limits>
#include <ostream>
#include <string>
#include <type_traits>
#include <utility>

#include <ext/keywords.hpp>
#include <ext/detail/infinity.hpp>


template <primitive_numeric _Tx>
class ext::number final
{
public aliases:
    using primitive_t = _Tx;

public friends:
    template <primitive_numeric _Vt> friend class number;

public constructors:
    number() = default;
    template <primitive_numeric _Ty> constexpr number(_Ty _Primitive);
    template <primitive_numeric _Ty> auto operator=(_Ty _Primitive) -> number&;

    template <primitive_numeric _Ty> explicit number(const number<_Ty>& _Other);
    template <primitive_numeric _Ty> explicit number(number<_Ty>&& _Other) noexcept;
    template <primitive_numeric _Ty> auto operator=(const number<_Ty>& _Other) -> number&;
    template <primitive_numeric _Ty> auto operator=(number<_Ty>&& _Other) noexcept -> number&;
    
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

    template <primitive_numeric _Ty> operator number<_Ty>() const {return number<_Ty>(_Val);}
    template <primitive_numeric _Ty> constexpr operator _Ty() const {return _Val;}

private:
    auto operator*() const -> _Tx {return _Val;}

private cpp_properties:
    _Tx _Val;
};


template <primitive_numeric _Tx>
template <primitive_numeric _Ty>
constexpr ext::number<_Tx>::number(_Ty _Primitive)
        : _Val(_Primitive)
{}


template <primitive_numeric _Tx>
template <primitive_numeric _Ty>
auto ext::number<_Tx>::operator=(_Ty _Primitive) -> number&
{
    _Val = _Primitive;
    return *this;
}


template <primitive_numeric _Tx>
template <primitive_numeric _Ty>
ext::number<_Tx>::number(const number<_Ty>& _Other)
        : _Val(*_Other)
{}


template <primitive_numeric _Tx>
template <primitive_numeric _Ty>
ext::number<_Tx>::number(number<_Ty>&& _Other) noexcept
        : _Val(*std::move(_Other))
{}


template <primitive_numeric _Tx>
template <primitive_numeric _Ty>
auto ext::number<_Tx>::operator=(const ext::number<_Ty>& _Other) -> number&
{
    _Val = *_Other;
    return *this;
}


template <primitive_numeric _Tx>
template <primitive_numeric _Ty>
auto ext::number<_Tx>::operator=(number<_Ty>&& _Other) noexcept -> number&
{
    _Val = *std::move(_Other);
    return *this;
}



template <bool _InclusiveLo, bool _InclusiveHi>
auto ext::is_between(auto&& _Val, auto&& _Lo, auto&& _Hi) -> ext::boolean
{
    auto _Condition1 = _InclusiveLo ? _Val >= _Lo : _Val > _Lo; // default to >
    auto _Condition2 = _InclusiveHi ? _Val <= _Hi : _Val < _Hi; // default to <
    return _Condition1 && _Condition2;
}


template <typename T, typename U, typename ...V>
auto ext::min(T&& first, U&& second, V&&... values)
{
    if constexpr(sizeof...(values) == 0) return first < second ? first : number{second};
    else return min(min(std::forward<T>(first), std::forward<U>(second)), std::forward<V>(values)...);
}


template <typename T, typename U, typename ...V>
auto ext::max(T&& first, U&& second, V&&... values)
{
    if constexpr(sizeof...(values) == 0) return first > second ? first : number{second};
    else return max(max(std::forward<T>(first), std::forward<U>(second)), std::forward<V>(values)...);
}


#endif //SBROWSER2_NUMBER_HPP
