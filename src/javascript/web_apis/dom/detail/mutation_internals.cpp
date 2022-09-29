#include "mutation_internals.hpp"

#include "ext/casting.hpp"
#include "ext/ranges.hpp"

#include "css/cssom/detail/miscellaneous_query_internals.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/shadow_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/detail/range_internals.hpp"
#include "dom/detail/shadow_internals.hpp"
#include "dom/detail/tree_internals.hpp"
#include "dom/nodes/text.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_fragment.hpp"
#include "dom/nodes/document_type.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/processing_instruction.hpp"
#include "dom/nodes/shadow_root.hpp"
#include "dom/ranges/range.hpp"

#include "html/elements/html_slot_element.hpp"

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

    // if the parent is not a document, document fragment or element, then throw a hierarchy request error
    throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
            [parent] {return !ext::multi_cast<const nodes::document*, const nodes::document_fragment*, const nodes::element*>(parent);},
            "Parent must be a Document, DocumentFragment or Element node",
            {"Objects are the incorrect type"},
            {"Check where the objects are instantiated, and verify their type is correct"},
            P("Parent", parent));

    // if the node is a shadow-including ancestor of the parent, then throw a hierarchy request error
    throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
            [node, parent] {return is_host_including_ancestor(node, parent);},
            "Node cannot be a host-including ancestor of parent",
            {"A [shadow tree containing 'node']'s host tree cannot contain 'parent'"},
            {
                    "Check where shadow trees are attached, and if 'parent' is in the host tree",
                    "Check where shadow trees are attached, and if 'child' is in the new shadow tree"
            },
            P("Node", node),
            P("Parent", parent));

    // if the child has a parent that doesn't equal parent, then throw a not found error
    throw_v8_exception_formatted<NOT_FOUND_ERR>(
            [parent, child] {return child && child->d_func()->parent_node != parent;},
            "'Child''s current parent must be 'parent'",
            {
                    "The incorrect node has been passed in as the 'child' parameter",
                    "The incorrect node has been passed in as the 'parent' parameter",
                    "The 'child', 'node', and 'parent' arguments are in each others positions",
                    "The 'parent' has been updated asynchronously"
            },
            {
                    "Check that the correct objects are passed into the method",
                    "Check that the arguments are in the correct order",
                    "Check that no other threads are updating objects' parent"
            },
            P("Node", node),
            P("Parent", parent),
            P("Child", child),
            P("Child's parent", child->d_func()->parent_node));

    // if the node is not a document fragment, document, element, text node, processing instruction or comment node, then throw a hierarchy request error
    throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
            [node] {return !ext::multi_cast<const nodes::document_fragment*, const nodes::document_type*, const nodes::element*, const nodes::character_data*>(node);},
            "Node must be a DocumentFragment, DocumentType, Element, CharacterData");

    // if the parent is a document and the node is a text node, then throe a hierarchy request error
    throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
            [node, parent] {return dynamic_cast<const nodes::document*>(parent) && dynamic_cast<const nodes::text*>(node);},
            "Document parents cannot have a Text node child");

    // if the parent is not a document and the node is a document, then throe a hierarchy request error
    throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
            [node, parent] {return dynamic_cast<const nodes::document_type*>(node) && !dynamic_cast<const nodes::document*>(parent);},
            "DocumentType nodes must have a Document parent");
}


