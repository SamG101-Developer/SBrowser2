#include "clipboard_event.hpp"

#include "dom_object.hpp"
#include "html/dnd/data_transfer.hpp"


clipboard::clipboard_event::clipboard_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event(std::move(event_type), std::move(event_init))
        , SET_PROPERTY_FROM_OPTIONS(event_init, clipboard_data, nullptr)
{}


auto clipboard::clipboard_event::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<clipboard_event>{isolate}
        .inherit<dom::events::event>()
        .ctor<ext::string&&, ext::map<ext::string, ext::any&&>>()
        .var("clipboardData", &clipboard_event::clipboard_data, true)
        .auto_wrap_objects();

    return std::move(conversion);
}
