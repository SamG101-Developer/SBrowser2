#pragma once
#ifndef SBROWSER2_STRING_HPP
#define SBROWSER2_STRING_HPP

#include "ext/keywords.hpp"
#include "ext/functional.hpp"
#include <sstream>
#include <string>
#include <string_view>
#include <cryptopp/secblock.h>
#include <range/v3/algorithm/fold.hpp>
#include <range/v3/to_container.hpp>


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
    using string = u16string;

    using u8string_view  = std::basic_string_view<char8_t>;
    using u16string_view = std::u16string_view;
    using u32string_view = std::u32string_view;
    using string_view = u16string_view;

    using u8string_stream = std::basic_stringstream<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>>;
    using u16string_stream = std::basic_stringstream<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>;
    using u32string_stream = std::basic_stringstream<char32_t, std::char_traits<char32_t>, std::allocator<char32_t>>;
    using string_stream = u16string_stream;

    auto to_lower = []<typename T>(T character) -> T {return std::tolower(character);};
    auto to_upper = []<typename T>(T character) -> T {return std::toupper(character);};

    template <typename T, ext::type_is<typename T::value_type> ...Args>
    auto sequence_matches(T&& string, Args&&... sequence)
    {return string == ranges::fold_left({sequence...}, u8"", ext::ops::add) | ranges::to<T>();}

    auto random_string() -> ext::string; // TODO : Implement
_EXT_END


_EXT_SECURE_BEGIN
    using string = std::basic_string<_EXT u8string::value_type, _EXT u8string::traits_type, CryptoPP::AllocatorBase<_EXT u8string::value_type>>;
    using string_view = _EXT u8string_view;
    using string_stream = std::basic_stringstream<_EXT string_stream::char_type, _EXT string_stream::traits_type, CryptoPP::AllocatorBase<_EXT string_stream::char_type>>;
_EXT_SECURE_END


_EXT_SHORTHAND_BEGIN
    using sv = u8string_view;
_EXT_SHORTHAND_END


_EXT_LITERALS_BEGIN
    constexpr auto operator"" _s8 (const char8_t* primitive_string, size_t length) {return ext::u8string{primitive_string, length};}
    constexpr auto operator"" _sv8(const char8_t* primitive_string, size_t length) {return ext::u8string_view{primitive_string, length};}

    constexpr auto operator"" _s16 (const char16_t* primitive_string, size_t length) {return ext::u16string{primitive_string, length};}
    constexpr auto operator"" _sv16(const char16_t* primitive_string, size_t length) {return ext::u16string_view{primitive_string, length};}

    constexpr auto operator"" _s32 (const char32_t* primitive_string, size_t length) {return ext::u32string{primitive_string, length};}
    constexpr auto operator"" _sv32(const char32_t* primitive_string, size_t length) {return ext::u32string_view{primitive_string, length};}
_EXT_LITERALS_END


#endif //SBROWSER2_STRING_HPP
