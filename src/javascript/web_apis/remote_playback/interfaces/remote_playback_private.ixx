module;
#include "ext/macros.hpp"


export module apis.remote_playback.remove_playback:p;
import apis.dom.event_target;

import apis.remote_playback.types;


DEFINE_PRIVATE_CLASS(remote_playback, remote_playback)
        : dom::event_target_private
{
public:
    MAKE_QIMPL(remote_playback);

public:
    ext::set<ext::tuple<ext::number<long>, detail::remote_playback_availability_callback_t>> availability_callbacks;
};
