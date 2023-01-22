#include "body.ixx"
#include "body_private.ixx"

#include "fetch/detail/body_internals.hpp"
#include "streams/detail/readable_abstract_operations_internals.hpp"


auto fetch::mixins::body::get_body() const -> streams::readable::readable_stream*
{
    ACCESS_PIMPL(const body);
    return d->body() ? d->body()->stream.get() : nullptr;
}


auto fetch::mixins::body::get_body_used() const -> ext::boolean
{
    ACCESS_PIMPL(const body);
    return d->body() && streams::detail::is_disturbed(d->body()->stream.get());
}


auto fetch::mixins::body::_to_v8(js::env::module_t E, v8::Isolate* isolate) -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .function("arrayBuffer", &body::array_buffer)
        .function("blob", &body::blob)
        .function("formData", &body::form_data)
        .function("json", &body::json)
        .function("text", &body::text)
        .property("body", &body::get_body)
        .property("bodyUsed", &body::get_body_used)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
