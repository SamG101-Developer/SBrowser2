#include "mutation_internals.hpp"

#include "environment/slots.ixx"




#include "ext/type_traits.ixx"

#include "css/cssom/detail/miscellaneous_query_internals.hpp"





























#include "html/elements/html_slot_element.hpp"
#include "html/elements/html_slot_element_private.hpp"

#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/find.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/any_view.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/transform.hpp>


auto dom::detail::common_checks(
        const nodes::node* node,
        const nodes::node* parent,
        const nodes::node* child)
        -> void
{
    using enum detail::dom_exception_error_t;
    auto e = js::env::env::relevant(node);

    throw_v8_exception<HIERARCHY_REQUEST_ERR>(
            [parent] {return !dom_multi_cast<nodes::document*, nodes::document_fragment*, nodes::element*>(parent);},
            u8"Parent must be a Document, DocumentFragment or Element node", e);

    throw_v8_exception<HIERARCHY_REQUEST_ERR>(
            [node, parent] {return is_host_including_ancestor(node, parent);},
            u8"Node cannot be a host-including ancestor of parent", e);

    throw_v8_exception<NOT_FOUND_ERR>(
            [parent, child] {return child && child->d_func()->parent_node.get() != parent;},
            u8"'Child''s current parent must be 'parent'", e);

    throw_v8_exception<HIERARCHY_REQUEST_ERR>(
            [node] {return !dom_multi_cast<nodes::document_fragment*, nodes::document_type*, nodes::element*, nodes::character_data*>(node);},
            u8"Node must be a DocumentFragment, DocumentType, Element, CharacterData", e);

    throw_v8_exception<HIERARCHY_REQUEST_ERR>(
            [node, parent] {return dom_multi_cast<nodes::document*>(parent) && dom_multi_cast<const nodes::text*>(node);},
            u8"Document parents cannot have a Text node child", e);

    throw_v8_exception<HIERARCHY_REQUEST_ERR>(
            [node, parent] {return dynamic_cast<const nodes::document_type*>(node) && !dynamic_cast<const nodes::document*>(parent);},
            u8"DocumentType nodes must have a Document parent", e);
}


auto dom::detail::ensure_pre_insertion_validity(
        const nodes::node* const node,
        const nodes::node* const parent,
        const nodes::node* const child)
        -> void
{
    // Run a set of common checks that are used in multiple functions.
    using enum detail::dom_exception_error_t;
    common_checks(node, parent, child);
    auto e = js::env::env::relevant(node);

    // The remaining checks only apply if the parent is a Document node.
    if (decltype(auto) cast_parent = dom_cast<const nodes::document*>(parent))
    {
        // DocumentFragment 'node'
        if (decltype(auto) cast_node = dom_cast<const nodes::document_fragment*>(node))
        {
            throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                    [&cast_node] {return cast_node->d_func()->children.size() > 1;},
                    u8"A DocumentFragment with a Document parent cannot have more than 1 Element child (document element)", e);

            throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                    [&cast_node] {return ranges::any_of(cast_node->d_func()->child_nodes, &is_text_node, ext::underlying);},
                    u8"A DocumentFragment with a Document parent cannot have any Text node children", e);

            // Special cases if the DocFragment has one element child
            if (cast_node->d_func()->children().size() == 1)
            {
                throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                        [&cast_parent] {return !cast_parent->d_func()->children.empty();},
                        u8"A DocumentFragment with a Document parent and Element child cannot have an Element sibling", e);

                throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                        [&child] {return dynamic_cast<const nodes::document_type*>(child);},
                        u8"A DocumentFragment with a Document parent and Element child cannot be inserted before a DocumentType node", e);

                throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                        [&child] {return child && !all_following<nodes::document_type>(child).empty();},
                        u8"A DocumentFragment with a Document parent and Element child cannot be inserted before a DocumentType node", e);
            }
        }

        // Element 'node'
        else if (decltype(auto) cast_node = dynamic_cast<const nodes::element*>(node))
        {
            throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                    [&cast_node] {return !cast_node->d_func()->children.empty();},
                    u8"An Element with a Document parent cannot have any Element children", e);

            throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                    [&child] {return dynamic_cast<const nodes::document_type*>(child);},
                    u8"An Element with a Document parent cannot be inserted before a DocumentType", e);

            throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                    [&child] {return child && !all_following<nodes::document_type>(child).empty();},
                    u8"An Element with a Document parent cannot be inserted before a DocumentType", e);
        }

        // DocumentType 'node'
        else if (decltype(auto) cast_node = dynamic_cast<const nodes::document_type*>(node))
        {
            throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                    [&cast_parent] {return ranges::any_of(cast_parent->d_func()->child_nodes, &is_document_type_node, ext::underlying);},
                    u8"A DocumentType node with a Document parent cannot have any DocumentType siblings", e);

            throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                    [&child] {return child && !all_preceding<nodes::element>(child).empty();},
                    u8"A DocumentType with a Document parent cannot be inserted after any Element nodes", e);

            throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                    [&child, &cast_parent] {return !child && ranges::any_of(cast_parent->d_func()->child_nodes, &is_element_node, ext::underlying);},
                    u8"A DocumentType with a Document parent cannot have any Element children", e);
        }
    }
}


