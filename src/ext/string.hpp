#pragma once
#ifndef SBROWSER2_STRING_HPP
#define SBROWSER2_STRING_HPP

#include "ext/keywords.hpp"
#include <string>
#include <string_view>
#include <cryptopp/secblock.h>


_EXT_BEGIN
    using octet_t = char8_t;
    using octet_string = std::basic_string<octet_t, std::char_traits<octet_t>, std::allocator<octet_t>>;
    using octet_string_view = std::basic_string_view<octet_t>;

    using byte_t = char8_t;
    using byte_string = std::basic_string<byte_t, std::char_traits<byte_t>, std::allocator<byte_t>>;
    using byte_string_view = std::basic_string_view<byte_t>;

    using u8string  = std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>;
    using u16string = std::u16string;
    using u32string = std::u32string;
    using string = u8string;

    using u8string_view  = std::basic_string_view<char8_t>;
    using u16string_view = std::u16string_view;
    using u32string_view = std::u32string_view;
    using string_view = u8string_view;

    auto to_lower = []<typename T>(T character) -> T {return std::tolower(character);};
    auto to_upper = []<typename T>(T character) -> T {return std::toupper(character);};
_EXT_END


_EXT_SECURE_BEGIN
    using string = std::basic_string<_EXT string::value_type, _EXT string::traits_type, CryptoPP::AllocatorBase<_EXT string::value_type>>;
    using string_view = _EXT string_view;
_EXT_SECURE_END


_EXT_SHORTHAND_BEGIN
    using sv = string_view;
_EXT_SHORTHAND_END


_EXT_LITERALS_BEGIN
    constexpr auto operator"" _es (const char8_t* primitive_string, size_t length) {return ext::string{primitive_string, length};}
    constexpr auto operator"" _esv(const char8_t* primitive_string, size_t length) {return ext::string_view{primitive_string, length};}
_EXT_LITERALS_END


#endif //SBROWSER2_STRING_HPP
