module;
#include "ext/macros/extended_attributes.hpp"
#include "ext/macros/os.hpp"
#include "ext/macros/pimpl.hpp"
#include <hwinfo/ram.h>


export module apis.device_memory.navigator_device_memory_private;
import apis._.dom_object_private;

import ext.number;


DEFINE_PRIVATE_CLASS(device_memory, navigator_device_memory)
        : virtual dom_object_private
{
    MAKE_QIMPL(navigator_device_memory);

    _EXT_NODISCARD auto device_memory() const -> ext::number<double>;
};
