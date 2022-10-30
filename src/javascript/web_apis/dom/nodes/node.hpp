#pragma once
#ifndef SBROWSER2_NODE_HPP
#define SBROWSER2_NODE_HPP

#include "dom/nodes/event_target.hpp"
namespace dom::nodes {class node;}
namespace dom::nodes {class node_private;}

#include "ext/map.hpp"
#include <range/v3/view/any_view.hpp>
#include INCLUDE_INNER_TYPES(dom)
namespace dom::nodes {class element;}
namespace dom::nodes {class document;}
namespace dom::mixins {class child_node;}
namespace dom::mixins {class document_or_element_node;}
namespace dom::mixins {class non_document_type_child_node;}
namespace dom::mixins {class parentable_node;}
namespace dom::mutations {class mutation_observer;}
namespace dom::node_ranges {class range;}
namespace html::elements {class html_option_element;}


class dom::nodes::node
        : public event_target
{
public friends:
    friend class dom::mixins::child_node;
    friend class dom::mixins::document_or_element_node;
    friend class dom::mixins::non_document_type_child_node;
    friend class dom::mixins::parentable_node;
    friend class dom::mutations::mutation_observer;
    friend class dom::node_ranges::range;
    friend class html::elements::html_option_element;

public constructors:
    DOM_CTORS(node);
    MAKE_PIMPL(node);
    MAKE_V8_AVAILABLE;

public js_static_constants:
    constexpr static const ext::number<ushort> ELEMENT_NODE = 1;
    constexpr static const ext::number<ushort> ATTRIBUTE_NODE = 2;
    constexpr static const ext::number<ushort> TEXT_NODE = 3;
    constexpr static const ext::number<ushort> CDATA_SECTION_NODE = 4;
    constexpr static const ext::number<ushort> PROCESSING_INSTRUCTION_NODE = 7;
    constexpr static const ext::number<ushort> COMMENT_NODE = 8;
    constexpr static const ext::number<ushort> DOCUMENT_NODE = 9;
    constexpr static const ext::number<ushort> DOCUMENT_TYPE_NODE = 10;
    constexpr static const ext::number<ushort> DOCUMENT_FRAGMENT_NODE = 11;
    
    constexpr static const ext::number<ushort> DOCUMENT_POSITION_DISCONNECTED = 0x01;
    constexpr static const ext::number<ushort> DOCUMENT_POSITION_PRECEDING = 0x02;
    constexpr static const ext::number<ushort> DOCUMENT_POSITION_FOLLOWING = 0x04;
    constexpr static const ext::number<ushort> DOCUMENT_POSITION_CONTAINS = 0x08;
    constexpr static const ext::number<ushort> DOCUMENT_POSITION_CONTAINED_BY = 0x10;
    constexpr static const ext::number<ushort> DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC = 0x20;

public js_methods:
    auto compare_document_position(node* other) -> ext::number<ushort>;
    auto get_root_node(ext::map<ext::string, ext::any>&& options) -> node*;
    auto contains(node* other) -> ext::boolean;
    auto has_child_nodes() -> ext::boolean;

    auto normalize() -> node*;
    auto clone_node(ext::boolean deep = false) -> std::unique_ptr<node>;
    auto is_equal_node(node* other) -> ext::boolean;

    auto is_default_namespace(ext::string_view namespace_) -> ext::boolean;
    auto lookup_prefix(ext::string_view namespace_) -> ext::string;
    auto lookup_namespace_uri(ext::string_view prefix) -> ext::string;

    auto insert_before(std::unique_ptr<node>&& new_node, node* child) -> node*;
    auto append_child(std::unique_ptr<node>&& new_node) -> node*;
    auto replace_child(node* old_node, std::unique_ptr<node>&& new_node) -> node*;
    auto remove_child(node* old_node) -> node*;

private js_properties:
    virtual DEFINE_GETTER(node_type, ext::number<ushort>) = 0;
    virtual DEFINE_GETTER(node_name, ext::string) = 0;
    virtual DEFINE_GETTER(text_content, ext::string) = 0;
    virtual DEFINE_GETTER(node_value, ext::string) = 0;

    virtual DEFINE_SETTER(text_content, ext::string) = 0;
    virtual DEFINE_SETTER(node_value, ext::string) = 0;

    DEFINE_GETTER(base_uri, ext::string);
    DEFINE_GETTER(is_connected, ext::boolean);
    DEFINE_GETTER(child_nodes, ranges::any_view<node*>);
    DEFINE_GETTER(parent_node, node*);
    DEFINE_GETTER(parent_element, element*);
    DEFINE_GETTER(owner_document, document*);
    DEFINE_GETTER(first_child, node*);
    DEFINE_GETTER(last_child, node*);
    DEFINE_GETTER(previous_sibling, node*);
    DEFINE_GETTER(next_sibling, node*);
};


#endif //SBROWSER2_NODE_HPP
