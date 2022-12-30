module;
#include "ext/macros/annotations.hpp"
#include "ext/macros.hpp"
#include "ext/macros/property.hpp"


export module apis.permissions.permission_status;
import apis.dom.event_target;

import apis.permissions.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(permissions, permission_status)
        : public dom::event_target
{
public constructors:
    permission_status();
    permission_status(detail::permissions_descriptor_t&& permission_descriptor);

private js_properties:
    DEFINE_GETTER(state, detail::permission_state_t);
    DEFINE_GETTER(name, ext::string_view);
};
