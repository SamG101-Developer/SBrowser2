#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_IMAGE__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_IMAGE__TYPEDEFS_HPP





namespace mediacapture::detail
{
    enum class red_eye_reduction_t {NEVER, ALWAYS, CONTROLLABLE};
    enum class fill_light_mode_t {AUTO, OFF, FLASH};
    enum class metering_mode_t {NONE, MANUAL, SINGLE_SHOT, CONTINUOUS};

    using photo_capabilities_t = ext::map<ext::string, ext::any>;
    using photo_settings_t = ext::map<ext::string, ext::any>;
    using media_settings_range_t = ext::map<ext::string, ext::any>;
    using constrain_point_2d_parameters_t = ext::map<ext::string, ext::any>;
    using constrain_point_2d_t = ext::map<ext::string, ext::any>;
    using point_2d_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_IMAGE__TYPEDEFS_HPP
