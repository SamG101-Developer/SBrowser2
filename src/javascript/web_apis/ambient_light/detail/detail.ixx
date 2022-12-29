module;
#include "ext/macros/macros.hpp"
#include <memory>


export module apis.ambient_light.detail;

import apis.ambient_light.types;
import apis.sensors.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(ambient_light)
{
    ext::number<int> illuminance_rounding_multiple = 1;
    ext::number<int> illuminance_threshold_value = 1;

    /* [6.1] */ auto construct_ambient_light_sensor_object(ambient_light_sensor* sensor, ext::map<ext::string, ext::any>&& options) -> void;
    /* [6.2] */ auto ambient_light_threshold_check_algorithm(const sensors::detail::sensor_reading_t& new_reading, const sensors::detail::sensor_reading_t& latest_reading) -> ext::boolean;
    /* [6.3] */ auto ambient_light_reading_quantization_algorithm(const sensors::detail::sensor_reading_t& reading) -> sensors::detail::sensor_reading_t;
};