auto dom::detail::pre_insert(
        std::unique_ptr<nodes::node> node,
        nodes::node* const parent,
        const nodes::node* const child)
        -> nodes::node*
{
    // If the pre insertion is valid, set the 'reference_child' to 'child', unless 'child' is the same node as 'node',
    // in which case set it to the sibling after 'node'. Insert 'node' into 'parent' before 'reference_child', returning
    // 'node'. This ensures that the node is inserted before the child, or in the same place as the node if it's already
    // in the parent.
    ensure_pre_insertion_validity(node.get(), parent, child);
    decltype(auto) reference_child = child != node.get() ? child : next_sibling(node.get());
    return insert(std::move(node), parent, reference_child);
}


auto dom::detail::pre_remove(
        const nodes::node* const node,
        const nodes::node* const parent)
        -> nodes::node*
{
    using enum detail::dom_exception_error_t;
    auto e = js::env::env::relevant(node);

    throw_v8_exception<NOT_FOUND_ERR>(
            [node, parent] {return node->d_func()->parent_node.get() != parent;},
            u8"Node's current parent does not equal parent", e);

    // Remove the node and return it
    return remove(node);
}


auto dom::detail::insert(
        std::unique_ptr<nodes::node>&& node,
        nodes::node* const parent,
        const nodes::node* const child,
        ext::boolean suppress_observers_flag)
        -> nodes::node*
{
    // Special case for DocumentFragment nodes: all of it's child nodes need to be re-inserted; otherwise, for any other
    // element extending Node, the single 'child' will be inserted. If there are no children to insert, then return from
    // the method early (ie inserting nullptr). Move the node into a list and determine the 'nodes' to insert.
    decltype(auto) is_node_document_fragment = dom_cast<nodes::document_fragment*>(node.get());
    decltype(auto) nodes = ranges::any_helpful_view<nodes::node*>(is_node_document_fragment ? node->d_func()->child_nodes | ranges::views::transform(ext::underlying) : node.get());

    auto count = nodes.size();
    return_if (count <= 0) nullptr;

    // Special case for DocumentFragment: remove all of its children first, and then queue a mutation tree record for
    // any observers.
    if (is_node_document_fragment)
    {
        nodes | ranges::views::for_each(BIND_BACK(remove, true));
        queue_tree_mutation_record(node.get(), {}, nodes, nullptr, nullptr);
    }

    // Live range modifications for when the child exists (ie the node is being inserted and not appended).
    if (child)
    {
        auto e = js::env::env::surrounding(nullptr);
        decltype(auto) live_ranges = js::env::get_slot<ext::vector<dom::node_ranges::range*>>(e, js::global_slots::live_ranges);
        decltype(auto) child_index = index(child);

        // Increment the start and end offset of ranges whose starting node is the parent, and starting offset is
        // greater than the index of the 'child'; this is because everything in the Range will be shifted forwards as
        // the new 'node' is inserted into the parent, at an index before the start offset.
        live_ranges
                | ranges::views::filter([parent](auto* range) {return range->d_func()->start->node.get() == parent;})
                | ranges::views::filter([child_index](auto* range) {return range->d_func()->start->offset > child_index;})
                | ranges::views::for_each([count](auto* range) {range->d_func()->start->offset += count;});

        live_ranges
                | ranges::views::filter([parent](auto* range) {return range->d_func()->end->node.get() == parent;})
                | ranges::views::filter([child_index](auto* range) {return range->d_func()->end->offset > child_index;})
                | ranges::views::for_each([count](auto* range) {range->d_func()->end->offset += count;});
    }

    // Save the previous sibling here (used later, but mutations in the ext step would distort this value as the nodes
    // are inserted next, changing the tree structure / sibling layout).
    decltype(auto) child_previous_sibling = child ? previous_sibling(child) : parent->d_func()->child_nodes.back().get();
    for (nodes::node* node_to_add: nodes)
    {
        // Adopt 'node' into 'parent''s document, and insert the node into the parent's child nodes list, before the
        // iterator representing 'child'; in the case where child == nullptr, the iterator is ::end(), so the element is
        // appended instead (expected behaviour).
        adopt(node_to_add, parent->d_func()->node_document);
        parent->d_func()->child_nodes.insert(ranges::find(parent->d_func()->child_nodes, child, ext::underlying), node_to_add);

        // If the 'parent' is a shadow host (shadow_root attribute is set), the 'parent's shadow_root's slot assignment
        // is "named", and 'node' is a slottable, assign a slot to 'node'.
        if (is_shadow_host(parent)
            && dynamic_cast<const nodes::element*>(parent)->d_func()->shadow_root->d_func()->slot_assignment == slot_assignment_mode_t::NAMED
            && is_slottable(node_to_add))
            assign_slot(node_to_add);

        // If 'parent''s root is a shadow root, 'parent' is a slot (in a shadow tree), and the (HTMLSlotElement)
        // 'parent''s assigned nodes are empty, then 'signal_a_slot_change()' for 'parent'.
        if (is_root_shadow_root(parent)
            && is_slot(parent)
            && dynamic_cast<const html::elements::html_slot_element*>(parent)->assigned_nodes().empty())
            signal_slot_change(parent);

        // Assign slottables for the tree whose root is the root of 'node'
        assign_slottables_for_tree(root(node_to_add));

        for (nodes::node* inclusive_descendant: shadow_including_descendants(node_to_add))
        {
            inclusive_descendant->d_func()->insertion_steps();
            if (decltype(auto) inclusive_descendant_element = dynamic_cast<nodes::element*>(inclusive_descendant);
                    inclusive_descendant_element && is_connected(inclusive_descendant))

                is_custom(dynamic_cast<nodes::element*>(inclusive_descendant))
                        ? enqueue_custom_element_callback_reaction(inclusive_descendant_element, u"connectedCallback")
                        : try_to_upgrade_element(inclusive_descendant_element);
        }
    }

    if (!suppress_observers_flag) queue_tree_mutation_record(parent, nodes, {}, child_previous_sibling, child);
    parent->d_func()->children_changed_steps();

    /* [CSSOM] */
    if (decltype(auto) processing_instruction = dom_cast<const nodes::processing_instruction*>(node.get());
            processing_instruction && index(node.get()) < index(node->d_func()->node_document->d_func()->document_element))
        css::detail::processing_instruction_prolog_steps(processing_instruction);
}


