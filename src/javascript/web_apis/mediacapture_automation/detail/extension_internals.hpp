#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_AUTOMATION_DETAIL_EXTENSION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_AUTOMATION_DETAIL_EXTENSION_INTERNALS_HPP

#include "ext/optional.hpp"
#include "ext/set.hpp"
#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(mediacapture_automation)

namespace mediacapture::detail
{
    auto set_capture_prompt_result(
            mock_capture_prompt_result_configuration_t&& val)
            -> void;

    auto get_capture_prompt_result()
            -> ext::optional<mock_capture_prompt_result_configuration_t>;

    auto add_mock_camera(
            mock_camera_configuration_t&& configuration)
            -> ext::optional<ext::string>;

    auto delete_mock_camera(
            mock_camera_configuration_t&& configuration)
            -> ext::optional<ext::string>;

    auto add_mock_microphone(
            mock_microphone_configuration_t&& configuration)
            -> ext::optional<ext::string>;

    auto delete_mock_microphone(
            mock_microphone_configuration_t&& configuration)
            -> ext::optional<ext::string>;

    auto set_default_mock_microphone_device(
            mock_microphone_configuration_t&& configuration)
            -> ext::optional<ext::string>;

    auto reset_mock_capture_devices()
            -> void;

    auto get_mock_capture_devices()
            -> ext::optional<ext::set<detail::mock_capture_device_configuration_t>>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_AUTOMATION_DETAIL_EXTENSION_INTERNALS_HPP
