#include "device_orientation_event.hpp"
#include "device_orientation_event_private.hpp"

#include "dom/events/event.hpp"


device_orientation::device_orientation_event::device_orientation_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL(device_orientation_event);
    ACCESS_PIMPL(device_orientation_event);

    d->alpha = event_init["alpha"].try_to<decltype(d->alpha)>();
    d->beta  = event_init["beta" ].try_to<decltype(d->beta )>();
    d->gamma = event_init["gamma"].try_to<decltype(d->gamma)>();
}


auto device_orientation::device_orientation_event::request_permission()
        -> ext::promise<detail::permission_state_t>
{
    ext::promise<detail::permission_state_t> promise;
    // TODO
}


auto device_orientation::device_orientation_event::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<device_orientation_event>{isolate}
        .ctor<ext::string, ext::map<ext::string, ext::any>>()
        .inherit<dom::events::event>()
        .property("alpha", &device_orientation_event::get_alpha)
        .property("beta", &device_orientation_event::get_beta)
        .property("gamma", &device_orientation_event::get_gamma)
        .property("absolute", &device_orientation_event::get_absolute)
        .auto_wrap_objects();

    return std::move(conversion);
}
