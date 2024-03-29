#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD__TYPEDEFS_HPP






namespace mediacapture::detail
{
    enum class bitrate_mode_t {CONSTANT, VARIABLE};
    enum class recording_state_t {INACTIVE, RECORDING, PAUSED};

    using media_recorder_options = ext::map<ext::string, ext::any>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD__TYPEDEFS_HPP
