#ifndef SBROWSER2_DOCUMENT_FRAGMENT_HPP
#define SBROWSER2_DOCUMENT_FRAGMENT_HPP

#include <dom/nodes/node.hpp>
#include <dom/mixins/non_element_parent_node.hpp>
#include <dom/mixins/parentable_node.hpp>
namespace dom::nodes {class document_fragment;}


class dom::nodes::document_fragment
        : public node
        , public mixins::non_element_parent_node
        , public mixins::parentable_node
{
public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    [[nodiscard]] auto get_node_type() const -> ext::number<ushort> override {return DOCUMENT_FRAGMENT_NODE;}
    [[nodiscard]] auto get_node_name() const -> ext::string override {return "#document-fragment";}
    [[nodiscard]] auto get_node_value() const -> ext::string override {return "";}
    [[nodiscard]] auto get_text_content() const -> ext::string override;

    auto set_node_value(ext::string_view val) -> void override {}
    auto set_text_content(ext::string_view val) -> void override;
};


#endif //SBROWSER2_DOCUMENT_FRAGMENT_HPP
