#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

namespace sensors::detail
{
    struct platform_sensor_t;
    struct device_sensor_t;
    struct sensor_type_t;

    enum class state_t {IDLE, ACTIVATING, ACTIVATED};
    enum class mock_sensor_type_t {
        AMBIENT_LIGHT, ACCELEROMETER, LINEAR_ACCELERATION, GRAVITY, GYROSCOPE, MAGNETOMETER, UNCALIBRATED_MAGNETOMETER,
        ABSOLUTE_ORIENTATION, RELATIVE_ORIENTATION, GEOLOCATION, PROXIMITY};

    using sensor_reading_t = ext::vector<ext::any>;
    using sensor_options_t = ext::map<ext::string, ext::any>;
    using mock_sensor_t = ext::map<ext::string, ext::any>;
    using mock_sensor_configuration_t = ext::map<ext::string, ext::any>;
    using mock_sensor_reading_values_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS__TYPEDEFS_HPP
