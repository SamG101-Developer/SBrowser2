#ifndef SBROWSER2_ELEMENT_HPP
#define SBROWSER2_ELEMENT_HPP

#include "dom/nodes/node.hpp"
#include "dom/mixins/child_node.hpp"
#include "dom/mixins/document_or_element_node.hpp"
#include "dom/mixins/non_document_type_child_node.hpp"
#include "dom/mixins/parentable_node.hpp"
#include "dom/mixins/slottable.hpp"
#include "aria/mixins/aria_mixin.hpp"
#include "css/css_web_animations/mixins/animatable.hpp"
namespace dom::nodes {class element;}
namespace dom::nodes {class element_private;}


#include "ext/optional.hpp"
#include "ext/queue.ixx"
#include "ext/map.ixx"
#include "ext/promise.hpp"
#include "ext/span.hpp"
#include "ext/vector.hpp"
#include <range/v3/view/any_view.hpp>

#include INCLUDE_INNER_TYPES(css/box_tree)
#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(intersection_observer)
#include INCLUDE_INNER_TYPES(fullscreen)

namespace css::box_tree {class dead_fragment_information;}
namespace dom::nodes {class attr;}
namespace dom::nodes {class node;}
namespace dom::nodes {class shadow_root;}
namespace dom::mixins {class document_or_element_node;}
namespace edit_context {class edit_context;}


class dom::nodes::element
        : public node
        , public mixins::child_node
        , public mixins::document_or_element_node
        , public mixins::non_document_type_child_node
        , public mixins::parentable_node
        , public mixins::slottable
        , public aria::mixins::aria_mixin
        , public css::css_web_animations::mixins::animatable
{
public friends:
    friend class dom::mixins::document_or_element_node;
    friend class dom::nodes::node;

public constructors:
    DOM_CTORS(element);
    MAKE_PIMPL(element);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    /* [DOM] */
    [[nodiscard]] auto has_attributes() const -> ext::boolean;
    [[nodiscard]] auto get_attribute_names() const -> ranges::any_view<ext::string>;

    [[nodiscard]] auto has_attribute(ext::string_view name) const -> ext::boolean;
    [[nodiscard]] auto has_attribute_ns(ext::string_view namespace_, ext::string_view local_name) const -> ext::boolean;
    [[nodiscard]] auto has_attribute_node(attr* attribute) const -> ext::boolean;
    [[nodiscard]] auto has_attribute_node_ns(attr* attribute) const -> ext::boolean;

    [[nodiscard]] auto get_attribute(ext::string_view qualified_name) const -> ext::string;
    [[nodiscard]] auto get_attribute_ns(ext::string_view namespace_, ext::string_view local_name) const -> ext::string;
    [[nodiscard]] auto get_attribute_node(ext::string_view qualified_name) const -> attr*;
    [[nodiscard]] auto get_attribute_node_ns(ext::string_view namespace_, ext::string_view local_name) const -> attr*;

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

    /* DOM_PARSING */
    auto insert_adjacent_html(ext::string_view position, ext::string&& text) -> void;

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
    DEFINE_GETTER(shadow_root, nodes::shadow_root*);
    DEFINE_GETTER(attributes, ranges::any_helpful_view<attr*>);

    /* [EDIT-CONTENT] */
    DEFINE_GETTER(edit_context, edit_context::edit_context*);
};


#endif //SBROWSER2_ELEMENT_HPP
