module;
#include "ext/macros.hpp"

export module apis.dom.abort_controller;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);


DEFINE_PUBLIC_CLASS(dom, abort_controller)
        : public virtual ::dom_object
{
public constructors:
    abort_controller();
    MAKE_PIMPL(abort_controller);
    MAKE_V8_AVAILABLE(ALL);

private js_methods:
    auto abort(ext::any&& reason) const -> void;

private js_properties:
    DEFINE_GETTER(signal, abort_signal*);
};
