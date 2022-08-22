#pragma once
#ifndef SBROWSER2_STRING_HPP
#define SBROWSER2_STRING_HPP

#include "ext/keywords.hpp"
#include <string>
#include <string_view>


_EXT_BEGIN

using string = std::string;
using string16 = std::u16string;
using string32 = std::u32string;

using string_view = std::string_view;
using string_view16 = std::u16string_view;
using string_view32 = std::u32string_view;

_EXT_END


_EXT_SHORTHAND_BEGIN
using sv = string_view;
_EXT_SHORTHAND_END


_EXT_LITERALS_BEGIN
auto operator"" _es(const char* primitive_string) -> ext::string
{
    return ext::string{primitive_string};
}

auto operator"" _esv(const char* primitive_string) -> ext::string_view
{
    return ext::string_view{primitive_string};
}
_EXT_LITERALS_END


#endif //SBROWSER2_STRING_HPP
