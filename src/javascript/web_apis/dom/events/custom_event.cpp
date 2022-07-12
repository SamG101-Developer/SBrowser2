#include "custom_event.hpp"


dom::events::custom_event::custom_event(
        ext::string_view event_type,
        ext::string_any_map_view event_init)

        : event(event_type, event_init)
        , detail(event_init.at("detail").value_to_or<ext::string>(""))
{
    // create a custom event
}


auto dom::events::custom_event::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<custom_event>{isolate}
            .ctor<const ext::string&, const ext::string_any_map&>()
            .inherit<event>()
            .var("detail", &custom_event::detail, true)
            .auto_wrap_objects();
}
