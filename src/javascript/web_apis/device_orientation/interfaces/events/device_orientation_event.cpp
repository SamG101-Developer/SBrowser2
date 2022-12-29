module;
#include "ext/macros/macros.hpp"
#include <javascript/macros/expose.hpp>


module apis.device_orientation.device_orientation_event;
import apis.device_orientation.device_orientation_event_private;

import apis.dom.event;

import ext.core;
import ext.js;
import js.env.module_type;


device_orientation::device_orientation_event::device_orientation_event(
        ext::string&& event_type,
        device_orientation_event_init_t&& event_init)
        : dom::event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL; ACCESS_PIMPL;

    d->alpha = event_init[u"alpha"].to<double>();
    d->beta  = event_init[u"beta" ].to<double>();
    d->gamma = event_init[u"gamma"].to<double>();
}


auto device_orientation::device_orientation_event::request_permission() -> ext::promise<detail::permission_state_t>
{
    auto promise = ext::promise<detail::permission_state_t>{};
    // TODO
}


auto device_orientation::device_orientation_event::get_alpha() const -> ext::number<double>
{
    // The 'alpha' getter returns the equivalent 'alpha' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->alpha;
}


auto device_orientation::device_orientation_event::get_beta() const -> ext::number<double>
{
    // The 'beta' getter returns the equivalent 'beta' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->beta;
}


auto device_orientation::device_orientation_event::get_gamma() const -> ext::number<double>
{
    // The 'gamma' getter returns the equivalent 'gamma' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->gamma;
}


auto device_orientation::device_orientation_event::get_absolute() const -> ext::boolean
{
    // The 'absolute' getter returns the equivalent 'absolute' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->absolute;
}


auto device_orientation::device_orientation_event::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .ctor<ext::string&&, device_orientation_event_init_t&&>()
        .inherit<dom::event>()
        .property("alpha", &device_orientation_event::get_alpha)
        .property("beta", &device_orientation_event::get_beta)
        .property("gamma", &device_orientation_event::get_gamma)
        .property("absolute", &device_orientation_event::get_absolute)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
