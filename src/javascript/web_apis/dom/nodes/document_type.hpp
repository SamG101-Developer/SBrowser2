#ifndef SBROWSER2_DOCUMENT_TYPE_HPP
#define SBROWSER2_DOCUMENT_TYPE_HPP

#include "dom/nodes/node.hpp"
#include "dom/mixins/child_node.hpp"
namespace dom::nodes {class document_type;}

class dom::nodes::document_type final
        : public node
        , public mixins::child_node
{
public js_methods:
    ext::property<ext::string> name;
    ext::property<ext::string> public_id;
    ext::property<ext::string> system_id;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(node_type) override {return DOCUMENT_TYPE_NODE;}
    DEFINE_CUSTOM_GETTER(node_name) override {return name();};
    DEFINE_CUSTOM_GETTER(node_value) override {return "";};
    DEFINE_CUSTOM_GETTER(text_content) override {return "";};

    DEFINE_CUSTOM_SETTER(node_value) override {};
    DEFINE_CUSTOM_SETTER(text_content) override {};
};


#endif //SBROWSER2_DOCUMENT_TYPE_HPP
