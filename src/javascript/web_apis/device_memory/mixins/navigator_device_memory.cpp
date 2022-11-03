#include "navigator_device_memory.hpp"
#include "navigator_device_memory_private.hpp"


auto device_memory::mixins::navigator_device_memory::get_device_memory() const -> ext::number<double>
{
    ACCESS_PIMPL(const navigator_device_memory);
    return d->device_memory();

}


auto device_memory::mixins::navigator_device_memory::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<navigator_device_memory>{isolate}
        .inherit<dom_object>()
        .property("deviceMemory", &navigator_device_memory::get_device_memory)
        .auto_wrap_objects();

    return std::move(conversion);
}
