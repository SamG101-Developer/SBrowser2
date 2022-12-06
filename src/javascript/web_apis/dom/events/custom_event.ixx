module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.custom_event;
import apis.dom.event;
import ext.any;
import ext.string;
import ext.tuple;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom, custom_event) final
        : public event
{
public typedefs:
    using custom_event_init_t = event_init_t;

public constructors:
    custom_event() = default;
    custom_event(ext::string&& event_type, custom_event_init_t&& event_init = {});
    MAKE_PIMPL(custom_event);
    MAKE_V8_AVAILABLE(ALL);

private js_properties:
    DEFINE_GETTER(detail, ext::any);
};
