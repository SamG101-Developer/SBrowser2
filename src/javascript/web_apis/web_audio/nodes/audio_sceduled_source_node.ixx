module;
#include "ext/macros.hpp"


export module apis.web_audio.audio_sceduled_source_node;
import apis.web_audio.audio_node;

import ext.number;
import ext.tuple;

import js.env.module_type;


DEFINE_PUBLIC_CLASS(web_audio, audio_sceduled_source_node)
        : public web_audio::audio_node
{
public constructors:
    DOM_CTORS(audio_sceduled_source_node);
    MAKE_PIMPL(audio_sceduled_source_node);
    MAKE_V8_AVAILABLE(WINDOW);

private js_methods:
    auto start(ext::number<double> when = 0) -> void;
    auto stop(ext::number<double> when = 0) -> void;
};
