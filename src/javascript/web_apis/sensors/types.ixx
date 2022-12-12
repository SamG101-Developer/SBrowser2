module;
#include <memory>
#include <function2/function2.hpp>


export module apis.sensors.types;

import ext.any;
import ext.boolean;
import ext.functional;
import ext.map;
import ext.set;
import ext.string;


export namespace sensors::detail
{
    struct platform_sensor_t;
    struct device_sensor_t;
    struct sensor_type_t;

    enum class state_t {IDLE, ACTIVATING, ACTIVATED};
    enum class mock_sensor_type_t {
        AMBIENT_LIGHT, ACCELEROMETER, LINEAR_ACCELERATION, GRAVITY, GYROSCOPE, MAGNETOMETER, UNCALIBRATED_MAGNETOMETER,
        ABSOLUTE_ORIENTATION, RELATIVE_ORIENTATION, GEOLOCATION, PROXIMITY};
    enum class coordinate_system_t {DEVICE_COORDINATE_SYSTEM, SCREEN_COORDINATE_SYSTEM};

    using sensor_reading_t = ext::map<ext::string, ext::any>;
    using sensor_options_t = ext::map<ext::string, ext::any>;
    using mock_sensor_t = ext::map<ext::string, ext::any>;
    using mock_sensor_configuration_t = ext::map<ext::string, ext::any>;
    using mock_sensor_reading_values_t = ext::map<ext::string, ext::any>;
}


struct sensors::detail::sensor_type_t
{
    // using extension_sensor_interfaces = ext::variant<Args...>;

    ext::set<sensor_type_t*> associated_sensors;
    std::shared_ptr<sensor_type_t> default_sensor;
    ext::set<ext::string> sensor_permission_names;

    ext::set<permissions_policy::detail::feature_t> sensor_feature_names;

    ext::unique_function<ext::boolean()> permission_request_algorithm;
    ext::unique_function<ext::boolean(const sensor_reading_t&, const sensor_reading_t&)> threshold_check_algorithm;
    ext::unique_function<sensor_reading_t(const sensor_reading_t&)> reading_quantization_algorithm;
};
