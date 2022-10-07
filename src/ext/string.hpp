#pragma once
#ifndef SBROWSER2_STRING_HPP
#define SBROWSER2_STRING_HPP

#include "ext/keywords.hpp"
#include <string>
#include <string_view>


_EXT_BEGIN

using u8string  = std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>;
using u16string = std::u16string;
using u32string = std::u32string;
using string = u8string;

using u8string_view  = std::basic_string_view<char8_t>;
using u16string_view = std::u16string_view;
using u32string_view = std::u32string_view;
using string_view = u8string_view;

_EXT_END


_EXT_SHORTHAND_BEGIN
using sv = string_view;
_EXT_SHORTHAND_END


_EXT_LITERALS_BEGIN
constexpr auto operator"" _es (const char* primitive_string, size_t length) {return ext::string{(const char8_t*)primitive_string, length};}
constexpr auto operator"" _esv(const char* primitive_string, size_t length) {return ext::string_view{(const char8_t*)primitive_string, length};}
_EXT_LITERALS_END


#endif //SBROWSER2_STRING_HPP
