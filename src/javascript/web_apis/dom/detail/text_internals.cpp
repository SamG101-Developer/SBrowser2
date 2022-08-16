#include "text_internals.hpp"

#include "dom/detail/exception_internals.hpp"
#include "dom/detail/mutation_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/detail/tree_internals.hpp"

#include "dom/nodes/element.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/shadow_root.hpp"
#include "dom/nodes/text.hpp"

#include "dom/other/dom_implementation.hpp"
#include "dom/ranges/range.hpp"

#include "url/url.hpp"

#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view/filter.hpp>


auto dom::detail::replace_data(
        nodes::character_data* text_node,
        const ext::number<ulong>& offset,
        const ext::number<ulong>& count,
        const ext::string_view data) -> void
{
    using detail::mutation_type_t;

    // get the length of the Text node, and throw an index size error if the length of the data is greater than the
    // 'offset', as replacing from an offset that si greater than the length of the Text is impossible
    auto length = tree_internals::length(text_node);

    throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            [length, offset] {return offset > length;},
            "The 'offset' must be less than the length of the node",
            {"Length of the node is smaller than it should be", "Offset is too big"},
            {"Check that the node contains the information expected", "Make the offset smaller"},
            P("Length", length), P("Offset", offset));

    // set the 'adjusted_count' to either the 'count', of the 'offset' - 'length', so the 'count' + 'offset' is either
    // less than or equal to the length of the Text node; the 'adjusted_delete' if the 'offset' + the length of the new
    // data - this is the start of the data that will be replaced
    const auto adjusted_count = ext::min(count + offset, length) - offset;
    const auto adjusted_delete = offset + data.size();

    // queue a CHARACTER_DATA mutation record for the Text node's data changing, and replace the data inside the Text
    // node
    queue_mutation_record(mutation_type_t::CHARACTER_DATA, text_node, "", "", text_node->data(), {}, {}, nullptr, nullptr);
    text_node->data = text_node->data().replace(offset, adjusted_count, data);

    // get the live ranges from the surrounding realm, because these need to be updated for the mutations in the Text
    // node
    JS_REALM_GET_SURROUNDING(text_node)
    const auto live_ranges = javascript::environment::realms_2::get<ext::vector<node_ranges::range*>>(text_node_surrounding_global_object, "live_ranges");

    // ranges whose start container is the Text node and whose start offset is in the data that was replaced: set the
    // start offset to the offset of the data being replaced
    ranges::for_each(
            live_ranges | ranges::views::filter([text_node, offset, adjusted_count](const node_ranges::range* const range) {return range->start_container() == text_node && ext::is_between<_F, _T>(range->start_offset(), offset, offset + adjusted_count);}),
            [offset](node_ranges::range* const live_range) {live_range->start_offset = offset;});

    // ranges whose end container is the Text node and whose end offset is in the data that was replaced: set the end
    // offset to the offset of the data being replaced
    ranges::for_each(
            live_ranges | ranges::views::filter([text_node, offset, adjusted_count](const node_ranges::range* const range) {return range->end_container() == text_node && ext::is_between<_F, _T>(range->end_offset(), offset, offset + adjusted_count);}),
            [offset](node_ranges::range* const live_range) {live_range->end_offset = offset;});

    // ranges whose start container is the Text node and whose start offset is after the data that was replaced:
    // increment the start offset by the new data's size, and decrement it by the length of the data that was replaced
    ranges::for_each(
            live_ranges | ranges::views::filter([text_node, offset, adjusted_count](const node_ranges::range* const range) {return range->start_container() == text_node && range->start_offset() > offset + adjusted_count;}),
            [data, adjusted_count](node_ranges::range* const live_range) {live_range->start_offset += (data.size() - adjusted_count);});

    // ranges whose end container is the Text node and whose end offset is after the data that was replaced: increment
    // the end offset by the new data's size, and decrement it by the length of the data that was replaced
    ranges::for_each(
            live_ranges | ranges::views::filter([text_node, offset, adjusted_count](const node_ranges::range* const range) {return range->end_container() == text_node && range->end_offset() > offset + adjusted_count;}),
            [data, adjusted_count](node_ranges::range* const live_range) {live_range->end_offset += (data.size() - adjusted_count);});

    // if the Text node has a parent node, the run the 'children_changed_steps' on the parent node, and the Text node
    // child has mutated (data has been replaced)
    if (text_node->parent_node())
        text_node->parent_node()->m_dom_behaviour.children_changed_steps();
}


