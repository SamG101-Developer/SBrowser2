#include "custom_event.hpp"


dom::events::custom_event::custom_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)

        : event(std::move(event_type), std::move(event_init))
        , SET_PROPERTY_FROM_OPTIONS(event_init, detail, 0)
{
    // create a custom event
}


auto dom::events::custom_event::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<custom_event>{isolate}
            .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
            .inherit<event>()
            .var("detail", &custom_event::detail, true)
            .auto_wrap_objects();
}
