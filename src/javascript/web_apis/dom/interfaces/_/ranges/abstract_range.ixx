module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/macros.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.abstract_range;
import apis.dom_object;

import apis.dom.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom, abstract_range)
        : public virtual dom_object
{
public constructors:
    abstract_range();
    MAKE_PIMPL(abstract_range);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(start_container, node*);
    DEFINE_GETTER(start_offset, ext::number<ulong>);
    DEFINE_GETTER(end_container, node*);
    DEFINE_GETTER(end_offset, ext::number<ulong>);
    DEFINE_GETTER(collapsed, ext::boolean);
};
