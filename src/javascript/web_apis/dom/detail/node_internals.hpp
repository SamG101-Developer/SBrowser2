#ifndef SBROWSER2_NODE_INTERNALS_HPP
#define SBROWSER2_NODE_INTERNALS_HPP


#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(dom)
namespace dom::nodes {class document;}
namespace dom::nodes {class element;}
namespace dom::nodes {class node;}
namespace dom::nodes {class event_target;}


namespace dom::detail
{
    // node manipulation
    template <ext::inherit<nodes::node> T>
    auto clone(
            T* node,
            nodes::document* document = nullptr,
            ext::boolean deep = false)
            -> std::unique_ptr<T>;

    auto adopt(
            const nodes::node* node,
            const nodes::document* document)
            -> nodes::node*;

    // locating information on a node
    auto locate_a_namespace_prefix(
            const nodes::element* element,
            ext::string_view namespace_)
            -> ext::string;

    auto locate_a_namespace(
            const nodes::node* node,
            ext::string_view prefix)
            -> ext::string;

    // list elements with certain features
    auto list_of_elements_with_qualified_name(
            const nodes::node* descendant_element,
            ext::string_view qualified_name)
            -> ext::vector<nodes::element*>;

    auto list_of_elements_with_namespace_and_local_name(
            const nodes::node* node,
            ext::string_view namespace_,
            ext::string_view local_name)
            -> ext::vector<nodes::element*>;

    auto list_of_elements_with_class_names(
            const nodes::node* node,
            ext::string_view class_names)
            -> ext::vector<nodes::element*>;

    // other
    auto string_replace_all(
            ext::string_view string,
            nodes::node* parent)
            -> ext::string; // TODO : return string (modified)

    auto is_document_available_to_user(
            nodes::document* document,
            ext::string_view)
            -> ext::boolean; // TODO name [-1]

    auto is_document_fully_active(
            nodes::document* document)
            -> ext::boolean;

    auto is_html(
            const nodes::element* element)
            -> ext::boolean;

    auto has_active_parser(
            nodes::document* document)
            -> ext::boolean;

    auto document_has_style_sheets_blocking_scripts(
            nodes::document* document)
            -> ext::boolean;

    auto convert_nodes_into_node(
            const nodes::document* document,
            type_is<nodes::node*, ext::string> auto&&... nodes)
            -> nodes::node*;

    // element stuff
    auto qualified_name(
            const nodes::element* element)
            -> ext::string;

    auto html_uppercase_qualified_name(
            const nodes::element* element)
            -> ext::string;

    auto html_lowercase_qualified_name(
            const nodes::element* element)
            -> ext::string;
}


#endif //SBROWSER2_NODE_INTERNALS_HPP
