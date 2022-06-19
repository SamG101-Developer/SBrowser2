#include "node.hpp"

#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/to_container.hpp>

#include <javascript/environment/realms.hpp>

#include <web_apis/dom/detail/text_internals.hpp>
#include <web_apis/dom/detail/tree_internals.hpp>
#include <web_apis/dom/nodes/character_data.hpp>
#include <web_apis/dom/nodes/node.hpp>
#include <web_apis/dom/nodes/text.hpp>
#include <web_apis/dom/ranges/range.hpp>

namespace dom::nodes {class window;}


dom::nodes::node::node()
        : parent_node(nullptr)
        , child_nodes(std::make_unique<ext::vector<node*>>())
{
    bind_get(base_uri);
    bind_get(first_child);
    bind_get(last_child);
    bind_get(previous_sibling);
    bind_get(next_sibling);

    bind_set(parent_node);
}


auto dom::nodes::node::normalize() -> void
{
    for (nodes::text* text_node: detail::tree_internals::descendant_text_nodes(this))
    {
        // if the length of the text node (ie the length of the text) is 0 then remove the text node
        auto length = dom::detail::tree_internals::length(text_node);
        continue_if(length <= 0);

        // combine the text from the next consecutive text nodes into the text node
        auto data = dom::detail::tree_internals::contiguous_text_nodes(text_node)
                | ranges::views::transform([](nodes::text* text_node) {return text_node->data();})
                | ranges::to<ext::string>();

        // replace the data in this node with the combined data from the contiguous nodes
        detail::text_internals::replace_data(text_node, 0, length, data);

        // get the current node as the next text node (whose text has been combined into the text node's text)
        auto* current_node = text_node->next_sibling();
        auto* live_ranges  = new ext::vector<node_ranges::range*>{}; // TODO javascript::environment::realms::realm<nodes::window*>::surrounding_realm(this).get<ext::vector<node_ranges::range*>*>("live_ranges");

        // iterate by incrementing the current_node to the next sibling
        while (detail::tree_internals::is_exclusive_text_node(current_node))
        {
            // ranges whose starting node is current_node: increment the starting offset by the length of the text of
            // the text node (text has shifted back to previous node) and set the starting node to the text node
            *live_ranges
                    | ranges::views::filter([&current_node](node_ranges::range* range) {return range->start_container == current_node;})
                    | ranges::for_each([&text_node, length](node_ranges::range* range) {range->start_offset += length; range->start_container = text_node;});

            // ranges whose ending node is current_node: increment the ending offset by the length of the text of this
            // text node (text has shifted back to previous node) abd set the ending node to the text node
            *live_ranges
                    | ranges::views::filter([&current_node](node_ranges::range* range) {return range->end_container == current_node;})
                    | ranges::for_each([&text_node, length](node_ranges::range* range) {range->end_offset += length; range->end_container = text_node;});

            // ranges whose starting node is current_node's parent: set the starting offset to the length of the text in
            // the text node and set the starting node to the text node TODO : why?
            live_ranges
                    | ranges::views::filter([&current_node](node_ranges::range* range) {return range->start_container == current_node->parent;})
                    | ranges::for_each([&text_node, length](node_ranges::range* range) {range->start_offset = length; range->start_container = text_node;});

            // ranges whose ending node is current_node's parent: set the ending offset to the length of the text in
            // the text node and set the ending node to the text node TODO : why?
            live_ranges
                    | ranges::views::filter([&current_node](node_ranges::range* range) {return range->end_container == current_node->parent;})
                    | ranges::for_each([&text_node, length](node_ranges::range* range) {range->end_offset = length; range->end_container = text_node;});
        }
    }
}


auto dom::nodes::node::get_previous_sibling() const -> node*
{
    auto* siblings = parent_node->child_nodes();
    auto this_node_iter = std::ranges::find(*siblings, this);
    return this_node_iter != siblings->begin() ? *(this_node_iter - 1) : nullptr;
}


auto dom::nodes::node::get_next_sibling() const -> node*
{
    auto* siblings = parent_node->child_nodes();
    auto this_node_iter = std::ranges::find(*siblings, this);
    return (this_node_iter + 1 != siblings->end()) ? *(this_node_iter + 1) : nullptr;
}


auto dom::nodes::node::get_parent_element() const -> element*
{
    auto* parent_as_node = parent_node();
    auto parent_as_element = dynamic_cast<element*>(parent_as_node);
    return parent_as_element;
}
