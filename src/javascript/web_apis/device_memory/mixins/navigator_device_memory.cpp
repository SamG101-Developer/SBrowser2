#include "navigator_device_memory.hpp"
#include "navigator_device_memory_private.hpp"


auto device_memory::mixins::navigator_device_memory::get_device_memory() const -> ext::number<double>
{
    // The 'device_memory' getter returns the equivalent 'device_memory' attribute value that is stored in the private
    // class. Method call becuase the value is always changing, and has to be got at the exact time the property is
    // accessed.
    ACCESS_PIMPL(const navigator_device_memory);
    return d->device_memory();

}


auto device_memory::mixins::navigator_device_memory::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("deviceMemory", &navigator_device_memory::get_device_memory)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
