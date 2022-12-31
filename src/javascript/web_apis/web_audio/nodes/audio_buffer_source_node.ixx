module;
#include "ext/macros.hpp"


export module apis.web_audio.audio_buffer_source_node;
import apis.web_audio.audio_node;

import ext.any;
import ext.boolean;
import ext.map;
import ext.number;
import ext.string;
import ext.tuple;
import ext.type_traits;

import js.env.module_type;

namespace web_audio {class base_audio_context;}
namespace web_audio {class audio_buffer;}
namespace web_audio {class audio_param;}


DEFINE_PUBLIC_CLASS(web_audio, audio_buffer_source_node)
        : public web_audio::audio_node
{
public typedefs:
    using audio_buffer_source_options_t = ext::map<ext::string, ext::any>;

public constructors:
    audio_buffer_source_node(base_audio_context* context, audio_buffer_source_options_t&& options = {});
    DOM_CTORS(audio_buffer_source_node);
    MAKE_PIMPL(audio_buffer_source_node);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto start(ext::number<double> when = 0, ext::number<double> offset = 0, ext::number<double> duration = 0) -> void;

public js_properties:
    DEFINE_GETTER(buffer, audio_buffer*);
    DEFINE_GETTER(playback_rate, audio_param*);
    DEFINE_GETTER(detune, audio_param*);
    DEFINE_GETTER(loop, ext::boolean);
    DEFINE_GETTER(loop_start, ext::number<double>);
    DEFINE_GETTER(loop_end, ext::number<double>);

    DEFINE_SETTER(buffer, audio_buffer*);
    DEFINE_SETTER(loop, ext::boolean);
    DEFINE_SETTER(loop_start, ext::number<double>);
    DEFINE_SETTER(loop_end, ext::number<double>);
};
