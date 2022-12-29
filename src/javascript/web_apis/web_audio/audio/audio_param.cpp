module;
#include "ext/macros/macros.hpp"
#include "javascript/macros/expose.hpp"
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.web_audio.audio_param;
import apis.web_audio.audio_param_private;
import apis.web_audio.types;

import ext.number;
import ext.tuple;
import ext.type_traits;

import js.env.module_type;


auto web_audio::audio_param::get_value() const -> ext::number<float>
{
    ACCESS_PIMPL;
    return d->value;
}


auto web_audio::audio_param::get_automation_rate() const -> detail::automation_rate_t
{
    ACCESS_PIMPL;
    return d->automation_rate;
}


auto web_audio::audio_param::get_default_value() const -> ext::number<float>
{
    ACCESS_PIMPL;
    return d->default_value;
}


auto web_audio::audio_param::get_min_value() const -> ext::number<float>
{
    ACCESS_PIMPL;
    return d->min_value;
}


auto web_audio::audio_param::get_max_value() const -> ext::number<float>
{
    ACCESS_PIMPL;
    return d->max_value;
}


auto web_audio::audio_param::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .function("setValueAtTime", &audio_param::set_value_at_time)
        .function("linearRampToValueAtTime", &audio_param::linear_ramp_to_value_at_time)
        .function("exponentialRampToValueAtTime", &audio_param::exponential_ramp_to_value_at_time)
        .function("setTargetAtTime", &audio_param::set_target_at_time)
        .function("setValueCurveAtTime", &audio_param::set_value_curve_at_time)
        .function("cancelScheduledValues", &audio_param::cancel_scheduled_values)
        .function("cancelAndHoldAtTime", &audio_param::cancel_and_hold_at_time)
        .property("value", &audio_param::get_value, &audio_param::set_value)
        .property("automation_rate", &audio_param::get_automation_rate, &audio_param::set_automation_rate)
        .property("defaultValue", &audio_param::get_default_value)
        .property("minValue", &audio_param::get_min_value)
        .property("maxValue", &audio_param::get_max_value)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
