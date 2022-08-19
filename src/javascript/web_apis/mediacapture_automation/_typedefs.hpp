#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_AUTOMATION__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_AUTOMATION__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"

namespace mediacapture::detail
{
    using mock_capture_prompt_result_configuration_t = ext::map<ext::string, ext::any>;
    using mock_capture_device_configuration_t = ext::map<ext::string, ext::any>;
    using mock_camera_configuration_t = ext::map<ext::string, ext::any>;
    using mock_microphone_configuration_t = ext::map<ext::string, ext::any>;

    enum class mock_capture_prompt_result_t {GRANTED, DENIED};
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_AUTOMATION__TYPEDEFS_HPP
