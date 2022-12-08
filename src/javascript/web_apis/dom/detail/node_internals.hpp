#ifndef SBROWSER2_NODE_INTERNALS_HPP
#define SBROWSER2_NODE_INTERNALS_HPP



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
            const nodes::element* node,
            ext::string_view prefix)
            -> ext::string;

    // list elements with certain features


    // other


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
