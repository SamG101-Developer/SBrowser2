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
#include <range/v3/view/any_view.hpp>
using namespace ext::shorthand;
namespace dom::nodes {class attr;}
namespace dom::nodes {class shadow_root;}
namespace dom::detail::customization_internals {struct custom_element_definition;}
namespace dom::detail::customization_internals {struct reaction;}
namespace dom::detail::customization_internals {enum custom_element_state_t;}
namespace dom::detail::customization_internals {auto create_an_element(nodes::document*, sv, sv, sv, sv, bv) -> nodes::element;}
namespace dom::detail::customization_internals {auto upgrade_element(custom_element_definition*, nodes::element*) -> void;}
namespace html::detail::context_internals {struct browsing_context;}


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
    friend auto dom::detail::customization_internals::create_an_element(
            nodes::document* document, ext::string_view local_name, ext::string_view namespace_,
            ext::string_view prefix, ext::string_view is, ext::boolean_view synchronous_custom_elements_flag)
            -> nodes::element;

    friend auto dom::detail::customization_internals::upgrade_element(
            detail::customization_internals::custom_element_definition* definition, nodes::element* element)
            -> void;

public constructors:
    element();
    ~element() override;

public js_methods:
    /* DOM */
    [[nodiscard]] auto has_attributes() const -> ext::boolean;
    [[nodiscard]] auto get_attribute_names() const -> ranges::any_view<ext::string>;

    [[nodiscard]] auto has_attribute(ext::string_view name) const -> ext::boolean;
    [[nodiscard]] auto has_attribute_ns(ext::string_view namespace_, ext::string_view local_name) const -> ext::boolean;
    auto has_attribute_node(attr* attribute) const -> ext::boolean;
    auto has_attribute_node_ns(attr* attribute) const -> ext::boolean;

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

    auto toggle_attribute(ext::string_view qualified_name, ext::optional<ext::boolean> force) -> ext::boolean;
    auto toggle_attribute_ns(ext::string_view namespace_, ext::string_view local_name, ext::optional<ext::boolean> force) -> ext::boolean;
    auto toggle_attribute_node(attr* attribute, ext::optional<ext::boolean> force) -> attr*;
    auto toggle_attribute_node_ns(attr* attribute, ext::optional<ext::boolean> force) -> attr*;

    auto attach_shadow(ext::map<ext::string, ext::any>&& options) -> shadow_root*;
    auto closest(ext::string_view selectors) -> element*;
    auto matches(ext::string_view selectors) -> ext::boolean;

    /* PointerEvents */
    auto set_pointer_capture(ext::number_view<long> pointer_id) -> void;
    auto release_pointer_capture(ext::number_view<long> pointer_id) -> void;
    auto has_pointer_capture(ext::number_view<long> pointer_id) -> ext::boolean;
    
public js_properties:
    ext::property<ext::string> namespace_uri;
    ext::property<ext::string> prefix;
    ext::property<ext::string> local_name;
    ext::property<ext::string> tag_name;
    ext::property<ext::string, _T> class_name;
    ext::property<ext::string, _T> slot;
    ext::property<ext::string, _T> id;
    ext::property<std::unique_ptr<shadow_root>> shadow_root_node;
    ext::property<std::unique_ptr<ext::vector<attr*>>> attributes;
    ext::property<std::unique_ptr<ext::vector<ext::string>>> class_list;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

protected cpp_methods:
    [[nodiscard]] auto qualified_name() const -> ext::string;
    [[nodiscard]] auto html_uppercase_qualified_name() const -> ext::string;
    [[nodiscard]] auto html_lowercase_qualified_name() const -> ext::string;

private cpp_properties:
    ext::string m_is;
    detail::customization_internals::custom_element_definition* m_custom_element_definition;
    detail::customization_internals::custom_element_state_t     m_custom_element_state;
    ext::queue<detail::customization_internals::reaction*>      m_custom_element_reaction_queue;
    html::detail::context_internals::browsing_context* m_nested_browsing_context;

private cpp_accessors:
    [[nodiscard]] auto get_node_type() const -> ext::number<ushort> override {return ELEMENT_NODE;}
    [[nodiscard]] auto get_node_name() const -> ext::string override {return html_uppercase_qualified_name();};
    [[nodiscard]] auto get_node_value() const -> ext::string override;
    [[nodiscard]] auto get_text_content() const -> ext::string override;
    auto set_node_value(ext::string_view val) -> void override;
    auto set_text_content(ext::string_view val) -> void override;

    [[nodiscard]] auto get_tag_name() const -> ext::string {return html_uppercase_qualified_name();};
    [[nodiscard]] auto get_shadow_root_node() const -> shadow_root*;
};


#endif //SBROWSER2_ELEMENT_HPP
