#include "text_internals.hpp"

#include <web_apis/dom/detail/exception_internals.hpp>
#include <web_apis/dom/detail/mutation_internals.hpp>
#include <web_apis/dom/detail/observer_internals.hpp>
#include <web_apis/dom/detail/tree_internals.hpp>

#include <web_apis/dom/nodes/element.hpp>
#include <web_apis/dom/nodes/document.hpp>
#include <web_apis/dom/nodes/shadow_root.hpp>
#include <web_apis/dom/nodes/text.hpp>

#include <web_apis/dom/other/dom_implementation.hpp>
#include <web_apis/dom/ranges/range.hpp>

#include <web_apis/url/url.hpp>

#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view/filter.hpp>


auto dom::detail::text_internals::replace_data(
        nodes::character_data* text_node,
        ext::number_view<ulong> offset,
        ext::number_view<ulong> count,
        ext::string_view data) -> void
{
    // get the length of the Text node, and throw an index size error if the length of the data is greater than the
    // 'offset', as replacing from an offset that si greater than the length of the Text is impossible
    auto length = tree_internals::length(text_node);

    exception_internals::throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            [length, offset] {return offset > length;},
            "The 'offset' must be less than the length of the node",
            {"Length of the node is smaller than it should be", "Offset is too big"},
            {"Check that the node contains the information expected", "Make the offset smaller"},
            P("Length", length), P("Offset", offset));

    // set the 'adjusted_count' to either the 'count', of the 'offset' - 'length', so the 'count' + 'offset' is either
    // less than or equal to the length of the Text node; the 'adjusted_delete' if the 'offset' + the length of the new
    // data - this is the start of the data that will be replaced
    auto adjusted_count = ext::min(count + offset, length) - offset;
    auto adjusted_delete = offset + data.size();

    // queue a CHARACTER_DATA mutation record for the Text node's data changing, and replace the data inside the Text
    // node
    detail::observer_internals::queue_mutation_record(observer_internals::CHARACTER_DATA, text_node, "", "", text_node->data(), {}, {}, nullptr, nullptr);
    text_node->data->replace(offset, adjusted_count, data);

    // get the live ranges from the surrounding realm, because these need to be updated for the mutations in the Text
    // node
    JS_REALM_GET_SURROUNDING(text_node)
    auto live_ranges = javascript::environment::realms_2::get<ext::vector<node_ranges::range*>>(surrounding_global_object, "live_ranges");

    // ranges whose start container is the Text node and whose start offset is in the data that was replaced: set the
    // start offset to the offset of the data being replaced
    ranges::for_each(
            live_ranges | ranges::views::filter([text_node, offset, adjusted_count](node_ranges::range* range) {return range->start_container() == text_node && ext::is_between<_F, _T>(range->start_offset(), offset, offset + adjusted_count);}),
            [offset](node_ranges::range* live_range) {live_range->start_offset = offset;});

    // ranges whose end container is the Text node and whose end offset is in the data that was replaced: set the end
    // offset to the offset of the data being replaced
    ranges::for_each(
            live_ranges | ranges::views::filter([text_node, offset, adjusted_count](node_ranges::range* range) {return range->end_container() == text_node && ext::is_between<_F, _T>(range->end_offset(), offset, offset + adjusted_count);}),
            [offset](node_ranges::range* live_range) {live_range->end_offset = offset;});

    // ranges whose start container is the Text node and whose start offset is after the data that was replaced:
    // increment the start offset by the new data's size, and decrement it by the length of the data that was replaced
    ranges::for_each(
            live_ranges | ranges::views::filter([text_node, offset, adjusted_count](node_ranges::range* range) {return range->start_container() == text_node && range->start_offset() > offset + adjusted_count;}),
            [data, adjusted_count](node_ranges::range* live_range) {live_range->start_offset += (data.size() - adjusted_count);});

    // ranges whose end container is the Text node and whose end offset is after the data that was replaced: increment
    // the end offset by the new data's size, and decrement it by the length of the data that was replaced
    ranges::for_each(
            live_ranges | ranges::views::filter([text_node, offset, adjusted_count](node_ranges::range* range) {return range->end_container() == text_node && range->end_offset() > offset + adjusted_count;}),
            [data, adjusted_count](node_ranges::range* live_range) {live_range->end_offset += (data.size() - adjusted_count);});

    // if the Text node has a parent node, the run the 'children_changed_steps' on the parent node, and the Text node
    // child has mutated (data has been replaced)
    if (text_node->parent_node())
        text_node->parent_node->m_dom_behaviour.children_changed_steps();
}


