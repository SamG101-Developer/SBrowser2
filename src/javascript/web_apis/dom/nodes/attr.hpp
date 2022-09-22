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
    MAKE_PIMPL(attr);
    MAKE_V8_AVAILABLE;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(node_type) override {return ATTRIBUTE_NODE;}
    DEFINE_CUSTOM_GETTER(node_name) override;
    DEFINE_CUSTOM_GETTER(node_value) override {return value();};
    DEFINE_CUSTOM_GETTER(text_content) override {return value();};

    DEFINE_CUSTOM_SETTER(node_value) override {value = val;};
    DEFINE_CUSTOM_SETTER(text_content) override {value = val;};

    DEFINE_CUSTOM_GETTER(namespace_uri) {return d_ptr->namespace_;}
    DEFINE_CUSTOM_GETTER(prefix) {return d_ptr->namespace_prefix;}
    DEFINE_CUSTOM_GETTER(local_name) {return d_ptr->local_name;}
    DEFINE_CUSTOM_GETTER(name);
    DEFINE_CUSTOM_GETTER(value);
    DEFINE_CUSTOM_GETTER(owner_element) {return d_ptr->element;}

    DEFINE_CUSTOM_SETTER(value);
};


#endif //SBROWSER2_ATTR_HPP
