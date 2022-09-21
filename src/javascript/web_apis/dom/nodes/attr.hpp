#ifndef SBROWSER2_ATTR_HPP
#define SBROWSER2_ATTR_HPP

#include "dom/nodes/node.hpp"
namespace dom::nodes {class attr;}

#include "dom/nodes/attr_private.hpp"
namespace dom::nodes {class element;}


class dom::nodes::attr final
        : public node
{
public constructors:
    attr();

public js_properties:
    ext::property<ext::string> namespace_uri;
    ext::property<ext::string> prefix;
    ext::property<ext::string> local_name;
    ext::property<ext::string> name;
    ext::property<ext::string> value; // TODO : CE_REACTIONS
    ext::property<std::unique_ptr<element>> owner_element;

private cpp_members:
    MAKE_V8_AVAILABLE;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(node_type) override {return ATTRIBUTE_NODE;}
    DEFINE_CUSTOM_GETTER(node_name) override;
    DEFINE_CUSTOM_GETTER(node_value) override {return value();};
    DEFINE_CUSTOM_GETTER(text_content) override {return value();};

    DEFINE_CUSTOM_SETTER(node_value) override {value = val;};
    DEFINE_CUSTOM_SETTER(text_content) override {value = val;};
    DEFINE_CUSTOM_SETTER(value);
};


#endif //SBROWSER2_ATTR_HPP
