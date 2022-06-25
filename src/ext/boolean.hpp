#pragma once
#ifndef SBROWSER2_BOOLEAN_HPP
#define SBROWSER2_BOOLEAN_HPP

namespace ext {class boolean;}
namespace ext {using boolean_view = const boolean&;}
using bv = ext::boolean_view;

#include <utility>
#include <ext/keywords.hpp>


class ext::boolean final
{
public:
    constexpr boolean() : _Val(false) {}

    constexpr boolean(const bool& _Other) : _Val(_Other) {};
    constexpr boolean(bool&& _Other) : _Val(std::forward<bool>(_Other)) {}
    auto operator=(const bool& _Other) -> boolean& {_Val = _Other; return *this;};
    auto operator=(bool&& _Other) -> boolean& {_Val = std::forward<bool>(_Other); return *this;}

public:
    static auto FALSE() -> ext::boolean {return ext::boolean{false};};
    static auto TRUE () -> ext::boolean {return ext::boolean{true };};

public:
    operator bool() const {return _Val;}
    auto operator !() const -> bool {return _Val ^ true;}

private:
    bool _Val;
};


#endif //SBROWSER2_BOOLEAN_HPP
