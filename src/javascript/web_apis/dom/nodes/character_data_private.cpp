module;
#include "ext/macros/pimpl.hpp"
#include <range/v3/view/filter.hpp>
#include <range/v3/view/for_each.hpp>

module apis.dom.character_data_private;
import apis.dom.range;
import apis.dom.range_private;
import apis.dom.node;
import apis.dom.node_private;
import apis.dom.text;
import apis.dom.text_private;
import apis.dom.detail;
import apis.dom.types;

import ext.number;
import ext.vector;
import ext.string;

import js.env.slots;
import js.env.realms;


auto dom::character_data_private::replace_data(
        ext::number<ulong> offset,
        ext::number<ulong> count,
        ext::string&& new_data)
        -> void
{
    ACCESS_QIMPL;
    using detail::mutation_type_t;
    using enum detail::dom_exception_error_t;

    // get the length of the Text node, and throw an index size error if the length of the data is greater than the
    // 'offset', as replacing from an offset that si greater than the length of the Text is impossible
    auto text_node_length = length();

    detail::throw_v8_exception<INDEX_SIZE_ERR>(
            [text_node_length, offset] {return offset > text_node_length;},
            u8"The 'offset' must be less than the length of the node");

    // set the 'adjusted_count' to either the 'count', of the 'offset' -- 'length', so the 'count' + 'offset' is either
    // less than or equal to the length of the Text node; the 'adjusted_delete' if the 'offset' + the length of the new
    // data -- this is the start of the data that will be replaced
    decltype(auto) data_size = data.size();
    decltype(auto) adjusted_count = ext::min(count + offset, text_node_length) - offset;
    decltype(auto) adjusted_delete = offset + data.size();

    // queue a CHARACTER_DATA mutation record for the Text node's data changing, and replace the data inside the Text
    // node
    detail::queue_mutation_record(mutation_type_t::CHARACTER_DATA, q, u"", u"", data, {}, {}, nullptr, nullptr);
    data = data.replace(offset, adjusted_count, std::move(data));

    // get the live ranges from the surrounding realm, because these need to be updated for the mutations in the Text
    // node
    auto e = js::env::env::surrounding(q);
    decltype(auto) live_ranges = js::env::get_slot(e, js::env::slots::LIVE_RANGES);

    // ranges whose start container is the Text node and whose start offset is in the data that was replaced: set the
    // start offset to the offset of the data being replaced
    *live_ranges
            | ranges::views::filter([q](auto* range) {return range->d_func()->start->node.get() == q;})
            | ranges::views::filter([=](auto* range) {return ext::is_between<false, true>(range->d_func()->start->offset, offset, offset + adjusted_count);})
            | ranges::views::for_each([offset](auto* range) {range->d_func()->start->offset = offset;});

    // ranges whose end container is the Text node and whose end offset is in the data that was replaced: set the end
    // offset to the offset of the data being replaced
    *live_ranges
            | ranges::views::filter([q](auto* range) {return range->d_func()->end->node.get() == q;})
            | ranges::views::filter([=](auto* range) {return ext::is_between<false, true>(range->d_func()->end->offset, offset, offset + adjusted_count);})
            | ranges::views::for_each([offset](auto* range) {range->d_func()->end->offset = offset;});

    // ranges whose start container is the Text node and whose start offset is after the data that was replaced:
    // increment the start offset by the new data's size, and decrement it by the length of the data that was replaced
    *live_ranges
            | ranges::views::filter([q](auto* range) {return range->d_func()->start->node.get() == q;})
            | ranges::views::filter([=](auto* range) {return range->d_func()->start->offset > offset + adjusted_count;})
            | ranges::views::for_each([data_size, adjusted_count](auto* range) {range->d_func()->start->offset += (data_size - adjusted_count);});

    // ranges whose end container is the Text node and whose end offset is after the data that was replaced: increment
    // the end offset by the new data's size, and decrement it by the length of the data that was replaced
    *live_ranges
            | ranges::views::filter([q](auto* range) {return range->d_func()->end->node.get() == q;})
            | ranges::views::filter([=](auto* range) {return range->d_func()->end->offset > offset + adjusted_count;})
            | ranges::views::for_each([data_size, adjusted_count](auto* range) {range->d_func()->end->offset += (data_size - adjusted_count);});

    // if the Text node has a parent node, the run the 'children_changed_steps' on the parent node, and the Text node
    // child has mutated (data has been replaced)
    if (parent_node)
        parent_node->d_func()->children_changed_steps();
}


