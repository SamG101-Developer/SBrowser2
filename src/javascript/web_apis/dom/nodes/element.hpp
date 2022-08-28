#ifndef SBROWSER2_ELEMENT_HPP
#define SBROWSER2_ELEMENT_HPP

#include "dom/nodes/node.hpp"
#include "dom/mixins/child_node.hpp"
#include "dom/mixins/document_or_element_node.hpp"
#include "dom/mixins/non_document_type_child_node.hpp"
#include "dom/mixins/parentable_node.hpp"
#include "dom/mixins/slottable.hpp"
#include "aria/mixins/aria_mixin.hpp"
namespace dom::nodes {class element;}

#include "ext/optional.hpp"
#include "ext/queue.hpp"
#include "ext/map.hpp"
#include "ext/vector.hpp"
#include <future>
#include <range/v3/view/any_view.hpp>
#include USE_INNER_TYPES(css/box_tree)
#include USE_INNER_TYPES(dom)
#include USE_INNER_TYPES(fullscreen)

namespace css::box_tree {class dead_fragment_information;}
namespace dom::nodes {class attr;}
namespace dom::nodes {class shadow_root;}
namespace dom::detail {auto handle_attributes_changes(const nodes::attr*, nodes::element*, const ext::string&, const ext::string&) -> void;}
namespace dom::detail {auto create_an_element(nodes::document*, const ext::string&, const ext::string&, const ext::string&, const ext::string&, const ext::boolean&) -> nodes::element*;}
namespace dom::detail {auto upgrade_element(custom_element_definition_t*, nodes::element*) -> void;}
namespace dom::detail {auto try_to_upgrade_element(nodes::element* element) -> void;}
namespace edit_context {class edit_context;}


class dom::nodes::element
        : public node
        , public mixins::child_node
        , public mixins::document_or_element_node
        , public mixins::non_document_type_child_node
        , public mixins::parentable_node
        , public mixins::slottable
        , public aria::mixins::aria_mixin
{
public friends:
    friend class node;
    friend struct mixins::document_or_element_node;

    friend auto detail::handle_attributes_changes(
            const nodes::attr* attribute, nodes::element* owner_element, const ext::string& old_value,
            const ext::string& new_value) -> void;

    friend auto detail::create_an_element(
            nodes::document* document, const ext::string& local_name, const ext::string& namespace_,
            const ext::string& prefix, const ext::string& is, const ext::boolean& synchronous_custom_elements_flag)
            -> nodes::element*;

    friend auto detail::upgrade_element(
            detail::custom_element_definition_t* definition, nodes::element* element) -> void;

    friend auto detail::try_to_upgrade_element(
            nodes::element* element) -> void;

public constructors:
    DOM_CTORS(element);
    element();
    ~element() override;

public js_methods:
    /* DOM */
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
    auto set_attribute_node(attr* attribute) -> attr*;
    auto set_attribute_node_ns(attr* attribute) -> attr*;

    auto remove_attribute(ext::string_view qualified_name) -> attr*;
    auto remove_attribute_ns(ext::string_view namespace_, ext::string_view local_name) -> attr*;
    auto remove_attribute_node(attr* attribute) -> attr*;
    auto remove_attribute_node_ns(attr* attribute) -> attr*;

    auto toggle_attribute(ext::string_view qualified_name, ext::optional<ext::boolean>&& force) -> ext::boolean;
    auto toggle_attribute_ns(ext::string_view namespace_, ext::string_view local_name, ext::optional<ext::boolean>&& force) -> ext::boolean;
    auto toggle_attribute_node(attr* attribute, ext::optional<ext::boolean>&& force) -> attr*;
    auto toggle_attribute_node_ns(attr* attribute, ext::optional<ext::boolean>&& force) -> attr*;

    auto attach_shadow(ext::map<ext::string, ext::any>&& options) -> shadow_root;
    auto closest(ext::string_view selectors) -> element*;
    auto matches(ext::string_view selectors) -> ext::boolean;

    /* POINTER_EVENTS */
    auto set_pointer_capture(const ext::number<long> pointer_id) -> void;
    auto release_pointer_capture(const ext::number<long> pointer_id) -> void;
    auto has_pointer_capture(const ext::number<long> pointer_id) -> ext::boolean;

    /* POINTER_LOCK */
    auto request_pointer_lock() -> void;

    /* FULLSCREEN */
    auto request_fullscreen(fullscreen::detail::fullscreen_options_t&& options = {}) -> std::promise<void>;

    /* DOM_PARSING */
    auto insert_adjacent_html(ext::string_view position, ext::string&& text) -> void;

    /* CSS_BOX_TREE */
    auto get_fragment_information(css::detail::fragment_filter_t filter) -> std::promise<css::box_tree::dead_fragent_information*>;
    
public js_properties:
    ext::property<ext::string> namespace_uri;
    ext::property<ext::string> prefix;
    ext::property<ext::string> local_name;
    ext::property<ext::string> tag_name;
    ext::property<ext::string> class_name; // TODO CE_REACTIONS
    ext::property<ext::string> slot; // TODO CE_REACTIONS
    ext::property<ext::string> id; // TODO CE_REACTIONS
    ext::property<std::unique_ptr<shadow_root>> shadow_root_node;
    ext::property<std::unique_ptr<ext::vector<attr*>>> attributes;
    ext::property<std::unique_ptr<ext::vector<ext::string>>> class_list;

    /* EDIT_CONTENT */
    ext::property<std::unique_ptr<edit_context::edit_context>> edit_context;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

protected cpp_methods:
    [[nodiscard]] auto qualified_name() const -> ext::string;
    [[nodiscard]] auto html_uppercase_qualified_name() const -> ext::string;
    [[nodiscard]] auto html_lowercase_qualified_name() const -> ext::string;

private cpp_properties:
    ext::string m_is;
    detail::custom_element_definition_t* m_custom_element_definition;
    detail::custom_element_state_t m_custom_element_state;
    ext::queue<detail::reaction_t*> m_custom_element_reaction_queue;
    html::detail::context_internals::browsing_context* m_nested_browsing_context;

    /* FULLSCREEN */
    ext::boolean m_fullscreen_flag;

private cpp_accessors:
    DEFINE_GETTER(node_type) override {return ELEMENT_NODE;}
    DEFINE_GETTER(node_name) override {return html_uppercase_qualified_name();};
    DEFINE_GETTER(node_value) override;
    DEFINE_GETTER(text_content) override;
    DEFINE_SETTER(node_value) override;
    DEFINE_SETTER(text_content) override;

    DEFINE_GETTER(tag_name) {return html_uppercase_qualified_name();};
    DEFINE_GETTER(shadow_root_node);
};


#endif //SBROWSER2_ELEMENT_HPP
