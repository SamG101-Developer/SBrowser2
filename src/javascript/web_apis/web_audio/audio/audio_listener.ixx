module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.web_audio.audio_listener;
import apis._.dom_object;

import ext.number;
import ext.tuple;

import js.env.module_type;

namespace web_audio {class audio_param;}


DEFINE_PUBLIC_CLASS(web_audio, audio_listener)
        : public dom_object
{
public constructors:
    audio_listener();
    MAKE_PIMPL(audio_listener);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto set_position(ext::number<float> x, ext::number<float> y, ext::number<float> z) -> void;
    auto set_orientation(ext::number<float> x, ext::number<float> y, ext::number<float> z, ext::number<float> up_x, ext::number<float> up_y, ext::number<float> up_z) -> void;

public js_properties:
    DEFINE_GETTER(position_x, audio_param*);
    DEFINE_GETTER(position_y, audio_param*);
    DEFINE_GETTER(position_z, audio_param*);
    DEFINE_GETTER(forward_x, audio_param*);
    DEFINE_GETTER(forward_y, audio_param*);
    DEFINE_GETTER(forward_z, audio_param*);
    DEFINE_GETTER(up_x, audio_param*);
    DEFINE_GETTER(up_y, audio_param*);
    DEFINE_GETTER(up_z, audio_param*);
};
