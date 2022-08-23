#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_DETAIL_SENSOR_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_DETAIL_SENSOR_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/functional.hpp"
#include "ext/optional.hpp"
#include "ext/set.hpp"
#include "ext/string.hpp"
#include "ext/variant.hpp"
#include USE_INNER_TYPES(permissions)
#include USE_INNER_TYPES(permissions_policy)
#include USE_INNER_TYPES(sensors)

namespace ambient_light_sensor {class ambient_light_sensor;}
namespace dom::other {class dom_exception;}
namespace sensors {class sensor;}


namespace sensors::detail
{
    auto initialize_sensor_object(
            sensor* sensor_instance,
            sensor_options_t&& options)
            -> void;

    auto check_sensor_policy_controlled_features(
            sensor_type_t sensor_type)
            -> ext::boolean;

    auto connect_to_sensor(
            sensor* sensor_instance)
            -> ext::boolean;

    auto activate_sensor_object(
            sensor* sensor_instance)
            -> ext::boolean;

    auto deactivate_sensor_object(
            sensor* sensor_instance)
            -> void;

    auto revoke_sensor_permissions(
            const platform_sensor_t& sensor)
            -> void;

    auto set_sensor_settings(
            const platform_sensor_t& sensor)
            -> void;

    auto update_sensor_reading(
            const platform_sensor_t& sensor,
            const sensor_reading_t& reading)
            -> void;

    auto find_reporting_frequency_of_sensor_object(
            sensor* sensor_instance)
            -> ext::number<double>;

    auto report_latest_reading_updated(
            sensor* sensor_instance)
            -> void;

    auto notify_new_reading(
            sensor* sensor_instance)
            -> void;

    auto notify_error(
            sensor* sensor_instance,
            dom::other::dom_exception* error)
            -> void;

    auto get_value_from_latest_reading(
            sensor* sensor_instance,
            ext::string&& name)
            -> ext::optional<sensor_reading_t>;

    auto request_sensor_access(
            sensor* sensor_instance)
            -> permissions::detail::permission_state_t;

    auto create_mock_sensor()
            -> void;

    auto get_mock_sensor()
            -> void;

    auto update_mock_sensor_reading()
            -> void;

    auto delete_mock_sensor()
            -> void;

    auto reading_quantization_algorithm(
            sensor* generic_sensor)
            -> sensor_reading_t;

    auto reading_quantization_algorithm(
            ambient_light_sensor::ambient_light_sensor* ambient_light_sensor)
            -> sensor_reading_t;
};


struct sensors::detail::sensor_type_t
{
    // using extension_sensor_interfaces = ext::variant<Args...>;

    ext::set<sensor_type_t*> associated_sensors;
    std::unique_ptr<sensor_type_t> default_sensor;
    ext::set<ext::string> sensor_permission_names;

    ext::set<permissions_policy::detail::feature_t> sensor_feature_names;

    ext::function<ext::boolean()> permission_request_algorithm;
    ext::function<ext::boolean(const sensor_reading_t&, const sensor_reading_t&)> threshold_check_algorithm;
    ext::function<sensor_reading_t(const sensor_reading_t&)> reading_quantization_algorithm;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_DETAIL_SENSOR_INTERNALS_HPP
