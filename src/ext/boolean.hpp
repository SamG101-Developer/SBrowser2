#pragma once
#ifndef SBROWSER2_BOOLEAN_HPP
#define SBROWSER2_BOOLEAN_HPP

namespace ext {class boolean;}
namespace ext {using boolean_view = const boolean&;}
using bv = ext::boolean_view;

#include "ext/keywords.hpp"
#include <utility>


class ext::boolean final
{
public:
    constexpr boolean() : _Boolean(false) {}

    constexpr boolean(const bool& _Other) : _Boolean(_Other) {};
    constexpr boolean(bool&& _Other) : _Boolean(std::forward<bool>(_Other)) {}
    auto operator=(const bool& _Other) -> boolean& {_Boolean = _Other; return *this;};
    auto operator=(bool&& _Other) -> boolean& {_Boolean = std::forward<bool>(_Other); return *this;}

public:
    static auto FALSE() -> ext::boolean {return ext::boolean{false};};
    static auto TRUE () -> ext::boolean {return ext::boolean{true };};

public:
    operator bool() const {return _Boolean;}
    auto operator !() const -> bool {return _Boolean ^ true;}

private:
    bool _Boolean;
};


#endif //SBROWSER2_BOOLEAN_HPP
