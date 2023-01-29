module;
#include "ext/macros.hpp"


export module apis.remote_playback.detail;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(remote_playback)
{
    auto monitor_list_of_available_remote_playback_devices() -> void;
    auto establish_connection_with_remote_playback_device() -> void;
    auto disconnect_from_remote_playback_device() -> void;
    auto disable_remote_playback() -> void;
};