auto dom::detail::append(
        std::unique_ptr<nodes::node>&& node,
        nodes::node* const parent)
        -> nodes::node*
{
    // Appending to something in the same as inserting at the end, ie inserting before the iterator representing
    // nullptr, which is always the end iterator; the tree won't contain Null nodes, so nullptr will never be in a list.
    pre_insert(std::move(node), parent, nullptr);
}


auto dom::detail::replace(
        std::unique_ptr<nodes::node>&& node,
        const nodes::node* const parent,
        nodes::node* child)
        -> nodes::node*
{
    // Run a set of common checks that are used in multiple functions.
    using enum dom::detail::dom_exception_error_t;
    common_checks(node.get(), parent, child);
    auto e = js::env::env::relevant(node);

    // The remaining checks only apply if the parent is a Document node.
    if (decltype(auto) cast_parent = dynamic_cast<const nodes::document*>(parent))
    {
        // DocumentFragment 'node'
        if (decltype(auto) cast_node = dynamic_cast<const nodes::document_fragment*>(node.get()))
        {
            throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                    [&cast_node] {return cast_node->d_func()->children.size() > 1;},
                    u8"A DocumentFragment with a Document parent cannot have more than 1 Element child (document element)", e);

            throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                    [&cast_node] {return ranges::any_of(cast_node->d_func()->child_nodes, &is_text_node, ext::underlying);},
                    u8"A DocumentFragment with a Document parent cannot have any Text node children", e);

            // if the document type has one element children
            if (cast_node->d_func()->children.size() == 1)
            {
                throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                        [&cast_node, &child] {return cast_node->d_func()->children.front() != child;},
                        u8"A DocumentFragment with a Document parent and an Element child cannot have an Element child that is not 'child'", e);

                throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                        [&child] {return !all_following<nodes::document_type>(child).empty();},
                        u8"A DocumentFragment with a Document parent and Element child cannot be inserted before a DocumentType node", e);
            }
        }

        // Element 'node'
        else if (decltype(auto) cast_node = dynamic_cast<const nodes::element*>(node.get()))
        {
            throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                    [&cast_node, &child] {return ranges::any_of(cast_node->d_func()->children, BIND_FRONT(ext::cmp::eq, child), ext::underlying);},
                    u8"An Element with a Document parent cannot have an Element child that isn't 'child'", e);

            throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                    [&child] {return !all_following<nodes::document_type>(child).empty();},
                    u8"An Element with a Document parent cannot be inserted before a DocumentType", e);
        }

        // DocumentType 'node'
        else if (decltype(auto) cast_node = dynamic_cast<const nodes::document_type*>(node.get()))
        {
            throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                    [&cast_parent, &child] {return ranges::any_of(cast_parent->d_func()->child_nodes, [child](nodes::node* child_node) {return is_document_type_node(child_node) && child_node != child;});},
                    u8"A DocumentType node with a Document parent cannot have a DocumentType sibling that isn't 'child'", e);

            throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                    [&child] {return child && !all_preceding<nodes::element>(child).empty();},
                    u8"A DocumentType with a Document parent cannot be inserted after any Element nodes", e);
        }
    }

    // Set the 'reference_child' to the 'child''s next sibling, unless the 'child''s next sibling is 'node', in which
    // case set it to the sibling after 'node' -- this works because 'node' is replacing 'child', so the index point has
    // to be before the 'child''s next sibling ie where 'child' is, unless the next sibling is 'node', in which case the
    // 'node' is moving in the sibling order, so the reference child has to be the sibling after 'node'.
    decltype(auto) reference_child  = next_sibling(child) != node.get() ? next_sibling(child) : next_sibling(node.get());
    decltype(auto) child_previous_sibling = previous_sibling(child);
    auto removed_nodes = ext::vector<const nodes::node*>{};

    // If there is a parent node, save the child to the removed nodes (it is being replaced), and remove the child node;
    // this frees the index for 'node' to be inserted into.
    if (child->d_func()->parent_node)
    {
        removed_nodes.push_back(child);
        remove(child, true);
    }

    // The nodes being added is a list of 'node', unless it is for a DocumentFragment parent, in which the special case
    // dictates that all the children are to be re-added -- insert the 'added_nodes', and queue a mutation record for
    // this.
    decltype(auto) is_node_document_fragment = dom_cast<nodes::document_fragment*>(node.get());
    decltype(auto) added_nodes = ranges::any_helpful_view<nodes::node*>(is_node_document_fragment ? node->d_func()->child_nodes | ranges::views::transform(ext::underlying) : node.get());
    insert(std::move(node), parent, reference_child, true);
    queue_tree_mutation_record(parent, added_nodes, removed_nodes, child_previous_sibling, reference_child);
    return child;
}


