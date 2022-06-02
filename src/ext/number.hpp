#pragma once
#ifndef SBROWSER2_NUMBER_HPP
#define SBROWSER2_NUMBER_HPP

//template <typename T> concept Arithmetic = std::integral<T> or std::floating_point<T>;
namespace ext {template <typename _Tx> class number;}

#include <algorithm>
#include <limits>
#include <ostream>
#include <string>
#include <type_traits>
#include <utility>

#include <ext/keywords.hpp>
#include <ext/detail/infinity.hpp>


template <typename _Tx>
class ext::number final
{
public friends:
    template<typename _Vt> friend class number;

public constructors:
    number(): _Val(0) {};
    ~number() {_Val = 0;};

    number(const number& _Other): _Val(_Other._Val) {}
    number(number&& _Other) noexcept: _Val(std::move(_Other._Val)) {}
    auto operator=(const number& _Other) -> number& {_Val = _Other._Val; return *this;}
    auto operator=(number&& _Other) noexcept -> number& {_Val = std::move(_Other._Val); return *this;}

    number(const _Tx& _Other) = delete;
    number(_Tx&& _Other) noexcept : _Val(std::forward<_Tx>(_Other)) {}
    auto operator=(const _Tx&) = delete;
    auto operator=(_Tx&& _Other) noexcept -> number& {_Val = std::forward<_Tx>(_Other);}

    template <typename _Ty> explicit number(const number<_Ty>& _Other): _Val(static_cast<_Tx>(_Other._Val)) {}
    template <typename _Ty> explicit number(number<_Ty>&& _Other) noexcept: _Val(static_cast<_Tx>(std::move(_Other._Val))) {}
    template <typename _Ty> auto operator=(const number<_Ty>& _Other) -> number& {_Val = static_cast<_Tx>(_Other._Val); return *this;}
    template <typename _Ty> auto operator=(number<_Ty>&& _Other) noexcept -> number& {_Val = static_cast<_Tx>(std::move(_Other._Val)); return *this;}

public cpp_methods:
    template <typename _Ty> auto as() {return number<_Ty>{static_cast<_Ty>(_Val)};}
    auto min() -> _Tx {return std::numeric_limits<_Tx>::min();}
    auto max() -> _Tx {return std::numeric_limits<_Tx>::max();}

public cpp_static_methods:
    static auto INF() -> detail::infinity<_Tx> {return detail::infinity<_Tx>{};};

public cpp_operators:
    template <typename _Ty> auto operator+(_Ty&& _Other) const {return number<_Tx>{_Val + std::forward<_Ty>(_Other)._Val};}
    template <typename _Ty> auto operator-(_Ty&& _Other) const {return number<_Tx>{_Val - std::forward<_Ty>(_Other)._Val};}
    template <typename _Ty> auto operator*(_Ty&& _Other) const {return number<_Tx>{_Val * std::forward<_Ty>(_Other)._Val};}
    template <typename _Ty> auto operator/(_Ty&& _Other) const {return number<_Tx>{_Val / std::forward<_Ty>(_Other)._Val};}
    template <typename _Ty> auto operator%(_Ty&& _Other) const {return number<_Tx>{_Val % std::forward<_Ty>(_Other)._Val};}

    template <typename _Ty> auto operator+=(_Ty&& _Other) {_Val += std::forward<_Ty>(_Other)._Val; return *this;}
    template <typename _Ty> auto operator-=(_Ty&& _Other) {_Val -= std::forward<_Ty>(_Other)._Val; return *this;}
    template <typename _Ty> auto operator*=(_Ty&& _Other) {_Val *= std::forward<_Ty>(_Other)._Val; return *this;}
    template <typename _Ty> auto operator/=(_Ty&& _Other) {_Val /= std::forward<_Ty>(_Other)._Val; return *this;}
    template <typename _Ty> auto operator%=(_Ty&& _Other) {_Val %= std::forward<_Ty>(_Other)._Val; return *this;}

    template <typename _Ty> auto operator<=>(const _Ty& _Other) const {return _Val <=> _Other._Val;}

    template <typename _Ty>
    auto operator==(const number<_Ty>& _Other) const -> bool {return _Val == _Other._Val;}
    auto operator==(_Tx _Other) const -> bool {return _Val == _Other;}
    explicit operator std::string() const {return std::to_string(_Val);}
    explicit operator _Tx() const {return _Val;}

private cpp_properties:
    _Tx _Val;
};


template <typename _Tx>
auto operator<<(std::ostream& _Out, const ext::number<_Tx>& _Val) -> std::ostream&
{
    return _Out << typeid(_Val).name() << ": " << static_cast<_Tx>(_Val) << std::endl;
}


#endif //SBROWSER2_NUMBER_HPP
