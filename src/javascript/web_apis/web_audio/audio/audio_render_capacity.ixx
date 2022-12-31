module;
#include "ext/macros.hpp"


export module apis.web_audio.audio_render_capacity;
import apis.dom.event_target;

import ext.any;
import ext.map;
import ext.string;
import ext.tuple;

import js.env.module_type;


DEFINE_PUBLIC_CLASS(web_audio, audio_render_capacity)
        : public dom::event_target
{
public typedefs:
    using audio_render_capacity_options_t = ext::map<ext::string, ext::any>;

public constructors:
    audio_render_capacity();
    MAKE_PIMPL(audio_render_capacity);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto start(audio_render_capacity_options_t&& options = {}) -> void;
    auto stop() -> void;
};