auto dom::detail::ensure_pre_insertion_validity(
        const nodes::node* const node,
        const nodes::node* const parent,
        const nodes::node* const child)
        -> void
{
    // run the common checks
    using enum detail::dom_exception_error_t;
    common_checks(node, parent, child);

    // all the checks only apply if the parent is a document
    if (decltype(auto) cast_parent = dynamic_cast<const nodes::document*>(parent))
    {
        // if the node is a document fragment
        if (decltype(auto) cast_node = dynamic_cast<const nodes::document_fragment*>(node))
        {
            throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [&cast_node] {return cast_node->d_func()->children.size() > 1;},
                    "A DocumentFragment with a Document parent cannot have more than 1 Element child (document element)");

            throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [&cast_node] {return ranges::any_of(*cast_node->d_func()->child_nodes, &is_text_node);},
                    "A DocumentFragment with a Document parent cannot have any Text node children");

            // if the document type has one element children
            if (cast_node->children().size() == 1)
            {
                throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                        [&cast_parent] {return !cast_parent->d_func()->children.empty();},
                        "A DocumentFragment with a Document parent and Element child cannot have an Element sibling");

                throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                        [&child] {return dynamic_cast<const nodes::document_type*>(child);},
                        "A DocumentFragment with a Document parent and Element child cannot be inserted before a DocumentType node");

                throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                        [&child] {return child && !all_following<nodes::document_type>(child).empty();},
                        "A DocumentFragment with a Document parent and Element child cannot be inserted before a DocumentType node");
            }
        }

        // otherwise, if the node is an element (document element)
        else if (decltype(auto) cast_node = dynamic_cast<const nodes::element*>(node))
        {
            throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [&cast_node] {return !cast_node->d_func()->children.empty();},
                    "An Element with a Document parent cannot have any Element children");

            throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [&child] {return dynamic_cast<const nodes::document_type*>(child);},
                    "An Element with a Document parent cannot be inserted before a DocumentType");

            throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [&child] {return child && !all_following<nodes::document_type>(child).empty();},
                    "An Element with a Document parent cannot be inserted before a DocumentType");
        }

        // otherwise, if the node is a document type
        else if (decltype(auto) cast_node = dynamic_cast<const nodes::document_type*>(node))
        {
            throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [&cast_parent] {return ranges::any_of(*cast_parent->d_func()->child_nodes, &is_document_type_node);},
                    "A DocumentType node with a Document parent cannot have any DocumentType siblings");

            throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [&child] {return child && !all_preceding<nodes::element>(child).empty();},
                    "A DocumentType with a Document parent cannot be inserted after any Element nodes");

            throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [&child, &cast_parent] {return !child && ranges::any_of(*cast_parent->d_func()->child_nodes, &is_element_node);},
                    "A DocumentType with a Document parent cannot have any Element children");
        }
    }
}


auto dom::detail::pre_insert(
        std::unique_ptr<nodes::node> node,
        const nodes::node* const parent,
        const nodes::node* const child)
        -> nodes::node*
{
    // if the pre insertion is valid, set the 'reference_child' to 'child', unless 'child' is the same node as 'node',
    // in which case set it to the sibling after 'node', and insert 'node' into 'parent' before 'reference_child',
    // returning 'node'
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

    // if node's parent doesn't equal the parent, then throw a not found error
    throw_v8_exception_formatted<NOT_FOUND_ERR>(
            [node, parent] {return node->d_func()->parent_node != parent;},
            "node's current parent does not equal parent");

    // remove the node and return  it
    return remove(node);
}


