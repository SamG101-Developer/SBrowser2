module;
#include "ext/macros.hpp"


export module apis.web_audio.offline_audio_completion_event;
import apis.dom.event;

import ext.any;
import ext.map;
import ext.string;
import ext.tuple;

import js.env.module_type;

namespace web_audio {class audio_buffer;}


DEFINE_PUBLIC_CLASS(web_audio, offline_audio_completion_event)
        : public dom::event
{
public typedefs:
    using offline_audio_completion_event_init_t = ext::map<ext::string, ext::any>;

public constructors:
    offline_audio_completion_event(ext::string&& event_type, offline_audio_completion_event_init_t&& event_init);
    MAKE_PIMPL(offline_audio_completion_event);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(rendered_buffer, audio_buffer*);
};
