module;
#include "ext/macros.hpp"
#include <tl/optional.hpp>


export module apis.remote_playback.remote_playback;
import apis.dom.event_target;
import ext.js;

import apis.remote_playback.types;


DEFINE_PUBLIC_CLASS(remote_playback, remote_playback) final
        : public dom::event_target
{
public constructors:
    DOM_CTORS(remote_playback);
    MAKE_PIMPL(remote_playback);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto watch_availability(detail::remote_playback_availability_callback_t&& callback) -> ext::promise<ext::number<long>>;
    auto cancel_watch_availability(ext::optional<ext::number<long>> id = ext::nullopt) -> ext::promise<void>;
    auto prompt() -> ext::promise<void>;

public js_properties:
    DEFINE_GETTER(state, detail::remote_playback_state);
};
