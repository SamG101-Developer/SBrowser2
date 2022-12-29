module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/macros.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.abort_controller;
import apis.dom_object;

import apis.dom.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom, abort_controller)
        : public virtual ::dom_object
{
public constructors:
    abort_controller();
    MAKE_PIMPL(abort_controller);
    MAKE_V8_AVAILABLE(ALL);

public js_methods:
    auto abort(ext::any&& reason) const -> void;

private js_properties:
    DEFINE_GETTER(signal, abort_signal*);
};
