#pragma once
#ifndef SBROWSER2_STRING_HPP
#define SBROWSER2_STRING_HPP

#include "ext/allocator.hpp"
#include "ext/concepts.hpp"
#include "ext/functional.hpp"
#include <sstream>
#include <string>
#include <string_view>
#include <cryptopp/secblock.h>
#include <range/v3/algorithm/fold.hpp>
#include <range/v3/to_container.hpp>


_EXT_BEGIN
    // Define aliases
    using octet_t = char8_t;
    using octet_string = std::basic_string<octet_t, std::char_traits<octet_t>, _EXT allocator<octet_t>>;
    using octet_string_view = std::basic_string_view<octet_t>;

    using byte_t = char8_t;
    using byte_string = std::basic_string<byte_t, std::char_traits<byte_t>, _EXT allocator<byte_t>>;
    using byte_string_view = std::basic_string_view<byte_t>;

    // Define all string types, default is utf16 encoding
    using u8string  = std::basic_string<char8_t, std::char_traits<char8_t>, _EXT allocator<char8_t>>;
    using u16string = std::u16string;
    using u32string = std::u32string;
    using string = u16string;

    // Define all string view types, default is utf16 encoding
    using u8string_view  = std::basic_string_view<char8_t>;
    using u16string_view = std::u16string_view;
    using u32string_view = std::u32string_view;
    using string_view = u16string_view;

    // Define all string stream types, default is utf16 encoding
    using u8string_stream = std::basic_stringstream<char8_t, std::char_traits<char8_t>, _EXT allocator<char8_t>>;
    using u16string_stream = std::basic_stringstream<char16_t, std::char_traits<char16_t>, _EXT allocator<char16_t>>;
    using u32string_stream = std::basic_stringstream<char32_t, std::char_traits<char32_t>, _EXT allocator<char32_t>>;
    using string_stream = u16string_stream;

    // Use better lower and upper conversion methods
    auto to_lower = []<typename T>(T character) -> T {return std::tolower(character);};
    auto to_upper = []<typename T>(T character) -> T {return std::toupper(character);};

    // Allow comparison of a string against a seqeunce of characters
    template <typename T, ext::type_is<typename T::value_type> ...Args>
    auto sequence_matches(T&& string, Args&&... sequence)
    {return string == ranges::fold_left({sequence...}, u8"", ext::ops::add) | ranges::to<T>();}

    // Random string generation
    auto random_string() -> ext::string;

    // Define concepts and struct for strings and string views
    template <typename T>
    concept string_like = requires
    {ext::type_is_any_specialization<T, std::basic_string>;};

    template <string_like T>
    struct view_of
    {using type = std::basic_string_view<typename T::value_type, typename T::traits_type>;};

    template <string_like T>
    using view_of_t = typename view_of<std::remove_cvref_t<T>>::type;
_EXT_END


_EXT_SECURE_BEGIN
    using string = std::basic_string<_EXT string::value_type, _EXT u8string::traits_type, _EXT secure::allocator<_EXT string::value_type>>;
    using string_view = _EXT string_view;
    using string_stream = std::basic_stringstream<_EXT string_stream::char_type, _EXT string_stream::traits_type, _EXT secure::allocator<_EXT string_stream::char_type>>;
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
