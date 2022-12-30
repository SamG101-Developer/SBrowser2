module;
#include "ext/macros/annotations.hpp"
#include "ext/macros.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom_parsing.mixins.inner_html;
import apis.dom_object;

import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom_parsing::mixins, inner_html)
        : virtual public dom_object
{
public constructors:
    inner_html();
    MAKE_PIMPL(inner_html);
    MAKE_V8_AVAILABLE(MIXIN);

public js_properties:
    virtual DEFINE_GETTER(inner_html, ext::string);
    virtual DEFINE_SETTER(inner_html, ext::string&&);
};
