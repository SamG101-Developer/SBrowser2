module;
#include "ext/macros.hpp"
#include <function2/function2.hpp>


export module apis.remote_playback.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(remote_playback)
{
    enum class remote_playback_state_t {CONNECTING, CONNECTED, DISCONNECTED};

    using remote_playback_availability_callback_t = ext::function<void(ext::boolean available)>;
}
