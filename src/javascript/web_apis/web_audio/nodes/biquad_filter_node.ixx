module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/constructors.hpp"
#include "ext/macros/macros.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.web_audio.biquad_filter_node;
import apis.web_audio.audio_node;

import ext.any;
import ext.array_buffer;
import ext.map;
import ext.string;
import ext.tuple;

import js.env.module_type;

namespace web_audio {class base_audio_context;}
namespace web_audio {class audio_param;}


DEFINE_PUBLIC_CLASS(web_audio, biquad_filter_node)
        : public web_audio::audio_node
{
public typedefs:
    using biquad_filter_options_t = ext::map<ext::string, ext::any>;

public constructors:
    biquad_filter_node(base_audio_context* context, biquad_filter_options_t&& options = {});
    DOM_CTORS(biquad_filter_node);
    MAKE_PIMPL(biquad_filter_node);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto get_frequency_response(ext::float32_array& frequency_hz, ext::float32_array& mag_Response, ext::float32_array& phase_response) -> void;

public js_properties:
    DEFINE_GETTER(frequency, audio_param*);
    DEFINE_GETTER(detune, audio_param*);
    DEFINE_GETTER(q, audio_param*);
    DEFINE_GETTER(gain, audio_param*);
};
