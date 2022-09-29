#pragma once
#ifndef SBROWSER2_SRC_EXT_STREAMS_HPP
#define SBROWSER2_SRC_EXT_STREAMS_HPP

#include "ext/keywords.hpp"
#include "ext/string.hpp"
#include <fmt/format.h>


_EXT_BEGIN

/*
 * https://codereview.stackexchange.com/questions/263749/codewars-kata-converting-snake-case-identifiers-to-camelcase-in-c
 * https://codereview.stackexchange.com/a/263761/211871
 * https://codereview.stackexchange.com/users/42409/deduplicator
 */
constexpr auto snake_to_camel(
        ext::string string)
        noexcept -> ext::string
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

_EXT_END


#endif //SBROWSER2_SRC_EXT_STREAMS_HPP
