module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"


export module apis.permissions.permissions;
import apis.dom_object;

import apis.permissions.types;
import ext.core;
import ext.js;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(permissions, permissions)
        : virtual public dom_object
{
public constructors:
    permissions();
    MAKE_PIMPL(permissions);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);

private js_properties:
    auto query(detail::permission_descriptor_t&& permission_descriptor) -> ext::promise<std::unique_ptr<permission_status>>;
};
