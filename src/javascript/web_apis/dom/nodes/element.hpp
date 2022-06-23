#ifndef SBROWSER2_ELEMENT_HPP
#define SBROWSER2_ELEMENT_HPP

#include <ext/map.hpp>
#include <ext/vector.hpp>
#include <dom/nodes/node.hpp>
namespace dom::nodes {class attr;}
namespace dom::nodes {class element;}
namespace dom::nodes {class shadow_root;}
namespace dom::detail::customization_internals {struct custom_element_definition;}
namespace dom::detail::customization_internals {struct reaction;}
namespace dom::detail::customization_internals {enum   custom_element_state_t;}
namespace dom::detail::customization_internals {auto create_an_element(nodes::document* document, ext::string_view local_name, ext::string_view namespace_, ext::string_view prefix, ext::string_view is, ext::boolean_view synchronous_custom_elements_flag) -> nodes::element*;}
namespace dom::detail::customization_internals {auto upgrade_element(custom_element_definition* definition, nodes::element* element) -> void;}
namespace html::detail::context_internals {struct browsing_context;}


class dom::nodes::element
        : public node
{
public friends:
    friend auto dom::detail::customization_internals::create_an_element(
            nodes::document* document, ext::string_view local_name, ext::string_view namespace_,
            ext::string_view prefix, ext::string_view is, ext::boolean_view synchronous_custom_elements_flag)
            -> nodes::element*;

    friend auto dom::detail::customization_internals::upgrade_element(
            detail::customization_internals::custom_element_definition* definition, nodes::element* element)
            -> void;

public constructors:
    element();

public js_methods:
    auto has_attributes() const -> bool;
    auto get_attribute_names() const -> ext::string_vector;

    auto has_attribute(ext::string_view name) const -> bool;
    auto has_attribute_ns(ext::string_view namespace_, ext::string_view local_name) const -> bool;
    auto has_attribute_node(attr* attribute) const -> bool;
    auto has_attribute_node_ns(attr* attribute) const -> bool;

    auto get_attribute(ext::string_view qualified_name) const -> ext::string;
    auto get_attribute_ns(ext::string_view namespace_, ext::string_view local_name) const -> ext::string;
    auto get_attribute_node(ext::string_view qualified_name) const -> attr*;
    auto get_attribute_node_ns(ext::string_view namespace_, ext::string_view local_name) const -> attr*;

    auto set_attribute(ext::string_view qualified_name, ext::string_view value) -> void;
    auto set_attribute_ns(ext::string_view namespace_, ext::string_view qualified_name, ext::string_view value) -> void;
    auto set_attribute_node(attr* attribute) -> attr*;
    auto set_attribute_node_ns(attr* attribute) -> attr*;

    auto remove_attribute(ext::string_view qualified_name) -> void;
    auto remove_attribute_ns(ext::string_view namespace_, ext::string_view local_name) -> void;
    auto remove_attribute_node(attr* attribute) -> attr*;
    auto remove_attribute_node_ns(attr* attribute) -> attr*;

    auto toggle_attribute(ext::string_view qualified_name, bool force = false) -> bool;
    auto toggle_attribute_ns(ext::string_view namespace_, ext::string_view local_name, bool force = false) -> bool;
    auto toggle_attribute_node(attr* attribute, bool force = false) -> attr*;
    auto toggle_attribute_node_ns(attr* attribute, bool force = false) -> attr*;

    auto attach_shadow(ext::string_any_map_view options) -> shadow_root;
    auto closest(ext::string_view selectors) -> element*;
    auto matches(ext::string_view selectors) -> bool;
    
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
    ext::property<std::unique_ptr<ext::string_vector>> class_list;

protected cpp_methods:
    auto qualified_name() const -> ext::string_view;
    auto html_uppercase_qualified_name() const -> ext::string_view;

    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    ext::string m_is;
    detail::customization_internals::custom_element_definition* m_custom_element_definition;
    detail::customization_internals::custom_element_state_t     m_custom_element_state;
    std::queue<detail::customization_internals::reaction*>      m_custom_element_reaction_queue;
    html::detail::context_internals::browsing_context* m_nested_browsing_context;

private cpp_accessors:
    [[nodiscard]] auto get_node_name() const -> ext::string override {return html_uppercase_qualified_name();};
    [[nodiscard]] auto get_node_value() const -> ext::string override;
    [[nodiscard]] auto get_text_content() const -> ext::string override;

    auto set_node_value(ext::string_view val) -> void override;
    auto set_text_content(ext::string_view val) -> void override;
};


#endif //SBROWSER2_ELEMENT_HPP
