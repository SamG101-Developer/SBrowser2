module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.mixins.slottable;
import apis._.dom_object;
import ext.tuple;
import ext.type_traits;
import js.env.module_type;

namespace dom {class node;}
namespace html {class html_slot_element;}


DEFINE_PUBLIC_CLASS(dom, slottable)
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
