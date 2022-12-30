module;
#include "ext/macros.hpp"


export module apis.dom.abstract_iterator;
import apis.dom_object;
import apis.dom.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom, abstract_iterator)
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(abstract_iterator);
    MAKE_PIMPL(abstract_iterator);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(filter, node_filter*);
    DEFINE_GETTER(root, node*);
    DEFINE_GETTER(what_to_show, ext::number<ulong>);
};
