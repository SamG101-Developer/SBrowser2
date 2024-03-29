module;
#include "ext/macros.hpp"


export module apis.web_audio.channel_merger_node;

import apis.web_audio.audio_node;

import ext.any;
import ext.map;
import ext.string;
import ext.tuple;

import js.env.module_type;

namespace web_audio {class base_audio_context;}


DEFINE_PUBLIC_CLASS(web_audio, channel_merger_node)
        : public web_audio::audio_node
{
public typedefs:
    using channel_merger_options_t = ext::map<ext::string, ext::any>;

public constructors:
    channel_merger_node(base_audio_context* context, channel_merger_options_t&& options = {});
    DOM_CTORS(channel_merger_node);
    MAKE_PIMPL(channel_merger_node);
    MAKE_V8_AVAILABLE(WINDOW);
};
