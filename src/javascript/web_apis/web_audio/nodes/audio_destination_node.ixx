module;
#include "ext/macros.hpp"


export module apis.web_audio.audio_destination_node;
import apis.web_audio.audio_node;

import ext.number;
import ext.tuple;

import js.env.module_type;


DEFINE_PUBLIC_CLASS(web_audio, audio_destination_node)
        : public web_audio::audio_node
{
public constructors:
    DOM_CTORS(audio_destination_node);
    MAKE_PIMPL(audio_destination_node);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(max_channel_count, ext::number<ulong>);
};
