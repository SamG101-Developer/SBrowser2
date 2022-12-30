module;
#include "ext/macros.hpp"


export module apis.dom.mixins.slottable;
import apis.dom_object;

import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom::mixins, slottable)
        : public virtual dom_object
{
public friends:
    friend class dom::node;

public constructors:
    slottable();
    MAKE_PIMPL(slottable);
    MAKE_V8_AVAILABLE(MIXIN);

private js_properties:
    DEFINE_GETTER(assigned_slot, html::html_slot_element*);
};
