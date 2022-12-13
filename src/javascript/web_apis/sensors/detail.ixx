module;
#include <tl/optional.hpp>


export module apis.sensors.detail;
import apis.sensors.types;

import ext.boolean;
import ext.number;
import ext.optional;
import ext.string;

namespace dom {class dom_exception;}
namespace sensors {class sensor;}


export namespace sensors::detail
{
    /* [8.01] */ auto initialize_sensor_object(sensor* sensor_instance, sensor_options_t&& options) -> void;
    /* [8.02] */ auto check_sensor_policy_controlled_features(const sensor_type_t& sensor_type) -> ext::boolean;
    /* [8.03] */ auto connect_to_sensor(sensor* sensor_instance) -> ext::boolean;
    /* [8.04] */ auto activate_sensor_object(sensor* sensor_instance) -> ext::boolean;
    /* [8.05] */ auto deactivate_sensor_object(sensor* sensor_instance) -> void;
    /* [8.06] */ auto revoke_sensor_permissions(const platform_sensor_t& platform_sensor) -> void;
    /* [8.07] */ auto set_sensor_settings(platform_sensor_t& platform_sensor) -> void;
    /* [8.08] */ auto update_sensor_reading(const platform_sensor_t& platform_sensor, const sensor_reading_t& reading) -> void;
    /* [8.09] */ auto find_reporting_frequency_of_sensor_object(sensor* sensor_instance) -> ext::number<double>;
    /* [8.10] */ auto report_latest_reading_updated() -> void;
    /* [8.11] */ auto notify_new_reading() -> void;
    /* [8.12] */ auto notify_activated_state() -> void;
    /* [8.13] */ auto notify_error(dom::dom_exception* error) -> void;
    /* [8.14] */ auto get_value_from_latest_reading(ext::string&& name) -> ext::optional<sensor_reading_t>;
    /* [8.15] */ auto request_sensor_access() -> permissions::detail::permission_state_t;

    /* [9.2.1] */ auto create_mock_sensor() -> void;
    /* [9.2.2] */ auto get_mock_sensor() -> void;
    /* [9.2.3] */ auto update_mock_sensor_reading() -> void;
    /* [9.2.4] */ auto delete_mock_sensor() -> void;
}
