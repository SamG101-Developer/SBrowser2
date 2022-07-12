#ifndef SBROWSER2_TEXT_INTERNALS_HPP
#define SBROWSER2_TEXT_INTERNALS_HPP

#include "ext/number.hpp"
#include "ext/string.hpp"
namespace dom::nodes {class character_data;}
namespace dom::nodes {class text;}


namespace dom::detail::text_internals
{
    auto replace_data(
            nodes::character_data* text_node,
            ext::number_view<ulong> offset,
            ext::number_view<ulong> count,
            ext::string_view data)
            -> void;

    auto substring_data(
            nodes::character_data* text_node,
            ext::number_view<ulong> offset,
            ext::number_view<ulong> count)
            -> ext::string;

    auto split(
            nodes::character_data* existing_text_node,
            ext::number_view<ulong> offset)
            -> nodes::text*;
}


#endif //SBROWSER2_TEXT_INTERNALS_HPP
