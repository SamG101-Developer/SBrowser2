module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.device_orientation.device_orientation_event;
import apis.dom.event;

import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(device_orientation, device_orientation_event) final
        : public dom::event
{
public typedefs:
    using device_orientation_event_init_t = ext::map<ext::string, ext::any>;

public constructors:
    device_orientation_event(ext::string&& event_type, device_orientation_event_init_t&& event_init = {});
    MAKE_PIMPL(device_orientation_event);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

public js_methods:
    static auto request_permission() -> ext::promise<permissions::detail::permission_state_t>;

private js_properties:
    DEFINE_GETTER(alpha, ext::number<double>);
    DEFINE_GETTER(beta, ext::number<double>);
    DEFINE_GETTER(gamma, ext::number<double>);
    DEFINE_GETTER(absolute, ext::boolean);
};
