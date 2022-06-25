#pragma once
#ifndef SBROWSER2_NUMBER_HPP
#define SBROWSER2_NUMBER_HPP

#include <ext/type_traits.hpp>
namespace ext {template <primitive_numeric _Tx> class number;}
namespace ext {template <primitive_numeric _Vt> using number_view = const number<_Vt>&;}

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
public friends:
    template<primitive_numeric _Vt> friend class number;

public constructors:
    number(): _Val(0) {};
    ~number() {_Val = 0;};

    number(const number& _Other): _Val(_Other._Val) {}
    number(number&& _Other) noexcept: _Val(std::move(_Other._Val)) {}
    auto operator=(const number& _Other) -> number& {_Val = _Other._Val; return *this;}
    auto operator=(number&& _Other) noexcept -> number& {_Val = std::move(_Other._Val); return *this;}

    number(const _Tx& _Other) : _Val(_Other) {};
    number(_Tx&& _Other) noexcept : _Val(std::forward<_Tx>(_Other)) {}
    auto operator=(const _Tx&) = delete;
    auto operator=(_Tx&& _Other) noexcept -> number& {_Val = std::forward<_Tx>(_Other);}

    template <primitive_numeric _Ty> explicit number(const number<_Ty>& _Other): _Val(static_cast<_Tx>(_Other._Val)) {}
    template <primitive_numeric _Ty> explicit number(number<_Ty>&& _Other) noexcept: _Val(static_cast<_Tx>(std::move(_Other._Val))) {}
    template <primitive_numeric _Ty> auto operator=(const number<_Ty>& _Other) -> number& {_Val = static_cast<_Tx>(_Other._Val); return *this;}
    template <primitive_numeric _Ty> auto operator=(number<_Ty>&& _Other) noexcept -> number& {_Val = static_cast<_Tx>(std::move(_Other._Val)); return *this;}

public cpp_methods:
    auto min() const -> ext::number<_Tx> {return std::numeric_limits<_Tx>::min();}
    auto max() const -> ext::number<_Tx> {return std::numeric_limits<_Tx>::max();}

public cpp_static_methods:
    static auto INF() -> detail::infinity<_Tx> {return detail::infinity<_Tx>{};};

public cpp_operators:
    auto operator+(primitive_numeric auto _Other) const -> auto {return number{_Val + _Other};}
    auto operator-(primitive_numeric auto _Other) const -> auto {return number{_Val - _Other};}
    auto operator*(primitive_numeric auto _Other) const -> auto {return number{_Val * _Other};}
    auto operator/(primitive_numeric auto _Other) const -> auto {return number{_Val / _Other};}
    auto operator%(primitive_numeric auto _Other) const -> auto {return number{_Val % _Other};}

    auto operator+=(primitive_numeric auto _Other) -> auto& {_Val += _Other; return *this;}
    auto operator-=(primitive_numeric auto _Other) -> auto& {_Val -= _Other; return *this;}
    auto operator*=(primitive_numeric auto _Other) -> auto& {_Val *= _Other; return *this;}
    auto operator/=(primitive_numeric auto _Other) -> auto& {_Val /= _Other; return *this;}
    auto operator%=(primitive_numeric auto _Other) -> auto& {_Val %= _Other; return *this;}

    auto operator<=>(primitive_numeric auto _Other) const -> ext::boolean {return _Val <=> static_cast<_Tx>(_Other);}

    explicit operator std::string() const {return std::to_string(_Val);}
    operator _Tx() const {return _Val;}
    template <primitive_numeric _Ty> operator number<_Ty>() {return number<_Ty>{static_cast<_Ty>(_Val)};}

private cpp_properties:
    _Tx _Val;
};


#endif //SBROWSER2_NUMBER_HPP
