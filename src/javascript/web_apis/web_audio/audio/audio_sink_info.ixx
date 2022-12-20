module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.web_audio.audio_sink_info;
import apis.dom_object;

import apis.web_audio.types;
import ext.tuple;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(web_audio, audio_sink_info)
        : public dom_object
{
public constructors:
    audio_sink_info();
    MAKE_PIMPL(audio_sink_info);
    MAKE_V8_AVAILABLE(WINDOW);

public js_properties:
    DEFINE_GETTER(type, detail::audio_sink_type_t);
};
