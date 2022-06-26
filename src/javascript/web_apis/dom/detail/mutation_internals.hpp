#ifndef SBROWSER2_MUTATION_INTERNALS_HPP
#define SBROWSER2_MUTATION_INTERNALS_HPP

#include <web_apis/dom/detail/node_internals.hpp>
#include <web_apis/dom/detail/observer_internals.hpp>
#include <web_apis/dom/detail/shadow_internals.hpp>
#include <web_apis/dom/nodes/comment.hpp>
#include <web_apis/dom/nodes/document.hpp>
#include <web_apis/dom/nodes/document_fragment.hpp>
#include <web_apis/dom/nodes/document_type.hpp>
#include <web_apis/dom/nodes/element.hpp>
#include <web_apis/dom/nodes/processing_instruction.hpp>
#include <web_apis/dom/nodes/shadow_root.hpp>
#include <web_apis/dom/ranges/range.hpp>

#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/count_if.hpp>


namespace dom::detail::mutation_internals
{
    // common checks across multiple methods / validity checks
    auto common_checks(
            nodes::node* node,
            nodes::node* parent,
            nodes::node* child)
            -> void;

    auto ensure_pre_insertion_validity(
            nodes::node* node,
            nodes::node* parent,
            nodes::node* child)
            -> void;

    // pre-insertion and -removal
    auto pre_insert(
            nodes::node* node,
            nodes::node* parent,
            nodes::node* child)
            -> nodes::node*;

    auto pre_remove(
            nodes::node* node,
            nodes::node* parent)
            -> nodes::node*;

    // general mutations
    auto insert(
            nodes::node* node,
            nodes::node* parent,
            nodes::node* child,
            ext::boolean_view suppress_observers_flag = false)
            -> nodes::node*;

    auto append(
            nodes::node* node,
            nodes::node* parent)
            -> nodes::node*;

    auto replace(
            nodes::node* node,
            nodes::node* parent,
            nodes::node* child)
            -> nodes::node*;

    auto replace_all(
            nodes::node* node,
            nodes::node* parent)
            -> void;

    auto remove(
            nodes::node* node,
            ext::boolean_view suppress_observers_flag = false)
            -> nodes::node*;
}


auto dom::detail::mutation_internals::common_checks(nodes::node* node, nodes::node* parent, nodes::node* child) -> void
{
    // if the parent is not a document, document fragment or element, then throw a hierarchy request error
    exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
            [parent] {return !ext::multi_cast<nodes::document*, nodes::document_fragment*, nodes::element*>(parent);},
            "Parent must be a Document, DocumentFragment or Element node",
            {"Objects are the incorrect type"},
            {"Check where the objects are instantiated, and verify their type is correct"},
            P("Parent", parent));

    // if the node is a shadow-including ancestor of the parent, then throw a hierarchy request error
    exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
            [node, parent] {return shadow_internals::is_host_including_ancestor(node, parent);},
            "Node cannot be a host-including ancestor of parent",
            {"A [shadow tree containing 'node']'s host tree cannot contain 'parent'"},
            {
                "Check where shadow trees are attached, and if 'parent' is in the host tree",
                "Check where shadow trees are attached, and if 'child' is in the new shadow tree"
            },
            P("Node", node), P("Parent", parent));

    // if the child has a parent that doesn't equal parent, then throw a not found error
    exception_internals::throw_v8_exception_formatted<NOT_FOUND_ERR>(
            [parent, child] {return child && child->parent_node() != parent;},
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
            P("Node", node), P("Parent", parent), P("Child", child), P("Child's parent", child->parent_node()));

    // if the node is not a document fragment, document, element, text node, processing instruction or comment node, then throw a hierarchy request error
    exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
            [node] {return !ext::multi_cast<nodes::document_fragment*, nodes::document_type*, nodes::element*, nodes::character_data*>(node);},
            "Node must be a DocumentFragment, DocumentType, Element, CharacterData");

    // if the parent is a document and the node is a text node, then throe a hierarchy request error
    exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
            [node, parent] {return dynamic_cast<nodes::document*>(parent) && dynamic_cast<nodes::text*>(node);},
            "Document parents cannot have a Text node child");

    // if the parent is not a document and the node is a document, then throe a hierarchy request error
    exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
            [node, parent] {return dynamic_cast<nodes::document_type*>(node) && !dynamic_cast<nodes::document*>(parent);},
            "DocumentType nodes must have a Document parent");
}


