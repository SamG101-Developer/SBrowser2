module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.web_audio.audio_params;
import apis._.dom_object;

import ext.number;
import ext.tuple;
import ext.vector;

import js.env.module_type;


DEFINE_PUBLIC_CLASS(web_audio, audio_param)
        : public dom_object
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
};
