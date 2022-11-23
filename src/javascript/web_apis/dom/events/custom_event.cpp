#include "custom_event.hpp"
#include "custom_event_private.hpp"


dom::events::custom_event::custom_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : event(std::move(event_type), std::move(event_init))
{
    INIT_PIMPL(custom_event);
    ACCESS_PIMPL(custom_event);
    d->detail = 0;
}


auto dom::events::custom_event::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<event>()
        .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
        .property("detail", &custom_event::get_detail)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
