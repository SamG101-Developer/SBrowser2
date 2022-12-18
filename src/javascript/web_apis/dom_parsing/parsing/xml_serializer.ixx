module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"


export module apis.dom_parsing.xml_serializer;
import apis._.dom_object;

import ext.string;

namespace dom {class node;}


DEFINE_PUBLIC_CLASS(dom_parsing, xml_serializer) final
        : public virtual dom_object
{
public constructors:
    xml_serializer() = default;

public js_methods:
    auto serialize_to_string(dom::node* root) -> ext::string;
};
