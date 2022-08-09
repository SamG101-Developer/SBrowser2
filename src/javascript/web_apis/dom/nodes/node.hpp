#pragma once
#ifndef SBROWSER2_NODE_HPP
#define SBROWSER2_NODE_HPP

#include "dom/nodes/event_target.hpp"
namespace dom::nodes {class node;}

#include "ext/map.hpp"
#include <QtCore/QObject>
#include <QtCore/QPointer>
namespace dom::nodes {class element;}
namespace dom::nodes {class document;}
namespace dom::detail::observer_internals {struct registered_observer;}


class dom::nodes::node
        : public event_target
{
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
    auto clone_node(ext::boolean_view deep = false) -> node*;
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
    ext::property<ext::string, _T> node_name;
    ext::property<ext::string, _T> node_value;
    ext::property<ext::string, _T> text_content;

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
    virtual auto to_qt() const -> QWidget* {return m_rendered_widget.get();};
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

protected cpp_properties:
    QPointer<QWidget> m_rendered_widget;
    std::unique_ptr<ext::vector<detail::observer_internals::registered_observer*>> m_registered_observer_list;

protected cpp_accessors:
    _EXT_NODISCARD virtual auto get_node_type() const -> ext::number<ushort> = 0;
    _EXT_NODISCARD virtual auto get_node_name() const -> ext::string = 0;
    _EXT_NODISCARD virtual auto get_text_content() const -> ext::string = 0;
    _EXT_NODISCARD virtual auto get_node_value() const -> ext::string = 0;

    virtual auto set_node_value(ext::string_view val) -> void = 0;
    virtual auto set_text_content(ext::string_view val) -> void = 0;
    virtual auto set_parent_node(node* val) -> void;

private cpp_accessors:
    _EXT_NODISCARD auto get_is_connected() const -> bool;
    _EXT_NODISCARD auto get_base_uri() const -> ext::string&;
    _EXT_NODISCARD auto get_first_child() const -> node* {return *child_nodes()->begin();}
    _EXT_NODISCARD auto get_last_child() const -> node* {return *child_nodes()->end();}
    _EXT_NODISCARD auto get_previous_sibling() const -> node*;
    _EXT_NODISCARD auto get_next_sibling() const -> node*;
    _EXT_NODISCARD auto get_parent_element() const -> element*;

};


#endif //SBROWSER2_NODE_HPP
