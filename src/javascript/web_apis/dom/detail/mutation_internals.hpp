#ifndef SBROWSER2_MUTATION_INTERNALS_HPP
#define SBROWSER2_MUTATION_INTERNALS_HPP

#include <web_apis/dom/nodes/document.hpp>
#include <web_apis/dom/nodes/document_fragment.hpp>
#include <web_apis/dom/nodes/element.hpp>


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
            bool suppress_observers_flag = false)
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

    auto remove(
            nodes::node* node,
            bool suppress_observers_flag = false)
            -> nodes::node*;

    auto replace_all(
            nodes::node* node,
            nodes::node* parent)
            -> void;
}


auto dom::detail::mutation_internals::common_checks(
        nodes::node* node,
        nodes::node* parent,
        nodes::node* child)
        -> void
{
    // if the parent is not a document, document fragment or element, then throw a hierarchy request error
    exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
            "Parent must be a Document, DocumentFragment or Element node",
            {"Objects are the incorrect type"},
            {"Check where the objects are instantiated, and verify their type is correct"},
            {{"Parent", parent}},
            [parent] {return not ext::multi_cast<nodes::document*, nodes::document_fragment*, nodes::element*>(parent);});

    // if the node is a shadow-including ancestor of the parent, then throw a hierarchy request error
    exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
            "Node can not be a host-including ancestor of parent",
            {"A [shadow tree containing 'node']'s host tree cannot contain 'parent'"},
            {
                "Check where shadow trees are attached, and if 'parent' is in the host tree",
                "Check where shadow trees are attached, and if 'child' is in the new shadow tree"
            },
            {{"Parent", parent}, {"Node", node}},
            [node, parent] {return shadow_internals::is_host_including_ancestor(node, parent);});

    // if the child has a parent that doesn't equal parent, then throw a not found error
    exception_internals::throw_v8_exception_formatted<NOT_FOUND_ERR>(
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
            {{"Node", node}, {"Parent", parent}, {"Child", child}, {"Child's parent", child->parent_node()}},
            [parent, child] {return child and child->parent_node() != parent;});

    // if the node is not a document fragment, document, element, text node, processing instruction or comment node, then throw a hierarchy request error
    exception_internals::throw_v8_exception<HIERARCHY_REQUEST_ERR>(
            "node must be a document_fragment, document_type, element, text, processing_instruction or comment node",
            [node] {return not ext::multi_cast<nodes::document_fragment*, nodes::document_type*, nodes::element*, nodes::text*, nodes::processing_instruction*, nodes::comment*>(
                    node);});

    // if the parent is a document and the node is a text node, then throe a hierarchy request error
    exception_internals::throw_v8_exception<HIERARCHY_REQUEST_ERR>(
            "document parents can not have a text node child",
            [node, parent] {return dynamic_cast<nodes::document*>(parent) and dynamic_cast<nodes::text*>(node);});

    // if the parent is not a document and the node is a document, then throe a hierarchy request error
    exception_internals::throw_v8_exception<HIERARCHY_REQUEST_ERR>(
            "document_type nodes can not have a non-document parent",
            [node, parent] {return dynamic_cast<nodes::document_type*>(node) and not dynamic_cast<nodes::document*>(parent);});
}



#endif //SBROWSER2_MUTATION_INTERNALS_HPP
