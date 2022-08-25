#pragma once
#ifndef SBROWSER2_NODE_HPP
#define SBROWSER2_NODE_HPP

#include "dom/nodes/event_target.hpp"
namespace dom::nodes {class node;}

#include "ext/map.hpp"
#include <QtCore/QObject>
#include <QtCore/QPointer>
#include USE_INNER_TYPES(dom)
namespace dom::nodes {class element;}
namespace dom::nodes {class document;}

namespace dom::detail {auto notify_mutation_observers() -> void;}


class dom::nodes::node
        : public event_target
{
public friends:
    friend auto dom::detail::notify_mutation_observers()
            -> void;

public constructors:
    DOM_CTORS(node);
    node();

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
    auto clone_node(ext::boolean&& deep = false) -> node*;
    auto is_equal_node(node* other) -> ext::boolean;

    auto is_default_namespace(ext::string_view namespace_) -> ext::boolean;
    auto lookup_prefix(ext::string_view namespace_) -> ext::string;
    auto lookup_namespace_uri(ext::string_view prefix) -> ext::string;

    auto insert_before(node* new_node, node* child) -> node*;
    auto append_child(node* new_node) -> node*;
    auto replace_child(node* old_node, node* new_node) -> node*;
    auto remove_child(node* old_node) -> node*;

public js_properties:
    ext::property<ext::number<ushort>> node_type;
    ext::property<ext::string> node_name; // TODO CE_REACTIONS
    ext::property<ext::string> node_value; // TODO CE_REACTIONS
    ext::property<ext::string> text_content; // TODO CE_REACTIONS

    ext::property<ext::string> base_uri;
    ext::property<ext::boolean> is_connected;

    ext::property<std::unique_ptr<ext::vector<node*>>> child_nodes;
    ext::property<std::unique_ptr<node>> parent_node;
    ext::property<std::unique_ptr<document>> owner_document;
    ext::property<element*> parent_element;

    ext::property<node*> first_child;
    ext::property<node*> last_child;
    ext::property<node*> previous_sibling;
    ext::property<node*> next_sibling;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

protected cpp_properties:
    std::unique_ptr<ext::vector<detail::registered_observer_t*>> m_registered_observer_list;

protected cpp_accessors:
    virtual DEFINE_GETTER(node_type) = 0;
    virtual DEFINE_GETTER(node_name) = 0;
    virtual DEFINE_GETTER(text_content) = 0;
    virtual DEFINE_GETTER(node_value) = 0;

    virtual DEFINE_SETTER(node_value) = 0;
    virtual DEFINE_SETTER(text_content) = 0;

private cpp_accessors:
    DEFINE_GETTER(is_connected);
    DEFINE_GETTER(base_uri);
    DEFINE_GETTER(first_child) {return *child_nodes()->begin();}
    DEFINE_GETTER(last_child) {return *child_nodes()->end();}
    DEFINE_GETTER(previous_sibling);
    DEFINE_GETTER(next_sibling);
    DEFINE_GETTER(parent_element);

};


#endif //SBROWSER2_NODE_HPP
