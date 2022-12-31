module;
#include "ext/macros.hpp"


export module apis.device_memory.mixins.navigator_device_memory;
import apis.dom_object;


DEFINE_PUBLIC_CLASS(device_memory::mixins, navigator_device_memory)
        : public virtual dom_object
{
private constructors:
    navigator_device_memory();
    MAKE_PIMPL(navigator_device_memory);
    MAKE_V8_AVAILABLE(WINDOW | WORKER | SECURE);

private js_properties:
    DEFINE_GETTER(device_memory, ext::number<double>);
};
