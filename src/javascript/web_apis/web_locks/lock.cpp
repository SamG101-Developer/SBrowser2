#include "lock.hpp"
#include "lock_private.hpp"

#include "web_locks/detail/lock_internals.hpp"


auto web_locks::lock::get_name() const -> ext::view_of_t<detail::resource_name_t>
{
    ACCESS_PIMPL(const lock);
    return d->lock->name;
}


auto web_locks::lock::get_mode() const -> detail::lock_mode_t
{
    ACCESS_PIMPL(const lock);
    return d->lock->mode;
}


auto web_locks::lock::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("name", &lock::get_name)
        .property("mode", &lock::get_mode)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
