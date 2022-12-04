#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_AUTOMATION__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_AUTOMATION__TYPEDEFS_HPP





namespace mediacapture::detail
{
    enum class mock_capture_prompt_result_t {GRANTED, DENIED};

    using mock_capture_prompt_result_configuration_t = ext::map<ext::string, ext::any>;
    using mock_capture_device_configuration_t = ext::map<ext::string, ext::any>;
    using mock_camera_configuration_t = ext::map<ext::string, ext::any>;
    using mock_microphone_configuration_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_AUTOMATION__TYPEDEFS_HPP
