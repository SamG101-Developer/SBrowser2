#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_MEMORY_MIXINS_NAVIGATOR_DEVICE_MEMORY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_MEMORY_MIXINS_NAVIGATOR_DEVICE_MEMORY_HPP

#include "dom_object.hpp"
namespace device_memory::mixins {class navigator_device_memory;}


class device_memory::mixins::navigator_device_memory
        : public virtual dom_object
{
private constructors:
    navigator_device_memory() = default;
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(device_memory, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_MEMORY_MIXINS_NAVIGATOR_DEVICE_MEMORY_HPP
