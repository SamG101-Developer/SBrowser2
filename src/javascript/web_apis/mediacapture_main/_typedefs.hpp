#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN__TYPEDEFS_HPP

namespace mediacapture::detail
{
    enum class media_device_kind_t {AUDIO_INPUT, AUDIO_OUTPUT, VIDEO_INPUT};
    enum class media_stream_track_state_t {LIVE, ENDED};
    struct media_stream_track_source;
    using capabilities_t = ext::map<ext::string, ext::any>;
    using constraints_t = ext::map<ext::string, ext::any>;
    using settings_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN__TYPEDEFS_HPP
