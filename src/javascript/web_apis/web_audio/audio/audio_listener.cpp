module;
#include "ext/macros.hpp"


module apis.web_audio.audio_listener;
import apis.web_audio.audio_param;
import apis.web_audio.types;

import ext.number;
import ext.tuple;

import js.env.module_type;


web_audio::audio_listener::audio_listener()
{
    INIT_PIMPL; ACCESS_PIMPL;
    using enum detail::automation_rate_t;

    d->position_x = std::make_unique<audio_param>();
    d->position_y = std::make_unique<audio_param>();
    d->position_z = std::make_unique<audio_param>();
    d->forward_x = std::make_unique<audio_param>();
    d->forward_y = std::make_unique<audio_param>();
    d->forward_z = std::make_unique<audio_param>();
    d->up_x = std::make_unique<audio_param>();
    d->up_y = std::make_unique<audio_param>();
    d->up_z = std::make_unique<audio_param>();

    d->forward_z->d_func()->default_value = -1;
    d->up_y->d_func()->default_value = 1;
}


auto web_audio::audio_listener::get_position_x() const -> audio_param*
{
    ACCESS_PIMPL;
    return d->position_x.get();
}


auto web_audio::audio_listener::get_position_y() const -> audio_param*
{
    ACCESS_PIMPL;
    return d->position_y.get();
}



auto web_audio::audio_listener::get_position_z() const -> audio_param*
{
    ACCESS_PIMPL;
    return d->position_z.get();
}


auto web_audio::audio_listener::get_forward_x() const -> audio_param*
{
    ACCESS_PIMPL;
    return d->forward_x.get();
}


auto web_audio::audio_listener::get_forward_y() const -> audio_param*
{
    ACCESS_PIMPL;
    return d->forward_y.get();
}



auto web_audio::audio_listener::get_forward_z() const -> audio_param*
{
    ACCESS_PIMPL;
    return d->forward_z.get();
}


auto web_audio::audio_listener::get_up_x() const -> audio_param*
{
    ACCESS_PIMPL;
    return d->up_x.get();
}


auto web_audio::audio_listener::get_up_y() const -> audio_param*
{
    ACCESS_PIMPL;
    return d->up_y.get();
}



auto web_audio::audio_listener::get_up_z() const -> audio_param*
{
    ACCESS_PIMPL;
    return d->up_z.get();
}


auto web_audio::audio_listener::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("positionX", &audio_listener::get_position_x)
        .property("positionY", &audio_listener::get_position_y)
        .property("positionZ", &audio_listener::get_position_z)
        .property("forwardX", &audio_listener::get_forward_x)
        .property("forwardY", &audio_listener::get_forward_y)
        .property("forwardZ", &audio_listener::get_forward_z)
        .property("upX", &audio_listener::get_up_x)
        .property("upY", &audio_listener::get_up_y)
        .property("upZ", &audio_listener::get_up_z)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}


