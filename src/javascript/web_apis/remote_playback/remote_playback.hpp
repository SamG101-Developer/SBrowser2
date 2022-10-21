#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REMOTE_PLAYBACK_REMOTE_PLAYBACK_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REMOTE_PLAYBACK_REMOTE_PLAYBACK_HPP

// Inheritance Includes & This Class
#include "dom/nodes/event_target.hpp"
namespace remote_playback {class remote_playback;}
namespace remote_playback {class remote_playback_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(remote_playback)
#include "ext/promise.hpp"
#include "ext/optional.hpp"


class remote_playback::remote_playback
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(remote_playback);
    MAKE_PIMPL(remote_playback);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto watch_availability(detail::remote_playback_availability_callback&& callback) -> ext::promise<ext::number<long>>;
    auto cancel_watch_availability(ext::optional<ext::number<long>> id = ext::nullopt) -> ext::promise<void>;
    auto prompt() -> ext::promise<void>;

public js_properties:
    DEFINE_GETTER(state, detail::remote_playback_state);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REMOTE_PLAYBACK_REMOTE_PLAYBACK_HPP