auto dom::detail::insert(
        std::unique_ptr<nodes::node> node,
        const nodes::node* const parent,
        const nodes::node* const child,
        ext::boolean  suppress_observers_flag)
        -> nodes::node*
{
    // special case for DocumentFragment nodes: all of it's child nodes need to be re-inserted; otherwise, for any other
    // element extending Node, the single 'child' will be inserted. if there are no children to insert, then return from
    // the method early
    auto is_node_document_fragment = dynamic_cast<nodes::document_fragment*>(node.get());
    decltype(auto) nodes = is_node_document_fragment
            ? node->d_func()->child_nodes | ranges::views::transform(&std::unique_ptr<nodes::node>::get)
            : ranges::make_any_view<ranges::category::forward | ranges::category::sized>(node.get());

    decltype(auto) count = nodes.size();
    if (count <= 0) return nullptr;

    // special case for DocumentFragment: remove all of its children first, and then queue a mutation tree record for
    // any observers
    if (is_node_document_fragment)
    {
        nodes | ranges::views::for_each([](nodes::node* const node_to_remove) {remove(node_to_remove, true);});
        queue_tree_mutation_record(node.get(), {}, nodes, nullptr, nullptr);
    }

    // live range modifications for when the child exists (ie the node is being inserted and not appended)
    if (child)
    {
        JS_REALM_GET_SURROUNDING(nullptr);
        decltype(auto) live_ranges = javascript::environment::realms::get<ext::vector<node_ranges::range*>>(nullptr_surrounding_global_object, "live_ranges");
        decltype(auto) child_index = index(child);

        // ranges whose starting node is 'parent' and whose starting offset is greater that the index of 'child':
        // increment the start offset by the number of children being inserted
        ranges::for_each(
                live_ranges | ranges::views::filter([parent, child_index](const node_ranges::range* const range) {return range->d_func()->start->node == parent && range->d_func()->start->offset > child_index;}),
                [count](node_ranges::range* const range) {range->d_func()->start->offset += count;});

        // ranges whose ending node is 'parent' and whose ending offset is greater that the index of 'child': increment
        // the end offset by the number of children being inserted
        ranges::for_each(
                live_ranges | ranges::views::filter([parent, child_index](const node_ranges::range* const range) {return range->d_func()->end->node == parent && range->d_func()->end->offset > child_index;}),
                [count](node_ranges::range* const range) {range->d_func()->end->offset += count;});
    }

    // save the previous sibling here (used later, but mutations in the ext step would distort this value as the nodes
    // are inserted next, changing the tree structure / sibling layout)
    decltype(auto) previous_sibling = child ? child->previous_sibling() : parent->d_func()->child_nodes.back();
    for (nodes::node* const node_to_add: nodes)
    {
        // adopt 'node' into 'parent''s document, and insert the node into the parent's child nodes list, before the
        // iterator representing 'child'; in the case where child == nullptr, the iterator is ::end(), so the element is
        // appended instead (expected behaviour)
        adopt(node_to_add, parent->d_func()->node_document);
        parent->d_func()->child_nodes.insert(ranges::find(*parent->child_nodes(), child), node_to_add);  // will 'push_back' if child is nullptr

        // if the parent is a shadow host (shadow_root attribute is set), the parent's shadow_root's slot assignment is
        // "named", and 'node' is a slottable, assign a slot to 'node'
        if (is_shadow_host(parent)
            && dynamic_cast<const nodes::element*>(parent)->shadow_root_node()->slot_assignment() == "named"
            && is_slottable(node_to_add))
            assign_slot(node_to_add);

        // if 'parent''s root is a shadow root, 'parent' is a slot (in a shadow tree), and the (HTMLSlotElement)
        // 'parent''s assigned nodes are empty, then 'signal_a_slot_change()' for 'parent'
        if (is_root_shadow_root(parent)
            && is_slot(parent)
            && dynamic_cast<const html::elements::html_slot_element*>(parent)->assigned_nodes().empty())
            signal_slot_change(parent);

        // assign slottables for the tree whose root is the root of 'node'
        assign_slottables_for_tree(root(node_to_add));

        for (nodes::node* inclusive_descendant: shadow_including_descendants(node_to_add))
        {
            inclusive_descendant->d_func()->insertion_steps();
            if (decltype(auto) inclusive_descendant_element = dynamic_cast<nodes::element*>(inclusive_descendant);
                    inclusive_descendant_element && is_connected(inclusive_descendant))

                is_custom(dynamic_cast<nodes::element*>(inclusive_descendant))
                        ? enqueue_custom_element_callback_reaction(inclusive_descendant_element, "connectedCallback")
                        : try_to_upgrade_element(inclusive_descendant_element);
        }
    }

    if (!suppress_observers_flag) queue_tree_mutation_record(parent, nodes, {}, previous_sibling, child);
    parent->children_changed_steps();

    /* CSSOM */
    if (decltype(auto) processing_instruction = dom_cast<const nodes::processing_instruction*>(node);
            processing_instruction && index(node) < index(node->d_func()->node_document->d_func()->document_element))
        css::detail::processing_instruction_prolog_steps(processing_instruction);
}


auto dom::detail::append(
        const nodes::node* const node,
        const nodes::node* const parent)
        -> nodes::node*
{
    // appending to something in the same as inserting at the end, ie inserting before the iterator representing nullptr
    // which is always the end iterator; the tree won't contain Null nodes, so nullptr will never be in a list
    pre_insert(node, parent, nullptr);
}