auto dom::detail::substring_data(
        const nodes::character_data* const text_node,
        const ext::number<ulong>& offset,
        const ext::number<ulong>& count)
        -> ext::string
{
    // get the length of the Text node, and throw an index size error if the length of the data is greater than the
    // 'offset', as substringing from an offset that si greater than the length of the Text is impossible
    auto length = tree_internals::length(text_node);

    throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            [length, offset] {return offset > length;},
            "The 'offset' must be less than the length of the node",
            {"Length of the node is smaller than it should be", "Offset is too big"},
            {"Check that the node contains the information expected", "Make the offset smaller"},
            P("Length", length), P("Offset", offset));

    // set the 'adjusted_count' to either the 'count', of the 'offset' - 'length', so the 'count' + 'offset' is either
    // less than or equal to the length of the Text node, and return the substring from the data (from 'offset',
    // and a length of 'adjusted_count')
    const auto adjusted_count = ext::min(count + offset, length) - offset;
    return text_node->data().substr(offset, adjusted_count);
}


auto dom::detail::split(
        nodes::character_data* const existing_text_node,
        const ext::number<ulong>& offset)
        -> nodes::text
{
    // get the length of the Text node, and throw an index size error if the length of the data is greater than the
    // 'offset', as substringing from an offset that si greater than the length of the Text is impossible
    auto length = tree_internals::length(existing_text_node);

    throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            [length, offset] {return offset > length;},
            "The 'offset' must be less than the length of the node",
            {"Length of the node is smaller than it should be", "Offset is too big"},
            {"Check that the node contains the information expected", "Make the offset smaller"},
            P("Length", length), P("Offset", offset));

    const auto count = length - offset;
    auto new_data = substring_data(existing_text_node, offset, count);

    nodes::text new_text_node {new_data};
    new_text_node.owner_document = existing_text_node->owner_document();

    auto* const parent = existing_text_node->parent_node();
    if (parent)
    {
        insert(&new_text_node, parent, existing_text_node->next_sibling());

        JS_REALM_GET_SURROUNDING(existing_text_node)
        const auto live_ranges = javascript::environment::realms_2::get<ext::vector<node_ranges::range*>>(existing_text_node_surrounding_global_object, "live_ranges");

        ranges::for_each(
                live_ranges | ranges::views::filter([existing_text_node, offset](const node_ranges::range* const range) {return range->start_container() == existing_text_node && range->start_offset() > offset;}),
                [&new_text_node, offset](node_ranges::range* const range) {range->start_container = &new_text_node; range->start_offset() = range->start_offset() - offset;});

        ranges::for_each(
                live_ranges | ranges::views::filter([existing_text_node, offset](const node_ranges::range* const range) {return range->end_container() == existing_text_node && range->end_offset() > offset;}),
                [&new_text_node, offset](node_ranges::range* const range) {range->end_container = &new_text_node; range->end_offset() = range->end_offset() - offset;});

        ranges::for_each(
                live_ranges | ranges::views::filter([parent, index = tree_internals::index(existing_text_node)](const node_ranges::range* const range) {return range->start_container() == parent && range->start_offset() > index + 1;}),
                [](node_ranges::range* const range) {range->start_offset += 1;});

        ranges::for_each(
                live_ranges | ranges::views::filter([parent, index = tree_internals::index(existing_text_node)](const node_ranges::range* const range) {return range->end_container() == parent && range->end_offset() > index + 1;}),
                [](node_ranges::range* const range) {range->end_offset += 1;});
    }

    replace_data(existing_text_node, offset, count, "");
    return new_text_node;
}
