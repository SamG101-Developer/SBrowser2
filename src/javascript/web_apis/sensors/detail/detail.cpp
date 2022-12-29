module;
#include "ext/macros/custom_operator.hpp"
#include "ext/macros/language_shorthand.hpp"
#include <range/v3/algorithm/fold.hpp>
#include <range/v3/algorithm/remove.hpp>
#include <range/v3/view/for_each.hpp>
#include <tl/optional.hpp>
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
import ext.string;
import ext.optional;


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
    // Get the platform sensor, and add the 'sensor_instance' to the activated sensors set. Set the sensor settings of
    // the platform sensor, and queue a task to 'notify_activated_state(...)' with the sensor instance.
    decltype(auto) platform_sensor = *sensor_instance->d_func()->sensor->platform_sensor;
    platform_sensor.activated_sensor_objects.emplace(sensor_instance);
    set_sensor_settings(platform_sensor);
    dom::detail::queue_task(&notify_activated_state, sensor_instance);
}


auto sensors::detail::deactivate_sensor_object(sensor* sensor_instance) -> void
{
    // TODO : sensor queue
    decltype(auto) platform_sensor = *sensor_instance->d_func()->platform_sensor;
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
        platform_sensor.set_requested_sampling_frequency(0);
        platform_sensor.latest_reading_map | ranges::views::for_each([](auto&& p) {p.second = nullptr;});
        // TODO
        return;
    }

    platform_sensor.set_requested_sampling_frequency(platform_sensor.optimal_sampling_frequency());
}


auto sensors::detail::update_latest_reading(const platform_sensor_t& platform_sensor, const sensor_reading_t& reading) -> void
{
    decltype(auto) type = *platform_sensor.sensor_type;
    if (!type.threshold_check_algorithm.empty())
    {
        auto result = type.threshold_check_algorithm(reading, platform_sensor.latest_reading_map);
        return_if (!result);
    }

    platform_sensor.latest_reading_map | ranges::view::for_each(
            [&platform_sensor, &reading](auto&& pair) mutable
            {platform_sensor.latest_reading_map[pair.first] = reading[pair.first];});

    _GO [&platform_sensor]
    {
        platform_sensor.activated_sensor_objects | ranges::views::for_each(ext::bind_front(report_latest_reading_updated, s));
    };
}


auto sensors::detail::find_reporting_frequency_of_sensor_object(sensor* sensor_instance) -> ext::number<double>
{
    auto f = sensor_instance->d_func()->frequency;
    // TODO : cap f
    return f;
}


auto sensors::detail::report_latest_reading_updated(sensor* sensor_instance) -> void
{
    return_if (sensor_instance->d_func()->pending_reading_notification);
    sensor_instance->d_func()->pending_reading_notification = true;

    auto last_reported_timestamp = sensor_instance->d_func()->last_event_fired_at;
    if (!last_reported_timestamp)
        return dom::detail::queue_task(html::detail::task_sources::sensors, &notify_new_reading, sensor_instance);

    auto reporting_frequency = find_reporting_frequency_of_sensor_object(sensor_instance);
    if (!reporting_frequency)
        return dom::detail::queue_task(html::detail::task_sources::sensors, &notify_new_reading, sensor_instance);

    auto reporting_interval = 1 / reporting_frequency;
    auto timestamp_delta = sensor_instance->d_func()->platform_sensor->latest_reading_map[u"timestamp"].to<int>();
    if (timestamp_delta > reporting_interval)
        return dom::detail::queue_task(html::detail::task_sources::sensors, &notify_new_reading, sensor_instance);

    auto defer_update_time = reporting_interval - timestamp_delta;
    html::detail::spin_event_loop(defer_event_time);

    if (sensor_instance->d_func()->pending_reading_notification)
        return dom::detail::queue_task(html::detail::task_sources::sensors, &notify_new_reading, sensor_instance);
}


auto sensors::detail::notify_new_reading(sensor* sensor_instance) -> void
{
    sensor_instance->d_func()->pending_reading_notification = false;
    sensor_instance->d_func()->last_event_fired_at = sensor_instance->d_func()->sensor->platform_sensor->lastest_reading_map[u"timestamp"].to<int>();
    sensor_instance->d_func()->fire_event(u"reading");
}


auto sensors::detail::notify_activated_state(sensor* sensor_instance) -> void
{
    sensor_instance->d_func()->state = ACTIVATED;
    sensor_instance->d_func()->fire_event(u"activate");
    if (sensor_instance->d_func()->platform_sensor->latest_reading_map[u"timestamp"].to<int>())
        dom::detail::queue_task(html::detail::task_sources::sensors, &notify_new_reading, sensor_instance);
}


auto sensors::detail::notify_error(sensor* sensor_instance, dom::dom_exception* error) -> void
{
    sensor_instance->d_func()->state = IDLE;
    sensor_instance->d_func()->fire_event<sensor_error_event>(u"error", {{"error", error}});
}


auto sensors::detail::get_value_from_latest_reading(const sensor* sensor_instance, ext::string&& name) -> ext::optional<sensor_reading_t>
{
    return_if (!sensor_instance->d_func()->state == ACTIVATED) ext::nullopt;

    decltype(auto) readings = sensor_instance->d_func()->platform_sensor->latest_reading_map;
    decltype(auto) type = *sensor_instance->d_func()->platform_sensor->sensor_type;
    if (!type.reading_quantization_algorithm.empty())
        readings = type.reading_quantization_algorithm(std::move(readings));

    // TODO : coordinate system
    return readings[std::move(name)];
}

