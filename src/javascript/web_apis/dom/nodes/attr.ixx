module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.attr;
import apis.dom.node;

import apis.dom.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom, attr) final
        : public node
{
public friends:
    friend class dom::element;
    friend class dom::node;

public constructors:
    attr();
    MAKE_PIMPL(attr);
    MAKE_V8_AVAILABLE(WINDOW);

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
