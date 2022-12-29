module;
#include "ext/macros/macros.hpp"


export module apis.web_audio.base_audio_context_private;
import apis.dom.event_target_private;

import apis.web_audio.types;
import ext.vector;
import ext.promise;


DEFINE_PRIVATE_CLASS(web_audio, base_audio_context)
        : dom::event_target_private
{
public:
    MAKE_QIMPL(base_audio_context);

public:
    ext::vector<ext::promise<void>> pending_promises; // TODO <T>
    detail::audio_context_state_t rendering_thread_state;
    detail::audio_context_state_t control_thread_state;
};
