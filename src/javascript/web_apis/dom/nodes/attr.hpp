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

private cpp_members:
    MAKE_PIMPL(attr);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return ATTRIBUTE_NODE;}
    DEFINE_GETTER(node_name, ext::string) override;
    DEFINE_GETTER(node_value, ext::string) override {return d_ptr->value;}
    DEFINE_GETTER(text_content, ext::string) override {return d_ptr->value;}

    DEFINE_SETTER(node_value, ext::string) override {d_ptr->value = new_node_value;}
    DEFINE_SETTER(text_content, ext::string) override {d_ptr->value = new_text_content;}

    DEFINE_GETTER(namespace_uri, ext::string) {return d_ptr->namespace_;}
    DEFINE_GETTER(prefix, ext::string) {return d_ptr->namespace_prefix;}
    DEFINE_GETTER(local_name, ext::string) {return d_ptr->local_name;}
    DEFINE_GETTER(name, ext::string);
    DEFINE_GETTER(value, ext::string);
    DEFINE_GETTER(owner_element, element*) {return d_ptr->element;}

    DEFINE_SETTER(value, ext::string);
};


#endif //SBROWSER2_ATTR_HPP
