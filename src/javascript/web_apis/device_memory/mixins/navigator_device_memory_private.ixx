module;
#include "ext/macros/os.hpp"
#include "ext/macros.hpp"
#include <hwinfo/ram.h>


export module apis.device_memory.mixins.navigator_device_memory:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(device_memory::mixins, navigator_device_memory)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(navigator_device_memory);

public:
    _EXT_NODISCARD auto device_memory() const -> ext::number<double>;
};
