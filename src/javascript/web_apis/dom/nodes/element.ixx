module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/constructors.hpp"
#include "ext/macros/extended_attributes.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"
#include <tl/optional.hpp>


export module apis.dom.element;
import apis.dom.node;
import apis.dom.mixins.child_node;
import apis.dom.mixins.document_or_element_node;
import apis.dom.mixins.non_document_type_child_node;
import apis.dom.mixins.parentable_node;
import apis.dom.mixins.slottable;
import apis.aria.mixins.aria_mixin;
import apis.dom_parsing.mixins.inner_html;

import apis.css.box_tree.types;
import apis.dom.types;
import apis.edit_context.types;

import ext.core;
import ext.js;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom, element)
        : public dom::node
        , public dom::child_node
        , public dom::document_or_element_node
        , public dom::non_document_type_child_node
        , public dom::parentable_node
        , public dom::slottable
        , public aria::aria_mixin
        , public dom_parsing::inner_html
{
public friends:
    friend class dom::document_or_element_node;
    friend class dom::node;

public constructors:
    DOM_CTORS(element);
    MAKE_PIMPL(element);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    /* [DOM] */
    _EXT_NODISCARD auto has_attributes() const -> ext::boolean;
    _EXT_NODISCARD auto get_attribute_names() const -> ranges::any_helpful_view<ext::string>;

    _EXT_NODISCARD auto has_attribute(ext::string_view name) const -> ext::boolean;
    _EXT_NODISCARD auto has_attribute_ns(ext::string_view namespace_, ext::string_view local_name) const -> ext::boolean;
    _EXT_NODISCARD auto has_attribute_node(attr* attribute) const -> ext::boolean;
    _EXT_NODISCARD auto has_attribute_node_ns(attr* attribute) const -> ext::boolean;

    _EXT_NODISCARD auto get_attribute(ext::string_view qualified_name) const -> ext::string;
    _EXT_NODISCARD auto get_attribute_ns(ext::string_view namespace_, ext::string_view local_name) const -> ext::string;
    _EXT_NODISCARD auto get_attribute_node(ext::string_view qualified_name) const -> attr*;
    _EXT_NODISCARD auto get_attribute_node_ns(ext::string_view namespace_, ext::string_view local_name) const -> attr*;

    auto set_attribute(ext::string_view qualified_name, ext::string_view value) -> attr*;
    auto set_attribute_ns(ext::string_view namespace_, ext::string_view qualified_name, ext::string_view value) -> attr*;
    auto set_attribute_node(std::unique_ptr<attr>&& attribute) -> attr*;
    auto set_attribute_node_ns(std::unique_ptr<attr>&& attribute) -> attr*;

    auto remove_attribute(ext::string_view qualified_name) -> attr*;
    auto remove_attribute_ns(ext::string_view namespace_, ext::string_view local_name) -> attr*;
    auto remove_attribute_node(attr* attribute) -> attr*;
    auto remove_attribute_node_ns(attr* attribute) -> attr*;

    auto toggle_attribute(ext::string_view qualified_name, ext::optional<ext::boolean>&& force) -> ext::boolean;
    auto toggle_attribute_ns(ext::string_view namespace_, ext::string_view local_name, ext::optional<ext::boolean>&& force) -> ext::boolean;
    auto toggle_attribute_node(attr* attribute, ext::optional<ext::boolean>&& force) -> attr*;
    auto toggle_attribute_node_ns(attr* attribute, ext::optional<ext::boolean>&& force) -> attr*;

    auto attach_shadow(ext::map<ext::string, ext::any>&& options) -> std::unique_ptr<shadow_root>;
    auto closest(ext::string_view selectors) -> element*;
    auto matches(ext::string_view selectors) -> ext::boolean;

    /* POINTER_EVENTS */
    auto set_pointer_capture(ext::number<long> pointer_id) -> void;
    auto release_pointer_capture(ext::number<long> pointer_id) -> void;
    auto has_pointer_capture(ext::number<long> pointer_id) -> ext::boolean;

    /* POINTER_LOCK */
    auto request_pointer_lock() -> void;

    /* FULLSCREEN */
    auto request_fullscreen(fullscreen::detail::fullscreen_options_t&& options = {}) -> ext::promise<void>;

    /* [DOM_PARSING] */
    auto insert_adjacent_html(ext::string_view position, ext::string&& text) -> void; // TODO : CE_REACTIONS

    /* CSS_BOX_TREE */
    // auto get_fragment_information(css::detail::fragment_filter_t filter) -> ext::promise<css::box_tree::dead_fragent_information*>;
    
private js_properties:
    /* [DOM] */
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return ELEMENT_NODE;}
    DEFINE_GETTER(node_name, ext::string) override;
    DEFINE_GETTER(node_value, ext::string) override;
    DEFINE_GETTER(text_content, ext::string) override;

    DEFINE_SETTER(node_value, ext::string) override;
    DEFINE_SETTER(text_content, ext::string) override;

    DEFINE_GETTER(namespace_uri, ext::string);
    DEFINE_GETTER(prefix, ext::string);
    DEFINE_GETTER(local_name, ext::string);
    DEFINE_GETTER(tag_name, ext::string);
    DEFINE_GETTER(class_list, ext::vector<ext::string>);
    DEFINE_GETTER(class_name, ext::string);
    DEFINE_GETTER(slot, ext::string);
    DEFINE_GETTER(id, ext::string);
    DEFINE_GETTER(shadow_root, shadow_root*);
    DEFINE_GETTER(attributes, ranges::any_helpful_view<attr*>);

    /* [DOM_PARSING] */
    virtual DEFINE_GETTER(outer_html, ext::string);

    /* [EDIT-CONTENT] */
    DEFINE_GETTER(edit_context, edit_context::edit_context*);
};
