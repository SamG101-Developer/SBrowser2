#include "text_internals.hpp"




#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/mutation_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/detail/range_internals.hpp"
#include "dom/detail/tree_internals.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/shadow_root.hpp"
#include "dom/nodes/text.hpp"
#include "dom/nodes/text_private.hpp"
#include "dom/other/dom_implementation.hpp"
#include "dom/ranges/range.hpp"
#include "dom/ranges/range_private.hpp"

#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view/filter.hpp>


auto dom::detail::replace_data(
        nodes::character_data* text_node,
        ext::number<ulong> offset,
        ext::number<ulong> count,
        ext::string&& data) -> void
{
    using detail::mutation_type_t;
    using enum detail::dom_exception_error_t;

    // get the length of the Text node, and throw an index size error if the length of the data is greater than the
    // 'offset', as replacing from an offset that si greater than the length of the Text is impossible
    auto text_node_length = length(text_node);

    throw_v8_exception<INDEX_SIZE_ERR>(
            [text_node_length, offset] {return offset > text_node_length;},
            u8"The 'offset' must be less than the length of the node",
            {u8"Length of the node is smaller than it should be", "Offset is too big"},
            {u8"Check that the node contains the information expected", "Make the offset smaller"},
            P(u8"Length", text_node_length), P(u8"Offset", offset));

    // set the 'adjusted_count' to either the 'count', of the 'offset' - 'length', so the 'count' + 'offset' is either
    // less than or equal to the length of the Text node; the 'adjusted_delete' if the 'offset' + the length of the new
    // data - this is the start of the data that will be replaced
    decltype(auto) data_size = data.size();
    decltype(auto) adjusted_count = ext::min(count + offset, text_node_length) - offset;
    decltype(auto) adjusted_delete = offset + data.size();

    // queue a CHARACTER_DATA mutation record for the Text node's data changing, and replace the data inside the Text
    // node
    queue_mutation_record(mutation_type_t::CHARACTER_DATA, text_node, u"", u"", text_node->d_func()->data, {}, {}, nullptr, nullptr);
    text_node->d_func->data = text_node->d_func()->data.replace(offset, adjusted_count, std::move(data));

    // get the live ranges from the surrounding realm, because these need to be updated for the mutations in the Text
    // node
    auto e = js::env::env::surrounding(text_node);
    decltype(auto) live_ranges = js::env::get_slot<ext::vector<node_ranges::range*>*>(e, js::global_slots::live_ranges);

    // ranges whose start container is the Text node and whose start offset is in the data that was replaced: set the
    // start offset to the offset of the data being replaced
    *live_ranges
            | ranges::views::filter([=](auto* range) {return range->d_func()->start->node == text_node;})
            | ranges::views::filter([=](auto* range) {return ext::is_between<false, true>(range->d_func()->start->offset, offset, offset + adjusted_count);})
            | ranges::views::for_each([offset](auto* range) {range->d_func()->start->offset = offset;});

    // ranges whose end container is the Text node and whose end offset is in the data that was replaced: set the end
    // offset to the offset of the data being replaced
    *live_ranges
            | ranges::views::filter([=](auto* range) {return range->d_func()->end->node == text_node;})
            | ranges::views::filter([=](auto* range) {return ext::is_between<false, true>(range->d_func()->end->offset, offset, offset + adjusted_count);})
            | ranges::views::for_each([offset](auto* range) {range->d_func()->end->offset = offset;});

    // ranges whose start container is the Text node and whose start offset is after the data that was replaced:
    // increment the start offset by the new data's size, and decrement it by the length of the data that was replaced
    *live_ranges
            | ranges::views::filter([=](auto* range) {return range->d_func()->start->node == text_node;})
            | ranges::views::filter([=](auto* range) {return range->d_func()->start->offset > offset + adjusted_count;})
            | ranges::views::for_each([data_size, adjusted_count](auto* range) {range->d_func()->start->offset += (data_size - adjusted_count);});

    // ranges whose end container is the Text node and whose end offset is after the data that was replaced: increment
    // the end offset by the new data's size, and decrement it by the length of the data that was replaced
    *live_ranges
            | ranges::views::filter([=](auto* range) {return range->d_func()->end->node == text_node;})
            | ranges::views::filter([=](auto* range) {return range->d_func()->end->offset > offset + adjusted_count;})
            | ranges::views::for_each([data_size, adjusted_count](auto* range) {range->d_func()->end->offset += (data_size - adjusted_count);});

    // if the Text node has a parent node, the run the 'children_changed_steps' on the parent node, and the Text node
    // child has mutated (data has been replaced)
    if (text_node->d_func()->parent_node)
        text_node->d_func()->parent_node->d_func()->children_changed_steps();
}


