#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER__TYPEDEFS_HPP






namespace magnetometer::detail
{
    using magnetometer_sensor_options_t = ext::map<ext::string, ext::any>;
    using magnetometer_reading_values_t = ext::map<ext::string, ext::any>;
    using uncalibrated_magnetometer_reading_values_t = ext::map<ext::string, ext::any>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MAGNETOMETER__TYPEDEFS_HPP
