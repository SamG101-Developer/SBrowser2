export module ext.boolean;
import std.core

#include "ext/keywords.hpp"


_EXT_BEGIN
    export class boolean;
    enum class bool_string_t {_, TRUE, FALSE};
_EXT_END


_EXT_SHORTHAND_BEGIN
    using bv = const boolean&;
_EXT_DETAIL_END


class ext::boolean final
{
public constructors:
    constexpr boolean() = default;
    constexpr boolean(bool other) : m_value{other} {}
    auto operator=(bool other) -> boolean& {m_value = other; return *this;}

public:
    static auto FALSE_() -> boolean {return boolean{false};};
    static auto TRUE_ () -> boolean {return boolean{true };};

    operator bool() const {return m_value;}
    auto operator !() const -> bool {return !m_value;}

    bool m_value;
};
