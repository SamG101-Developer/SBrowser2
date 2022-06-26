#ifndef SBROWSER2_TEXT_INTERNALS_HPP
#define SBROWSER2_TEXT_INTERNALS_HPP

#include <ext/number.hpp>
#include <ext/string.hpp>
#include <ext/type_traits.hpp>

#include <web_apis/dom/detail/exception_internals.hpp>
#include <web_apis/dom/detail/tree_internals.hpp>
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
            const nodes::character_data* text_node,
            ext::number_view<ulong> offset,
            ext::number_view<ulong> count)
            -> ext::string;

    auto split(
            nodes::character_data* text_node,
            ext::number_view<ulong> offset)
            -> nodes::text*;
}


auto dom::detail::text_internals::replace_data(
        nodes::character_data* text_node, ext::number_view<ulong> offset, ext::number_view<ulong> count,
        ext::string_view data) -> void
{
    auto length = tree_internals::length(text_node);

    exception_internals::throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            "The 'offset' must be less than the length of the node",
            {"Length of the node is smaller than it should be", "Offset is too big"},
            {"Check that the node contains the information expected", "Make the offset smaller"},
            {{"Length", length}, {"Offset", offset}},
            [length, offset] {return length > offset;});
}


#endif //SBROWSER2_TEXT_INTERNALS_HPP