auto dom::detail::mutation_internals::ensure_pre_insertion_validity(
        nodes::node* node, nodes::node* parent, nodes::node* child) -> void
{
    // run the common checks
    common_checks(node, parent, child);

    // all the checks only apply if the parent is a document
    if (auto cast_parent =dynamic_cast<nodes::document*>(parent))
    {
        // if the node is a document fragment
        if (auto* cast_node = dynamic_cast<nodes::document_fragment*>(node))
        {
            exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [cast_node] {return cast_node->children->size() > 1;},
                    "A DocumentFragment with a Document parent cannot have more than 1 Element child (document element)");

            exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [cast_node] {return ranges::any_of(*cast_node->child_nodes(), &tree_internals::is_text_node);},
                    "A DocumentFragment with a Document parent cannot have any Text node children");

            // if the document type has one element children
            if (cast_node->children->size() == 1)
            {
                exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                        [cast_parent] {return !cast_parent->children->empty();},
                        "A DocumentFragment with a Document parent and Element child cannot have an Element sibling");

                exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                        [child] {return dynamic_cast<nodes::document_type*>(child);},
                        "A DocumentFragment with a Document parent and Element child cannot be inserted before a DocumentType node");

                exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                        [child] {return child && !tree_internals::all_following<nodes::document_type>(child).empty();},
                        "A DocumentFragment with a Document parent and Element child cannot be inserted before a DocumentType node");
            }
        }

        // otherwise, if the node is an element (document element)
        else if (auto* cast_node = dynamic_cast<nodes::element*>(node))
        {
            exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [cast_node] {return !cast_node->children->empty();},
                    "An Element with a Document parent cannot have any Element children");

            exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [child] {return dynamic_cast<nodes::document_type*>(child);},
                    "An Element with a Document parent cannot be inserted before a DocumentType");

            exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [child] {return child && !tree_internals::all_following<nodes::document_type>(child).empty();},
                    "An Element with a Document parent cannot be inserted before a DocumentType");
        }

        // otherwise, if the node is a document type
        else if (auto* cast_node = dynamic_cast<nodes::document_type*>(node))
        {
            exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [cast_parent] {return ranges::any_of(*cast_parent->child_nodes(), &tree_internals::is_document_type_node);},
                    "A DocumentType node with a Document parent cannot have any DocumentType siblings");

            exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [child] {return child && !tree_internals::all_preceding<nodes::element>(child).empty();},
                    "A DocumentType with a Document parent cannot be inserted after any Element nodes");

            exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [child, cast_parent] {return !child && ranges::any_of(*cast_parent->child_nodes(), &tree_internals::is_element_node);},
                    "A DocumentType with a Document parent cannot have any Element children");
        }
    }
}


auto dom::detail::mutation_internals::pre_insert(
        nodes::node* node, nodes::node* parent, nodes::node* child) -> nodes::node*
{
    // if the pre insertion is valid, set the 'reference_child' to 'child', unless 'child' is the same node as 'node',
    // in which case set it to the sibling after 'node', and insert 'node' into 'parent' before 'reference_child',
    // returning 'node'
    ensure_pre_insertion_validity(node, parent, child);
    nodes::node* reference_child = child != node ? child : node->next_sibling();
    return insert(node, parent, reference_child);
}


auto dom::detail::mutation_internals::pre_remove(
        nodes::node* node, nodes::node* parent) -> nodes::node*
{
    // if node's parent doesn't equal the parent, then throw a not found error
    exception_internals::throw_v8_exception_formatted<NOT_FOUND_ERR>(
            [node, parent] {return node->parent_node() != parent;},
            "node's current parent does not equal parent");

    // remove the node and return  it
    return remove(node);
}


