#pragma once
#ifndef SBROWSER2_BOOLEAN_HPP
#define SBROWSER2_BOOLEAN_HPP

#include "ext/pimpl.hpp"
#include <utility>


_EXT_BEGIN

class boolean final
{
public constructors:
    constexpr boolean() = default;
    boolean(const boolean&) = default;
    boolean(boolean&&) noexcept = default;
    auto operator=(const boolean&) -> ext::boolean& = default;
    auto operator=(boolean&&) noexcept -> ext::boolean& = default;
    constexpr ~boolean() {m_value = false;};

    constexpr boolean(bool other) : m_value{other} {}
    auto operator=(bool other) -> boolean& {m_value = other; return *this;}

public:
    static auto FALSE_() -> boolean {return boolean{false};};
    static auto TRUE_ () -> boolean {return boolean{true };};

    operator bool() const {return m_value;}
    auto operator !() const -> bool {return !m_value;}

    bool m_value;
};


enum class bool_string_t {_, TRUE, FALSE};

_EXT_END


_EXT_SHORTHAND_BEGIN
using bv = const boolean&;
_EXT_DETAIL_END


#endif //SBROWSER2_BOOLEAN_HPP
