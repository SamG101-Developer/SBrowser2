module;
#include "ext/macros/annotations.hpp"


export module apis.web_audio.audio_listener;
import apis.dom_object;

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