auto dom::detail::replace_all(
        std::unique_ptr<nodes::node>&& node,
        const nodes::node* const parent)
        -> void
{
    // All the 'parent''s children are going to be replaced with 'node', so all the children are the 'removed_nodes';
    // the added nodes is a list of 'node', unless it is for a DocumentFragment parent, in which the special case
    // dictates that all the children are to be re-added.
    decltype(auto) is_node_document_fragment = dom_cast<nodes::document_fragment*>(node.get());
    decltype(auto) removed_nodes = parent->d_func()->child_nodes | ranges::views::transform(ext::underlying);
    decltype(auto) added_nodes = ranges::any_helpful_view<nodes::node*>(is_node_document_fragment ? node->d_func()->child_nodes | ranges::views::transform(ext::underlying) : node.get());

    // remove each node in 'remove_nodes', and then insert the node into parent (before nullptr) as that is the only
    // accessible interator in an empty list
    removed_nodes | ranges::views::for_each([](nodes::node* node_to_remove) {remove(node_to_remove, true);});
    if (node)
        insert(std::move(node), parent, nullptr, true);

    // if any nodes have been added or removed, queue a mutation record
    if (!added_nodes.empty() || !removed_nodes.empty())
        queue_tree_mutation_record(parent, added_nodes, removed_nodes, nullptr, nullptr);
}


// TODO : remove(...) -> place below code at start of method
// /* CSSOM */
//    if (decltype(auto) processing_instruction = dom_cast<const nodes::processing_instruction*>(node);
//            processing_instruction && index(node) < index(node->owner_document()->document_element()))
//        css::detail::processing_instruction_prolog_steps(processing_instruction);
