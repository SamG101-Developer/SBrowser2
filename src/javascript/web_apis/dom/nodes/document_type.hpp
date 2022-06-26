#ifndef SBROWSER2_DOCUMENT_TYPE_HPP
#define SBROWSER2_DOCUMENT_TYPE_HPP

#include <web_apis/dom/nodes/node.hpp>
#include <web_apis/dom/mixins/child_node.hpp>
namespace dom::nodes {class document_type;}

class dom::nodes::document_type
        : public node
        , public mixins::child_node
{
public js_methods:
    ext::property<ext::string> name;
    ext::property<ext::string> public_id;
    ext::property<ext::string> system_id;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_accessors:
    [[nodiscard]] auto get_node_name() const -> ext::string override {return "#document-fragment";};
    [[nodiscard]] auto get_node_value() const -> ext::string override {return "";};
    [[nodiscard]] auto get_text_content() const -> ext::string override {return "";};

    auto set_node_value(ext::string_view val) -> void override {};
    auto set_text_content(ext::string_view val) -> void override {};
};


#endif //SBROWSER2_DOCUMENT_TYPE_HPP