auto dom::detail::mutation_internals::insert(
        nodes::node* node, nodes::node* parent, nodes::node* child, ext::boolean_view suppress_observers_flag) -> nodes::node*
{
    // special case for DocumentFragment nodes: all tof it's child nodes need to be re-inserted; otherwise, for any
    // other element extending Node, the single 'child' will be inserted. if there are no children to insert, then
    // return from the method early
    auto nodes = dynamic_cast<nodes::document_fragment*>(node) ? *node->child_nodes() : ext::vector<nodes::node*>{node};
    auto count = nodes.size();
    if (count <= 0) return nullptr;

    // special case for DocumentFragment: remove all of its children first, and then queue a mutation tree record for
    // any observers
    if (dynamic_cast<nodes::document_fragment*>(node))
    {
        ranges::for_each(nodes, [](nodes::node* node) {remove(node, true);});
        observer_internals::queue_tree_mutation_record(node, {}, nodes, nullptr, nullptr);
    }

    // live range modifications for when the child exists (ie the node is being inserted and not appended)
    if (child)
    {
        JS_REALM_GET_SURROUNDING(nullptr)
        auto live_ranges = javascript::environment::realms_2::get<ext::vector<node_ranges::range*>>(surrounding_global_object, "live_ranges");
        auto child_index = tree_internals::index(child);

        // ranges whose starting node is 'parent' and whose starting offset is greater that the index of 'child':
        // increment the start offset by the number of children being inserted
        ranges::for_each(
                live_ranges | ranges::views::filter([parent, child_index](node_ranges::range* range) {return range->start_container() == parent && range->start_offset() > child_index;}),
                [count](node_ranges::range* range) {range->start_offset += count;});

        // ranges whose ending node is 'parent' and whose ending offset is greater that the index of 'child': increment
        // the end offset by the number of children being inserted
        ranges::for_each(
                live_ranges | ranges::views::filter([parent, child_index](node_ranges::range* range) {return range->end_container() == parent && range->end_offset() > child_index;}),
                [count](node_ranges::range* range) {range->end_offset += count;});
    }

    // save the previous sibling here (used later, but mutations in the ext step would distort this value as the nodes
    // are inserted next, changing the tree structure / sibling layout)
    auto previous_sibling = child ? child->previous_sibling() : parent->last_child();
    ranges::for_each(nodes, [node, parent, child](nodes::node* node_to_add)
    {
        // adopt 'node' into 'parent''s document, and insert the node into the parent's child nodes list, before the
        // iterator representing 'child'; in the case where child == nullptr, the iterator is ::end(), so the element is
        // appended instead (expected behaviour)
        node_internals::adopt(node, parent->owner_document());
        parent->child_nodes->insert(ranges::find(*parent->child_nodes(), child), node);  // will 'push_back' if child is nullptr

        // if the parent is a shadow host (shadow_root attribute is set), the parent's shadow_root's slot assignment is
        // "named", and 'node' is a slottable, assign a slot to 'node'
        if (shadow_internals::is_shadow_host(parent)
                && dynamic_cast<nodes::element*>(parent)->shadow_root_node->slot_assignment() == "named"
                && shadow_internals::is_slottable(node))
            shadow_internals::assign_slot(node);

        // if 'parent''s root is a shadow root, 'parent' is a slot (in a shadow tree), and the (HTMLSlotElement)
        // 'parent''s assigned nodes are empty, then 'signal_a_slot_change()' for 'parent'
        if (shadow_internals::is_root_shadow_root(parent)
                && shadow_internals::is_slot(parent)
                && dynamic_cast<html::elements::html_slot_element*>(parent)->m_assigned_nodes->empty())
            shadow_internals::signal_slot_change(parent);

        // assign slottables for the tree whose root is the root of 'node'
        shadow_internals::assign_slottables_for_tree(tree_internals::root(node));

        ranges::for_each(shadow_internals::shadow_including_descendants(node), [node](nodes::node* inclusive_descendant)
        {
            inclusive_descendant->m_dom_behaviour.insertion_steps();
            if (auto* inclusive_descendant_element = dynamic_cast<nodes::element*>(inclusive_descendant);
                    inclusive_descendant_element
                    && shadow_internals::is_connected(inclusive_descendant))

                customization_internals::is_custom(dynamic_cast<nodes::element*>(node))
                        ? customization_internals::enqueue_custom_element_callback_reaction(inclusive_descendant_element, "connectedCallback")
                        : customization_internals::try_to_upgrade_element(inclusive_descendant_element);
        });
    });

    if (!suppress_observers_flag) observer_internals::queue_tree_mutation_record(parent, nodes, {}, previous_sibling, child);
    parent->m_dom_behaviour.children_changed_steps();
}


auto dom::detail::mutation_internals::append(
        nodes::node* node, nodes::node* parent) -> nodes::node*
{
    // appending to something in the same as inserting at the end, ie inserting before the iterator representing nullptr
    // which is always the end iterator; the tree won't contain Null nodes, so nullptr will never be in a list
    pre_insert(node, parent, nullptr);
}


