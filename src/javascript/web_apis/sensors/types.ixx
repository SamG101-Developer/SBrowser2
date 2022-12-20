module;
#include "ext/macros/pimpl.hpp"
#include <memory>
#include <function2/function2.hpp>
#include <QtSensors/QSensor>


export module apis.sensors.types;
import ext.any;
import ext.boolean;
import ext.functional;
import ext.map;
import ext.memory;
import ext.set;
import ext.string;


DEFINE_FWD_DECL_NAMESPACE(sensors)
{
    class sensor;
    class sensor_error_event;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(sensors)
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
    using mock_sensor_t = ext::map<ext::string, ext::any>;
    using mock_sensor_configuration_t = ext::map<ext::string, ext::any>;
    using mock_sensor_reading_values_t = ext::map<ext::string, ext::any>;
}


struct sensors::detail::platform_sensor_t
{
    ext::set<sensor*> activated_sensor_objects;
    ext::map<ext::string, ext::any> latest_reading_map;
    std::observer_ptr<sensor_type_t> sensor_type;
    std::unique_ptr<QSensor> qt_sensor;

    auto set_requested_sampling_frequency(int frequency) -> void;
    auto requested_sampling_frequency() const -> int;
    auto sampling_frequency() const -> int;
    auto reporting_frequency() const -> int;
    auto optimal_sampling_frequency() const -> int;
};


struct sensors::detail::sensor_type_t
{
    ext::set<platform_sensor_t*> associated_sensors;
    auto default_sensor() -> std::unique_ptr<platform_sensor_t>;
    ext::set<ext::string> sensor_permission_names;

    ext::set<permissions_policy::detail::feature_t> sensor_feature_names;

    ext::unique_function<void()> permission_revocation_algorithm;
    ext::unique_function<ext::boolean()> permission_request_algorithm;
    ext::unique_function<ext::boolean(const sensor_reading_t&, const sensor_reading_t&)> threshold_check_algorithm;
    ext::unique_function<sensor_reading_t(const sensor_reading_t&)> reading_quantization_algorithm;

    // Not on spec:
    ext::string type;
    std::unique_ptr<platform_sensor_t> platform_sensor;
};
