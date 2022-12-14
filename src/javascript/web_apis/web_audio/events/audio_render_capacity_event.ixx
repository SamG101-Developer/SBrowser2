module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.web_audio.audio_render_capacity_event;
import apis.dom.event;

import ext.any;
import ext.map;
import ext.string;
import ext.tuple;

import js.env.module_type;


DEFINE_PUBLIC_CLASS(web_audio, audio_render_capacity_event)
        : public dom::event
{
public typedefs:
    using audio_render_capacity_event_init_t = ext::map<ext::string, ext::any>;

public constructors:
    audio_render_capacity_event(ext::string&& event_type, audio_render_capacity_event_init_t&& event_init);
    MAKE_PIMPL(audio_render_capacity_event);
    MAKE_V8_AVAILABLE(WINDOW);

public js_properties:
    DEFINE_GETTER(timestamp, ext::number<double>);
    DEFINE_GETTER(average_load, ext::number<double>);
    DEFINE_GETTER(peak_load, ext::number<double>);
    DEFINE_GETTER(underrun_ratio, ext::number<double>);
};