auto dom::detail::text_internals::substring_data(
         nodes::character_data* text_node,
        ext::number_view<ulong> offset,
        ext::number_view<ulong> count)
        -> ext::string
{
    // get the length of the Text node, and throw an index size error if the length of the data is greater than the
    // 'offset', as substringing from an offset that si greater than the length of the Text is impossible
    auto length = tree_internals::length(text_node);

    exception_internals::throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            [length, offset] {return offset > length;},
            "The 'offset' must be less than the length of the node",
            {"Length of the node is smaller than it should be", "Offset is too big"},
            {"Check that the node contains the information expected", "Make the offset smaller"},
            P("Length", length), P("Offset", offset));

    // set the 'adjusted_count' to either the 'count', of the 'offset' - 'length', so the 'count' + 'offset' is either
    // less than or equal to the length of the Text node, and return the substring from the data (from 'offset',
    // and a length of 'adjusted_count')
    auto adjusted_count = ext::min(count + offset, length) - offset;
    return text_node->data->substr(offset, adjusted_count);
}


auto dom::detail::text_internals::split(
        nodes::character_data* existing_text_node,
        ext::number_view<ulong> offset)
        -> nodes::text*
{
    // get the length of the Text node, and throw an index size error if the length of the data is greater than the
    // 'offset', as substringing from an offset that si greater than the length of the Text is impossible
    auto length = tree_internals::length(existing_text_node);

    exception_internals::throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            [length, offset] {return offset > length;},
            "The 'offset' must be less than the length of the node",
            {"Length of the node is smaller than it should be", "Offset is too big"},
            {"Check that the node contains the information expected", "Make the offset smaller"},
            P("Length", length), P("Offset", offset));

    auto count = length - offset;
    auto new_data = substring_data(existing_text_node, offset, count);

    auto* new_text_node = std::make_unique<nodes::text>(new_data).get();
    new_text_node->owner_document = existing_text_node->owner_document();

    auto parent = existing_text_node->parent_node();
    if (parent)
    {
        mutation_internals::insert(new_text_node, parent, existing_text_node->next_sibling());

        JS_REALM_GET_SURROUNDING(existing_text_node)
        auto live_ranges = javascript::environment::realms_2::get<ext::vector<node_ranges::range*>>(surrounding_global_object, "live_ranges");

        ranges::for_each(
                live_ranges | ranges::views::filter([existing_text_node, offset](node_ranges::range* range) {return range->start_container() == existing_text_node && range->start_offset() > offset;}),
                [new_text_node, offset](node_ranges::range* range) {range->start_container = new_text_node; range->start_offset -= offset;});

        ranges::for_each(
                live_ranges | ranges::views::filter([existing_text_node, offset](node_ranges::range* range) {return range->end_container() == existing_text_node && range->end_offset() > offset;}),
                [new_text_node, offset](node_ranges::range* range) {range->end_container = new_text_node; range->end_offset -= offset;});

        ranges::for_each(
                live_ranges | ranges::views::filter([parent, index = tree_internals::index(existing_text_node)](node_ranges::range* range) {return range->start_container() == parent && range->start_offset() > index + 1;}),
                [](node_ranges::range* range) {range->start_offset += 1;});

        ranges::for_each(
                live_ranges | ranges::views::filter([parent, index = tree_internals::index(existing_text_node)](node_ranges::range* range) {return range->end_container() == parent && range->end_offset() > index + 1;}),
                [](node_ranges::range* range) {range->end_offset += 1;});
    }

    replace_data(existing_text_node, offset, count, "");
    return new_text_node; // TODO copy CTors with using base::base() etc...
}
