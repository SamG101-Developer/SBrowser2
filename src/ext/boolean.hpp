#pragma once
#ifndef SBROWSER2_BOOLEAN_HPP
#define SBROWSER2_BOOLEAN_HPP

#include "ext/keywords.hpp"
#include <utility>


_EXT_BEGIN

class boolean final
{
public constructors:
    constexpr boolean(bool _Other = false) : _Boolean(_Other) {}
    auto operator=(bool _Other) -> boolean& {_Boolean = _Other; return *this;}

public cpp_methods:
    static auto FALSE() -> _EXT boolean {return _EXT boolean{false};};
    static auto TRUE () -> _EXT boolean {return _EXT boolean{true };};

public cpp_properties:
    operator bool() const {return _Boolean;}
    auto operator !() const -> bool {return _Boolean ^ true;}

private cpp_properties:
    bool _Boolean;
};

using boolean_view = const boolean&;

_EXT_END


using bv = _EXT boolean_view;


#endif //SBROWSER2_BOOLEAN_HPP
