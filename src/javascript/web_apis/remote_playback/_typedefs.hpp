#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REMOTE_PLAYBACK__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REMOTE_PLAYBACK__TYPEDEFS_HPP

#include "ext/boolean.hpp"
#include "ext/functional.hpp"


namespace remote_playback::detail
{
    enum class remote_playback_state {CONNECTING, CONNECTED, DISCONNECTED};

    using remote_playback_availability_callback = ext::function<void(ext::boolean available)>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REMOTE_PLAYBACK__TYPEDEFS_HPP
