module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.device_memory.navigator_device_memory;
import apis.dom_object;

import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(device_memory, navigator_device_memory)
        : public virtual dom_object
{
private constructors:
    navigator_device_memory();
    MAKE_PIMPL(navigator_device_memory);
    MAKE_V8_AVAILABLE(WINDOW | WORKER | SECURE);

private js_properties:
    DEFINE_GETTER(device_memory, ext::number<double>);
};
