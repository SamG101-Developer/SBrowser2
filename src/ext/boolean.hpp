#pragma once
#ifndef SBROWSER2_BOOLEAN_HPP
#define SBROWSER2_BOOLEAN_HPP

namespace ext {class boolean;}
namespace ext {using boolean_view = const boolean&;}
using bv = ext::boolean_view;

#include "ext/keywords.hpp"
#include "ext/type_traits.hpp"
#include <utility>


class ext::boolean final
{
public constructors:
    constexpr boolean(bool _Other = false) : _Boolean(_Other) {}
    auto operator=(bool _Other) -> boolean& {_Boolean = _Other; return *this;}

public cpp_methods:
    static auto FALSE() -> ext::boolean {return ext::boolean{false};};
    static auto TRUE () -> ext::boolean {return ext::boolean{true };};

public cpp_properties:
    operator bool() const {return _Boolean;}
    auto operator !() const -> bool {return _Boolean ^ true;}

private cpp_properties:
    bool _Boolean;
};


#endif //SBROWSER2_BOOLEAN_HPP
