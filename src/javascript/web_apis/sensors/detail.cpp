module;
#include <range/v3/algorithm/fold.hpp>
#include <QtSensors/QSensor>
#include <QtCore/QString>


module apis.sensors.detail;
import apis.sensors.types;
import apis.sensors.sensor;
import apis.sensors.sensor_private;

import apis.dom.detail;
import apis.dom.types;
import apis.dom.dom_exception;

import ext.boolean;
import ext.functional;
import ext.number;


auto sensors::detail::initialize_sensor_object(sensor* sensor_instance, sensor_options_t&& options) -> void
{
    sensor_instance->d_func()->frequency = options[u"frequency"].to<ext::number<double>>();
}


auto sensors::detail::check_sensor_policy_controlled_features(const sensor_type_t& sensor_type) -> ext::boolean
{
    auto feature_names = sensor_type.sensor_feature_names;
    return ranges::views::fold_left(feature_names | dom::detail::active_document()->d_func()->allowed_to_use(feature_name), ext::ops::and_);
}


auto sensors::detail::connect_to_sensor(sensor* sensor_instance) -> ext::boolean
{
    // Get the sensor type ie "QAccelerometer" from the Sensor's sensor_type, and convert it to a QString. Create a
    // platorm sensor with the type.
    auto type = QString::fromStdU16String(sensor_instance->d_func()->sensor->type);
    auto qt_sensor = std::make_unique<QSensor>(type);

    // If there is only 1 sensor available for this type, then set the Sensor's sensor_type's platform sensor to the
    // 'platform_sensor' that has just been created. Return true for a successful operation.
    if (!qt_sensor->type().empty()) // TODO : 1 Sensor available
    {
        sensor_instance->d_func()->sensor->platform_sensor->qt_sensor = std::move(qt_sensor);
        return true;
    }

    // If there are multiple sensors available for this type, then set the Sensor's sensor_type's platform sensor to the
    // default sensor type for the 'type'. Return true for a successful operation.
    else
    {
        auto default_sensor = std::make_unique<QSensor>(QSensor::defaultSensorForType(type));
        sensor_instance->d_func()->sensor->platform_sensor->qt_sensor = default_sensor;
        return true;
    }

    //  Return false for a failed operation.
    return false;
}


auto sensors::detail::activate_sensor_object(sensor* sensor_instance) -> ext::boolean
{
    decltype(auto) platform_sensor = *sensor_instance->d_func()->sensor->platform_sensor;
    platform_sensor.activated_sensor_objects.emplace(sensor_instance);
    set_sensor_settings(platform_sensor);
    dom::detail::queue_task(&notify_activated_state, sensor_instance);
}


auto sensors::detail::deactivate_sensor_object(sensor* sensor_instance) -> void
{
    // TODO : sensor queue
    decltype(auto) platform_sensor = *sensor_instance->d_func()->sensor->platform_sensor;
    if (platform_sensor.activated_sensor_objects.contains(sensor_instance))
    {
        platform_sensor.activated_sensor_objects |= ranges::algorithms::remove(platform_sensor);
        set_sensor_settings(platform_sensor);
        sensor_instance->d_func()->pending_reading_notification = false;
        sensor_instance->d_func()->last_event_fired_at = 0;
    }
}


auto sensors::detail::revoke_sensor_permissions(const platform_sensor_t& platform_sensor) -> void
{
    using enum dom::detail::dom_exception_error_t;
    for (decltype(auto) sensor_instance: platform_sensor.activated_sensor_objects)
    {
        deactivate_sensor_object(sensor_instance);
        auto e = dom::dom_exception{"Permission revoked", NOT_ALLOWED_ERR};
        dom::detail::queue_task(&notify_error, sensor_instance, std::move(e));
    }
}


auto sensors::detail::set_sensor_settings(platform_sensor_t& platform_sensor) -> void
{
    if (platform_sensor.activated_sensor_objects.empty())
    {
        platform_sensor.set
    }
}
