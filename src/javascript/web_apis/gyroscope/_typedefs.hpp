#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GYROSCOPE__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GYROSCOPE__TYPEDEFS_HPP






namespace gyroscope::detail
{
    enum class gyroscope_local_coordinate_system_t {DEVICE, SCREEN};

    using gyroscope_sensor_options_t = ext::map<ext::string, ext::any>;
    using gyroscope_reading_values_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GYROSCOPE__TYPEDEFS_HPP
