#ifndef SBROWSER2_ATTR_HPP
#define SBROWSER2_ATTR_HPP

#include <web_apis/dom/nodes/node.hpp>
namespace dom::nodes {class attr;}

namespace dom::nodes {class element;}


class dom::nodes::attr
        : public node
{
public constructors:
    attr();

public js_properties:
    ext::property<ext::string> namespace_uri;
    ext::property<ext::string> prefix;
    ext::property<ext::string> local_name;
    ext::property<ext::string> name;
    ext::property<ext::string> value;
    ext::property<std::unique_ptr<element>> owner_element;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_methods:
    [[nodiscard]] auto qualified_name() const -> ext::string;

private cpp_accessors:
    [[nodiscard]] auto get_node_name() const -> ext::string override {return qualified_name();};
    [[nodiscard]] auto get_node_value() const -> ext::string override {return value();};
    [[nodiscard]] auto get_text_content() const -> ext::string override {return value();};

    auto set_node_value(ext::string_view val) -> void override {value = val;};
    auto set_text_content(ext::string_view val) -> void override {value = val;};
    auto set_value(ext::string_view val) -> void;
};


#endif //SBROWSER2_ATTR_HPP
