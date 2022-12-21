module;
#include "ext/macros/extended_attributes.hpp"
#include "ext/macros/os.hpp"
#include "ext/macros/pimpl.hpp"
#include <hwinfo/ram.h>


export module apis.device_memory.navigator_device_memory_private;
import apis.dom_object_private;

import ext.core;


DEFINE_PRIVATE_CLASS(device_memory, navigator_device_memory)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(navigator_device_memory);

public:
    _EXT_NODISCARD auto device_memory() const -> ext::number<double>;
};