auto dom::detail::substring_data(
        const nodes::character_data* const text_node,
        ext::number<ulong> offset,
        ext::number<ulong> count)
        -> ext::string
{
    // get the length of the Text node, and throw an index size error if the length of the data is greater than the
    // 'offset', as substringing from an offset that si greater than the length of the Text is impossible
    using enum detail::dom_exception_error_t;
    auto text_node_length = length(text_node);

    throw_v8_exception<INDEX_SIZE_ERR>(
            [text_node_length, offset] {return offset > text_node_length;},
            u8"The 'offset' must be less than the length of the node",
            {u8"Length of the node is smaller than it should be", "Offset is too big"},
            {u8"Check that the node contains the information expected", "Make the offset smaller"},
            P(u8"Length", length), P(u8"Offset", offset));

    // set the 'adjusted_count' to either the 'count', of the 'offset' - 'length', so the 'count' + 'offset' is either
    // less than or equal to the length of the Text node, and return the substring from the data (from 'offset',
    // and a length of 'adjusted_count')
    const auto adjusted_count = ext::min(count + offset, text_node_length) - offset;
    return text_node->d_func()->data.substr(offset, adjusted_count);
}


auto dom::detail::split(
        nodes::character_data* const existing_text_node,
        ext::number<ulong> offset)
        -> std::unique_ptr<nodes::text>
{
    // get the length of the Text node, and throw an index size error if the length of the data is greater than the
    // 'offset', as substringing from an offset that si greater than the length of the Text is impossible
    using enum detail::dom_exception_error_t;
    auto text_node_length = length(existing_text_node);

    throw_v8_exception<INDEX_SIZE_ERR>(
            [text_node_length, offset] {return offset > text_node_length;},
            u8"The 'offset' must be less than the length of the node",
            {u8"Length of the node is smaller than it should be", "Offset is too big"},
            {u8"Check that the node contains the information expected", "Make the offset smaller"},
            P(u8"Length", text_node_length), P(u8"Offset", offset));

    decltype(auto) count = text_node_length - offset;
    decltype(auto) new_data = substring_data(existing_text_node, offset, count);

    auto new_text_node = std::make_unique<nodes::text>(std::move(new_data));
    new_text_node->d_func()->node_document = existing_text_node->d_func()->node_document;

    decltype(auto) parent = existing_text_node->d_func()->parent_node;
    if (parent)
    {
        auto text_node = new_text_node.get();
        insert(std::move(new_text_node), parent, detail::next_sibling(existing_text_node));
        auto e = js::env::env::surrounding(existing_text_node);

        decltype(auto) live_ranges = js::env::get_slot<ext::vector<node_ranges::range*>*>(e, js::global_slots::live_ranges);

        *live_ranges
                | ranges::views::filter([=](auto* range) {return range->d_func()->start->node == existing_text_node;})
                | ranges::views::filter([=](auto* range) {return range->d_func()->start->offset > offset;})
                | ranges::views::for_each([=](auto* range) {range->d_func()->start->node = text_node;})
                | ranges::views::for_each([=](auto* range) {range->d_func()->start->offset = range->d_func()->start->offset - offset;});

        *live_ranges
                | ranges::views::filter([=](auto* range) {return range->d_func()->end->node == existing_text_node;})
                | ranges::views::filter([=](auto* range) {return range->d_func()->end->offset > offset;})
                | ranges::views::for_each([=](auto* range) {range->d_func()->end->node = text_node;})
                | ranges::views::for_each([=](auto* range) {range->d_func()->end->offset = range->d_func()->end->offset - offset;});

        auto node_index = index(existing_text_node);
        *live_ranges
                | ranges::views::filter([=](auto* range) {return range->d_func()->start->node == parent;})
                | ranges::views::filter([=](auto* range) {return range->d_func()->start->offset > node_index + 1;})
                | ranges::views::for_each([](auto* range) {range->d_func()->start->offset += 1;});

        node_index = index(existing_text_node);
        *live_ranges
                | ranges::views::filter([=](auto* range) {return range->d_func()->end->node == parent;})
                | ranges::views::filter([=](auto* range) {return range->d_func()->end->offset > node_index + 1;})
                | ranges::views::for_each([](auto* range) {range->d_func()->end->offset += 1;});
    }

    replace_data(existing_text_node, offset, count, u"");
    return new_text_node;
}
