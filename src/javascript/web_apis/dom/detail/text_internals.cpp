#include "text_internals.hpp"

#include <web_apis/dom/detail/exception_internals.hpp>
#include <web_apis/dom/detail/tree_internals.hpp>
#include <web_apis/dom/nodes/text.hpp>


auto dom::detail::text_internals::replace_data(
        nodes::character_data* text_node, ext::number_view<ulong> offset, ext::number_view<ulong> count,
        ext::string_view data) -> void
{
    auto length = tree_internals::length(text_node);

    exception_internals::throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            [length, offset] {return length > offset;},
            "The 'offset' must be less than the length of the node",
            {"Length of the node is smaller than it should be", "Offset is too big"},
            {"Check that the node contains the information expected", "Make the offset smaller"},
            P("Length", length), P("Offset", offset));
}
