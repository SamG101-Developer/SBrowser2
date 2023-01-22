module;
#include "ext/macros/namespaces.hpp"
#include <string>
#include <sstream>
#include <range/v3/algorithm/fold.hpp>
#include <range/v3/to_container.hpp>


export module ext.core:string;

import :allocator;
import :concepts;
import :functional;


_EXT_BEGIN
    // Define concepts and struct for strings and string views
    export template <typename T>
    concept string_like =
            _EXT type_is_any_specialization<T, std::basic_string>;

    export template <typename T>
    concept string_view_like =
            _EXT type_is_any_specialization<T, std::basic_string_view>;

    export template <typename T>
    concept char_like =
            _EXT type_is<T, char8_t, char16_t, char32_t>;

    // Define aliases
    export using octet_t = char8_t;
    export using octet_string = std::basic_string<octet_t, std::char_traits<octet_t>, _EXT allocator<octet_t>>;

    export using byte_t = char8_t;
    export using byte_string = std::basic_string<byte_t, std::char_traits<byte_t>, _EXT allocator<byte_t>>;

    // Define all string types, default is utf16 encoding
    export template <_EXT char_like T> using any_string = std::basic_string<T, std::char_traits<T>, _EXT allocator<T>>;
    export using u8string  = std::u8string;
    export using u16string = std::u16string;
    export using u32string = std::u32string;
    export using string = u16string;

    // Define all string view types, default is utf16 encoding
    export template <_EXT char_like T> using any_string_view = std::basic_string_view<T>;
    export using u8string_view  = std::u8string_view;
    export using u16string_view = std::u16string_view;
    export using u32string_view = std::u32string_view;
    export using string_view = u16string_view;

    // Define all string stream types, default is utf16 encoding
    export template <_EXT char_like T> using any_string_stream = std::basic_stringstream<T, std::char_traits<T>, _EXT allocator<T>>;
    export using u8string_stream = std::basic_stringstream<char8_t, std::char_traits<char8_t>, _EXT allocator<char8_t>>;
    export using u16string_stream = std::basic_stringstream<char16_t, std::char_traits<char16_t>, _EXT allocator<char16_t>>;
    export using u32string_stream = std::basic_stringstream<char32_t, std::char_traits<char32_t>, _EXT allocator<char32_t>>;
    export using string_stream = u16string_stream;

    // Use better lower and upper conversion methods
    export auto to_lower = []<_EXT char_like T>(T character) -> T {return std::tolower(character);};
    export auto to_upper = []<_EXT char_like T>(T character) -> T {return std::toupper(character);};

    // Allow comparison of a string against a seqeunce of characters
    export template <typename T, _EXT type_is<typename T::value_type> ...Args>
    auto sequence_matches(T&& string, Args&&... sequence)
    {return string == ranges::fold_left({sequence...}, T{}, _EXT ops::add) | ranges::to<T>();}

    // Random string generation
    export auto random_string() -> _EXT string;

    export template <_EXT string_like S>
    constexpr auto snake_to_camel(S&& string) noexcept -> S;
_EXT_END


_EXT_SECURE_BEGIN
    export using string = std::basic_string<_EXT string::value_type, _EXT string::traits_type, _EXT secure::allocator<_EXT string::value_type>>;
    export using string_view = _EXT string_view;
    export using string_stream = std::basic_stringstream<_EXT string_stream::char_type, _EXT string_stream::traits_type, _EXT secure::allocator<_EXT string_stream::char_type>>;
_EXT_SECURE_END


_EXT_SHORTHAND_BEGIN
    export using sv = string_view;
_EXT_SHORTHAND_END


_EXT_LITERALS_BEGIN
    export constexpr auto operator"" _s8 (const char8_t* primitive_string, size_t length) {return _EXT u8string{primitive_string, length};}
    export constexpr auto operator"" _sv8(const char8_t* primitive_string, size_t length) {return _EXT u8string_view{primitive_string, length};}

    export constexpr auto operator"" _s16 (const char16_t* primitive_string, size_t length) {return _EXT u16string{primitive_string, length};}
    export constexpr auto operator"" _sv16(const char16_t* primitive_string, size_t length) {return _EXT u16string_view{primitive_string, length};}

    export constexpr auto operator"" _s32 (const char32_t* primitive_string, size_t length) {return _EXT u32string{primitive_string, length};}
    export constexpr auto operator"" _sv32(const char32_t* primitive_string, size_t length) {return _EXT u32string_view{primitive_string, length};}
_EXT_LITERALS_END


template <_EXT string_like S>
constexpr auto ext::snake_to_camel(S&& string) noexcept -> S
{
    bool tail = false;
    size_t n = 0;

    for (decltype(auto) character: string)
    {
        if (character == '-' || character == '_')
            tail = false;
        else if (tail)
            string[n++] = character;
        else
        {
            tail = true;
            string[n++] = std::toupper(character);
        }
    }

    string.resize(n);
    return string;
}


/*
 * https://codereview.stackexchange.com/questions/263749/codewars-kata-converting-snake-case-identifiers-to-camelcase-in-c
 * https://codereview.stackexchange.com/a/263761/211871
 * https://codereview.stackexchange.com/users/42409/deduplicator
 */
