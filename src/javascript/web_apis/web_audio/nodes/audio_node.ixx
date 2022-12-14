module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/constructors.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.web_audio.audio_node;
import apis.dom.event_target;

import ext.tuple;

import js.env.module_type;

namespace web_audio {class audio_param;}
namespace web_audio {class base_audio_context;}


DEFINE_PUBLIC_CLASS(web_audio, audio_node)
        : public dom::event_target
{
public constructors:
    DOM_CTORS(audio_node);
    MAKE_PIMPL(audio_node);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto connect(audio_node* destination, ext::number<ulong> output = 0, ext::number<ulong> input = 0) -> std::unique_ptr<audio_node>;
    auto connect(audio_param* destination_param, ext::number<ulong> output = 0) -> void;

    auto disconnect(ext::number<ulong> output = 0) -> void;
    auto disconnect(audio_node* destination, ext::number<ulong> output = 0, ext::number<ulong> input = 0) -> void;
    auto disconnect(audio_param* destination_param, ext::number<ulong> output = 0) -> void;

public js_properties:
    DEFINE_GETTER(context, base_audio_context*);
    DEFINE_GETTER(number_of_inputs, ext::number<ulong>);
    DEFINE_GETTER(number_of_outputs, ext::number<ulong>);
    DEFINE_GETTER(channel_count, ext::number<ulong>);
    DEFINE_GETTER(channel_count_mode, detail::channel_count_mode_t);
    DEFINE_GETTER(channel_interpretation, detail::channel_interpretation_t);
};