auto dom::detail::substring_data(
        ext::number<ulong> offset,
        ext::number<ulong> count)
        const -> ext::string
{
    // get the length of the Text node, and throw an index size error if the length of the data is greater than the
    // 'offset', as substringing from an offset that si greater than the length of the Text is impossible
    using enum detail::dom_exception_error_t;
    auto text_node_length = length();

    detail::throw_v8_exception<INDEX_SIZE_ERR>(
            [text_node_length, offset] {return offset > text_node_length;},
            u8"The 'offset' must be less than the length of the node");

    // set the 'adjusted_count' to either the 'count', of the 'offset' - 'length', so the 'count' + 'offset' is either
    // less than or equal to the length of the Text node, and return the substring from the data (from 'offset',
    // and a length of 'adjusted_count')
    const auto adjusted_count = ext::min(count + offset, text_node_length) - offset;
    return substr(offset, adjusted_count);
}


auto dom::character_data_private::split(
        ext::number<ulong> offset)
        -> std::unique_ptr<text>
{
    // get the length of the Text node, and throw an index size error if the length of the data is greater than the
    // 'offset', as substringing from an offset that si greater than the length of the Text is impossible
    ACCESS_QIMPL;
    using enum detail::dom_exception_error_t;
    auto text_node_length = length();

    detail::throw_v8_exception<INDEX_SIZE_ERR>(
            [text_node_length, offset] {return offset > text_node_length;},
            u8"The 'offset' must be less than the length of the node");

    decltype(auto) count = text_node_length - offset;
    decltype(auto) new_data = substring_data(offset, count);

    auto new_text_node = std::make_unique<text>(std::move(new_data));
    new_text_node->d_func()->node_document = node_document;

    decltype(auto) parent = parent_node;
    if (parent)
    {
        decltype(auto) text_node = new_text_node.get();
        insert(std::move(new_text_node), parent, next_sibling());
        auto e = js::env::env::surrounding(q);

        decltype(auto) live_ranges = js::env::get_slot(e, js::env::slots::LIVE_RANGES);

        *live_ranges
                | ranges::views::filter([q](auto* range) {return range->d_func()->start->node.get() == q;})
                | ranges::views::filter([=](auto* range) {return range->d_func()->start->offset > offset;})
                | ranges::views::for_each([&](auto* range) {range->d_func()->start->node = text_node;})
                | ranges::views::for_each([=](auto* range) {range->d_func()->start->offset -= offset;});

        *live_ranges
                | ranges::views::filter([q](auto* range) {return range->d_func()->end->node == q;})
                | ranges::views::filter([=](auto* range) {return range->d_func()->end->offset > offset;})
                | ranges::views::for_each([&](auto* range) {range->d_func()->end->node = text_node;})
                | ranges::views::for_each([=](auto* range) {range->d_func()->end->offset -= offset;});

        auto node_index = index();
        *live_ranges
                | ranges::views::filter([=](auto* range) {return range->d_func()->start->node == parent;})
                | ranges::views::filter([=](auto* range) {return range->d_func()->start->offset > node_index + 1;})
                | ranges::views::for_each([](auto* range) {range->d_func()->start->offset += 1;});

        node_index = index();
        *live_ranges
                | ranges::views::filter([=](auto* range) {return range->d_func()->end->node == parent;})
                | ranges::views::filter([=](auto* range) {return range->d_func()->end->offset > node_index + 1;})
                | ranges::views::for_each([](auto* range) {range->d_func()->end->offset += 1;});
    }

    replace_data(offset, count, u"");
    return new_text_node;
}