auto dom::detail::replace(
        const nodes::node* const node,
        const nodes::node* const parent,
        nodes::node* const child)
        -> nodes::node*
{
    // run the common checks
    using enum dom::detail::dom_exception_error_t;
    common_checks(node, parent, child);

    // all the checks only apply if the parent is a document
    if (decltype(auto) cast_parent = dynamic_cast<const nodes::document*>(parent))
    {
        // if the node is a document fragment
        if (decltype(auto) cast_node = dynamic_cast<const nodes::document_fragment*>(node))
        {
            throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [&cast_node] {return cast_node->d_func()->children.size() > 1;},
                    "A DocumentFragment with a Document parent cannot have more than 1 Element child (document element)");

            throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [&cast_node] {return ranges::any_of(cast_node->d_func()->child_nodes, &is_text_node);},
                    "A DocumentFragment with a Document parent cannot have any Text node children");

            // if the document type has one element children
            if (cast_node->children().size() == 1)
            {
                throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                        [&cast_node, &child] {return cast_node->d_func()->children.front() != child;},
                        "A DocumentFragment with a Document parent and an Element child cannot have an Element child that is not 'child'");

                throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                        [&child] {return !all_following<nodes::document_type>(child).empty();},
                        "A DocumentFragment with a Document parent and Element child cannot be inserted before a DocumentType node");
            }
        }

        // otherwise, if the node is an element (document element)
        else if (decltype(auto) cast_node = dynamic_cast<const nodes::element*>(node))
        {
            throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [&cast_node, &child] {return ranges::any_of(cast_node->d_func()->children, BIND_FRONT(std::not_equal_to{}, child));},
                    "An Element with a Document parent cannot have an Element child that isn't 'child'");

            throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [&child] {return !all_following<nodes::document_type>(child).empty();},
                    "An Element with a Document parent cannot be inserted before a DocumentType");
        }

        // otherwise, if the node is a document type
        else if (decltype(auto) cast_node = dynamic_cast<const nodes::document_type*>(node))
        {
            throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [&cast_parent, &child] {return ranges::any_of(cast_parent->d_func()->child_nodes, [child](nodes::node* child_node) {return is_document_type_node(child_node) and child_node != child;});},
                    "A DocumentType node with a Document parent cannot have a DocumentType sibling that isn't 'child'");

            throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [&child] {return child && !all_preceding<nodes::element>(child).empty();},
                    "A DocumentType with a Document parent cannot be inserted after any Element nodes");
        }
    }

    // set the 'reference_child' to the 'child''s next sibling, unless the 'child''s next sibling is 'node', in which
    // case set it to the sibling after 'node' - this works because 'node' is replacing 'child', so the index point has
    // to be before the 'child''s next sibling ie where 'child' is, unless the next sibling is 'node', in which case the
    // 'node' is moving in the sibling order, so the reference child has to be the sibling after 'node'
    decltype(auto) reference_child  = child->next_sibling() != node ? child->next_sibling() : node->next_sibling();
    decltype(auto) previous_sibling = child->previous_sibling();
    ext::vector<const nodes::node*> removed_nodes;

    // if there is a parent node, save the child to the removed nodes (it is being replaced), and remove the child node;
    // this frees the index for 'node' to be inserted into
    if (child->d_func()->parent_node)
    {
        removed_nodes.push_back(child);
        remove(child, true);
    }

    // the nodes being added is a list of 'node', unless it is for a DocumentFragment parent, in which the special case
    // dictates that all the children are to be re-added - insert the 'added_nodes', and queue a mutation record for
    // this
    decltype(auto) added_nodes = dynamic_cast<const nodes::document_fragment*>(node) ? node->d_func()->child_nodes() : ext::vector<const nodes::node*>{node};
    insert(node, parent, reference_child, true);
    queue_tree_mutation_record(parent, added_nodes, removed_nodes, previous_sibling, reference_child);
    return child;
}


auto dom::detail::replace_all(
        const nodes::node* const node,
        const nodes::node* const parent)
        -> void
{
    // all the 'parent''s children are going to be replaces with 'node, so all the children are the 'removed_nodes'; the
    // added nodes is a list of 'node', unless it is for a DocumentFragment parent, in which the special case
    //    // dictates that all the children are to be re-added
    decltype(auto) removed_nodes = parent->d_func()->child_nodes;
    decltype(auto) added_nodes = dynamic_cast<const nodes::document_fragment*>(node) ? node->d_func()->child_nodes : ext::vector<nodes::node*>{node};

    // remove each node in 'remove_nodes', and then insert the node into parent (before nullptr) as that is the only
    // accessible interator in an empty list
    ranges::for_each(removed_nodes, [](nodes::node* const node_to_remove) {remove(node_to_remove, true);});
    if (node) insert(node, parent, nullptr, true);

    // if any nodes have been added or removed, queue a mutation record
    if (!added_nodes.empty() || !removed_nodes.empty())
        queue_tree_mutation_record(parent, added_nodes, removed_nodes, nullptr, nullptr);
}


// TODO : remove(...) -> place below code at start of method
// /* CSSOM */
//    if (decltype(auto) processing_instruction = dom_cast<const nodes::processing_instruction*>(node);
//            processing_instruction && index(node) < index(node->owner_document()->document_element()))
//        css::detail::processing_instruction_prolog_steps(processing_instruction);
