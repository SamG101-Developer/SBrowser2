module;
#include "ext/macros/annotations.hpp"
#include "ext/macros.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.web_audio.audio_param;
import apis.dom_object;
import apis.web_audio.types;

import ext.number;
import ext.tuple;
import ext.type_traits;
import ext.vector;

import js.env.module_type;


DEFINE_PUBLIC_CLASS(web_audio, audio_param)
        : virtual public dom_object
{
public constructors:
    audio_param();
    MAKE_PIMPL(audio_param);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto set_value_at_time(ext::number<float> value, ext::number<double> start_time) -> audio_param*;
    auto linear_ramp_to_value_at_time(ext::number<float> value, ext::number<double> end_time) -> audio_param*;
    auto exponential_ramp_to_value_at_time(ext::number<float> value, ext::number<double> end_time) -> audio_param*;
    auto set_target_at_time(ext::number<float> target, ext::number<double> start_time, ext::number<float> time_constant) -> audio_param*;
    auto set_value_curve_at_time(ext::vector<ext::number<float>> values, ext::number<double> start_time, ext::number<double> duration) -> audio_param*;
    auto cancel_scheduled_values(ext::number<double> cancel_time) -> audio_param*;
    auto cancel_and_hold_at_time(ext::number<double> cancel_time) -> audio_param*;

public js_properties:
    DEFINE_GETTER(value, ext::number<float>);
    DEFINE_GETTER(automation_rate, detail::automation_rate_t);
    DEFINE_GETTER(default_value, ext::number<float>);
    DEFINE_GETTER(min_value, ext::number<float>);
    DEFINE_GETTER(max_value, ext::number<float>);

    DEFINE_SETTER(value, ext::number<float>);
    DEFINE_SETTER(automation_rate, detail::automation_rate_t);
};
