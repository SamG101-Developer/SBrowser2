#ifndef SBROWSER2_ATTR_HPP
#define SBROWSER2_ATTR_HPP

#include "dom/nodes/node.hpp"
namespace dom::nodes {class attr;}
namespace dom::nodes {class attr_private;}

namespace dom::nodes {class element;}


class dom::nodes::attr final
        : public node
{
public constructors:
    attr();
    MAKE_PIMPL(attr);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return ATTRIBUTE_NODE;}
    DEFINE_GETTER(node_name, ext::string) override;
    DEFINE_GETTER(node_value, ext::string) override;
    DEFINE_GETTER(text_content, ext::string) override;

    DEFINE_SETTER(node_value, ext::string) override;
    DEFINE_SETTER(text_content, ext::string) override;

    DEFINE_GETTER(namespace_uri, ext::string);
    DEFINE_GETTER(prefix, ext::string);
    DEFINE_GETTER(local_name, ext::string);
    DEFINE_GETTER(name, ext::string);
    DEFINE_GETTER(value, ext::string);
    DEFINE_GETTER(owner_element, element*);

    DEFINE_SETTER(value, ext::string);
};


#endif //SBROWSER2_ATTR_HPP
