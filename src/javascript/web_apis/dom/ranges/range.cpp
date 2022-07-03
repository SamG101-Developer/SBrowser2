#include "range.hpp"

#include <ext/casting.hpp>
#include <ext/ranges.hpp>

#include <javascript/environment/realms_2.hpp>

#include <web_apis/dom/nodes/comment.hpp>
#include <web_apis/dom/nodes/document.hpp>
#include <web_apis/dom/nodes/document_fragment.hpp>
#include <web_apis/dom/nodes/processing_instruction.hpp>
#include <web_apis/dom/nodes/text.hpp>

#include <web_apis/dom/detail/exception_internals.hpp>
#include <web_apis/dom/detail/mutation_internals.hpp>
#include <web_apis/dom/detail/range_internals.hpp>
#include <web_apis/dom/detail/text_internals.hpp>
#include <web_apis/dom/detail/tree_internals.hpp>

namespace dom::nodes {class window;}


dom::node_ranges::range::range()
{
    bind_get(common_ancestor_container);

    JS_REALM_GET_CURRENT
    start_container = javascript::environment::realms_2::get<nodes::document*>(current_global_object, "associated_document");
    end_container   = javascript::environment::realms_2::get<nodes::document*>(current_global_object, "associated_document");
    start_offset    = 0;
    end_offset      = 0;

    m_root = nullptr;
}


auto dom::node_ranges::range::set_start(
        nodes::node* new_container,
        ext::number_view<ulong> new_offset)
        -> void
{
    // set the start of this range to the 'new_container' and 'new_offset' variables, by calling the detail method with
    // the same variables
    detail::range_internals::set_start_or_end(this, new_container, new_offset, true);
}


auto dom::node_ranges::range::set_start_before(
        nodes::node* new_container)
        -> void
{
    // set the start of this range to be before the 'new_container', by calling the detail method with the parent of the
    // 'new_container' and the index of the 'new_container' as the offset
    verify_parent_exists(new_container);
    auto parent_node = new_container->parent_node();
    auto new_offset  = detail::tree_internals::index(new_container);
    detail::range_internals::set_start_or_end(this, parent_node, new_offset, true);
}


auto dom::node_ranges::range::set_start_after(
        nodes::node* new_container)
        -> void
{
    // set the start of this range to be after the 'new_container', by calling the detail method with the parent of the
    // 'new_container' and the index of the 'new_container' + 1 as the offset
    verify_parent_exists(new_container);
    auto parent_node = new_container->parent_node();
    auto new_offset  = detail::tree_internals::index(new_container) + 1;
    detail::range_internals::set_start_or_end(this, parent_node, new_offset, true);
}


auto dom::node_ranges::range::set_end(
        nodes::node* new_container,
        ext::number_view<ulong> new_offset)
        -> void
{
    detail::range_internals::set_start_or_end(this, new_container, new_offset, false);
}


auto dom::node_ranges::range::set_end_before(
        nodes::node* new_container)
        -> void
{
    // set the end of this range to be before the 'new_container', by calling the detail method with the parent of the
    // 'new_container' and the index of the 'new_container' as the offset
    verify_parent_exists(new_container);
    auto parent_node = new_container->parent_node();
    auto new_offset  = detail::tree_internals::index(new_container);
    detail::range_internals::set_start_or_end(this, parent_node, new_offset, false);
}


auto dom::node_ranges::range::set_end_after(
        nodes::node* new_container)
        -> void
{
    // set the end of this range to be before the 'new_container', by calling the detail method with the parent of the
    // 'new_container' and the index of the 'new_container' + 1 as the offset
    verify_parent_exists(new_container);
    auto parent_node = new_container->parent_node();
    auto new_offset  = detail::tree_internals::index(new_container) + 1;
    detail::range_internals::set_start_or_end(this, parent_node, new_offset, false);
}


auto dom::node_ranges::range::insert_node(
        nodes::node* new_container)
        -> void
{
    detail::exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
            [this, new_container]
            {return ext::multi_cast<nodes::comment*, nodes::processing_instruction*>(start_container())
                    || dynamic_cast<nodes::text*>(start_container()) && !new_container->parent_node()
                    || start_container() == new_container;},
            "Cannot insert a new container into a Range whose start node is a Comment/ProcessingInstruction, an orphaned Text node, or is the new container");

    // the 'reference_node' is the node that the 'new_container' will be inserted before; if the start container is a
    // Text node, then set the 'reference_node' to the start container (insert before all the text), otherwise the
    // child of the non-Text start container whose index is the offset (exact correct node)
    auto* reference_node = dynamic_cast<nodes::text*>(start_container())
            ? start_container()
            : ranges::first_where(*start_container->child_nodes(), [this](nodes::node* child_node) {return detail::tree_internals::index(child_node) == start_offset();});

    // the 'parent_node' is the parent that the 'new_container' is going to be inserted into; if there is no
    // 'reference_node', then the parent is the start container, otherwise it's the reference node's parent node (the
    // 'new_container' will be inserted before the 'reference_node' into the 'parent_node'
    auto* parent_node = !reference_node
            ? start_container()
            : reference_node->parent_node();

    // if the reference node is a Text node, set it to everything after the start offset, otherwise if the reference
    // node is the 'new_container', then set it to the next sibling, otherwise leave it as it is
    reference_node = dynamic_cast<nodes::text*>(start_container())
            ? detail::text_internals::split(dynamic_cast<nodes::text*>(start_container()), start_offset())
            : new_container == reference_node ? reference_node->next_sibling() : reference_node;

    // the 'new_offset' is the length of the 'parent_node' if there is no 'reference_node', otherwise it's the index of
    // the 'reference_node'. adjust the 'new_offset' by the length of the 'new_container' if it's a DocumentFragment,
    // otherwise 1 (number of children being inserted)
    auto new_offset = !reference_node ? detail::tree_internals::length(parent_node) : detail::tree_internals::index(reference_node);
    new_offset += dynamic_cast<nodes::document_fragment*>(new_container) ? detail::tree_internals::length(new_container) : 1;

    // ensure that the 'new_container' can be inserted into the 'parent_node' before the 'reference_node', remove the
    // 'new_container' from its current parent (if it has a parent), and insert it into the 'parent_node' before the
    // 'reference_node'
    detail::mutation_internals::ensure_pre_insertion_validity(new_container, parent_node, reference_node);
    detail::mutation_internals::remove(new_container->parent_node() ? new_container : nullptr);
    detail::mutation_internals::pre_insert(new_container, parent_node, reference_node);

    // if the range is currently collapsed, then set the end container and offset to the 'parent_node' and the
    // 'new_offset', so that the range maintains its collapsed state
    if (collapsed())
        std::tie(end_container, end_offset) = std::tuple(parent_node, new_offset);
}
