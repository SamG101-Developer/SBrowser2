#include "device_orientation_event.hpp"

#include "dom/events/event.hpp"


device_orientation::device_orientation_event::device_orientation_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event{std::move(event_type), std::move(event_init)}
        , SET_PROPERTY_FROM_OPTIONS(event_init, alpha, 0.0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, beta, 0.0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, gamma, 0.0)
{}


auto device_orientation::device_orientation_event::request_permission()
        -> std::promise<detail::permission_state_t>
{
    std::promise<detail::permission_state_t> promise;
    // TODO
}


auto device_orientation::device_orientation_event::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<device_orientation_event>{isolate}
        .ctor<ext::string, ext::map<ext::string, ext::any>>()
        .inherit<dom::events::event>()
        .var("alpha", &device_orientation_event::alpha, true)
        .var("beta", &device_orientation_event::beta, true)
        .var("gamma", &device_orientation_event::gamma, true)
        .var("absolute", &device_orientation_event::absolute, true)
        .auto_wrap_objects();
}
