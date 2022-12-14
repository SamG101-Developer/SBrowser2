module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.web_audio.offline_audio_context;
import apis.web_audio.base_audio_context;

import ext.any;
import ext.map;
import ext.promise;
import ext.number;
import ext.string;
import ext.tuple;

import js.env.module_type;

namespace web_audio {class audio_buffer;}


DEFINE_PUBLIC_CLASS(web_audio, offline_audio_context)
        : public web_audio::base_audio_context
{
public typedefs:
    using offline_audio_context_options_t = ext::map<ext::string, ext::any>;

public constructors:
    offline_audio_context(offline_audio_context_options_t&& context_options);
    offline_audio_context(ext::number<long> number_of_channels, ext::number<ulong> length, ext::number<float> sample_rate);
    MAKE_PIMPL(offline_audio_context);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto start_rendering() -> ext::promise<std::unique_ptr<audio_buffer>>;
    auto resume() -> ext::promise<void>;
    auto suspend() -> ext::promise<void>;

public js_properties:
    DEFINE_GETTER(length, ext::number<ulong>);
};
