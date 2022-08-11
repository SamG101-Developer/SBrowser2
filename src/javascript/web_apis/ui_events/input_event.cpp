#include "input_event.hpp"

#include "ext/boolean.hpp"


ui_events::input_event::input_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : ui_event(std::move(event_type), std::move(event_init))
        , data{event_init.try_emplace("data", "").first->second.to<ext::string>()}
        , input_type{event_init.try_emplace("inputType", "").first->second.to<ext::string>()}
        , is_composing{event_init.try_emplace("isComposing", ext::boolean::FALSE_()).first->second.to<ext::boolean>()}
{}


auto ui_events::input_event::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<input_event>{isolate}
            .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
            .inherit<ui_event>()
            .var("data", &input_event::data, true)
            .var("inputType", &input_event::input_type, true)
            .var("isComposing", &input_event::is_composing, true)
            .auto_wrap_objects();
}