auto dom::detail::mutation_internals::replace(
        nodes::node* node, nodes::node* parent, nodes::node* child) -> nodes::node*
{
    // run the common checks
    common_checks(node, parent, child);

    // all the checks only apply if the parent is a document
    if (auto* cast_parent = dynamic_cast<nodes::document*>(parent))
    {
        // if the node is a document fragment
        if (auto* cast_node = dynamic_cast<nodes::document_fragment*>(node))
        {
            exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [cast_node] {return cast_node->children->size() > 1;},
                    "A DocumentFragment with a Document parent cannot have more than 1 Element child (document element)");

            exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [cast_node] {return ranges::any_of(*cast_node->child_nodes(), &tree_internals::is_text_node);},
                    "A DocumentFragment with a Document parent cannot have any Text node children");

            // if the document type has one element children
            if (cast_node->children->size() == 1)
            {
                exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                        [cast_node, child] {return cast_node->children->front() != child;},
                        "A DocumentFragment with a Document parent and an Element child cannot have an Element child that is not 'child'");

                exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                        [child] {return !tree_internals::all_following<nodes::document_type>(child).empty();},
                        "A DocumentFragment with a Document parent and Element child cannot be inserted before a DocumentType node");
            }
        }

        // otherwise, if the node is an element (document element)
        else if (auto* cast_node = dynamic_cast<nodes::element*>(node))
        {
            exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [cast_node, child] {return ranges::any_of(cast_node->children(), [child](nodes::element* child_element) {return child_element != child;});},
                    "An Element with a Document parent cannot have an Element child that isn't 'child'");

            exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [child] {return !tree_internals::all_following<nodes::document_type>(child).empty();},
                    "An Element with a Document parent cannot be inserted before a DocumentType");
        }

        // otherwise, if the node is a document type
        else if (auto* cast_node = dynamic_cast<nodes::document_type*>(node))
        {
            exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [cast_parent, child] {return ranges::any_of(*cast_parent->child_nodes(), [child](nodes::node* child_node) {return tree_internals::is_document_type_node(child_node) and child_node != child;});},
                    "A DocumentType node with a Document parent cannot have a DocumentType sibling that isn't 'child'");

            exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                    [child] {return child && !tree_internals::all_preceding<nodes::element>(child).empty();},
                    "A DocumentType with a Document parent cannot be inserted after any Element nodes");
        }
    }

    // set the 'reference_child' to the 'child''s next sibling, unless the 'child''s next sibling is 'node', in which
    // case set it to the sibling after 'node' - this works because 'node' is replacing 'child', so the index point has
    // to be before the 'child''s next sibling ie where 'child' is, unless the next sibling is 'node', in which case the
    // 'node' is moving in the sibling order, so the reference child has to be the sibling after 'node'
    auto reference_child  = child->next_sibling() != node ? child->next_sibling() : node->next_sibling();
    auto previous_sibling = child->previous_sibling();
    ext::vector<nodes::node*> removed_nodes;

    // if there is a parent node, save the child to the removed nodes (it is being replaced), and remove the child node;
    // this frees the index for 'node' to be inserted into
    if (child->parent_node())
    {
        removed_nodes.push_back(child);
        remove(child, true);
    }

    // the nodes being added is a list of 'node', unless it is for a DocumentFragment parent, in which the special case
    // dictates that all the children are to be re-added - insert the 'added_nodes', and queue a mutation record for
    // this
    auto added_nodes = dynamic_cast<nodes::document_fragment*>(node) ? *node->child_nodes() : ext::vector<nodes::node*>{node};
    insert(node, parent, reference_child, true);
    observer_internals::queue_tree_mutation_record(parent, added_nodes, removed_nodes, previous_sibling, reference_child);
    return child;
}


auto dom::detail::mutation_internals::replace_all(
        nodes::node* node, nodes::node* parent) -> void
{
    // all the 'parent''s children are going to be replaces with 'node, so all the children are the 'removed_nodes'; the
    // added nodes is a list of 'node', unless it is for a DocumentFragment parent, in which the special case
    //    // dictates that all the children are to be re-added
    auto removed_nodes = *parent->child_nodes();
    auto added_nodes = dynamic_cast<nodes::document_fragment*>(node) ? *node->child_nodes() : ext::vector<nodes::node*>{node};

    // remove each node in 'remove_nodes', and then insert the node into parent (before nullptr) as that is the only
    // accessible interator in an empty list
    ranges::for_each(removed_nodes, [](nodes::node* node) {remove(node, true);});
    if (node) insert(node, parent, nullptr, true);

    // if any nodes have been added or removed, queue a mutation record
    if (!added_nodes.empty() || !removed_nodes.empty())
        observer_internals::queue_tree_mutation_record(parent, added_nodes, removed_nodes, nullptr, nullptr);
}



#endif //SBROWSER2_MUTATION_INTERNALS_HPP
