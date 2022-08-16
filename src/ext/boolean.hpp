#pragma once
#ifndef SBROWSER2_BOOLEAN_HPP
#define SBROWSER2_BOOLEAN_HPP

#include "ext/keywords.hpp"
#include <utility>


_EXT_BEGIN

class boolean final
{
public constructors:
    constexpr boolean(bool other = false) : internal_boolean(other) {}
    auto operator=(bool other) -> boolean& {internal_boolean = other; return *this;}

public cpp_methods:
    static auto FALSE_() -> boolean {return boolean{false};};
    static auto TRUE_ () -> boolean {return boolean{true };};

public cpp_properties:
    operator bool() const {return internal_boolean;}
    auto operator !() const -> bool {return internal_boolean ^ true;}

private cpp_properties:
    bool internal_boolean;
};

_EXT_END


_EXT_SHORTHAND_BEGIN
using bv = const boolean&;
_EXT_DETAIL_END


#endif //SBROWSER2_BOOLEAN_HPP
