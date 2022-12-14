export module apis.ambient_light.detail;

import apis.sensors.types;
import ext.any;
import ext.boolean;
import ext.number;
import ext.map;
import ext.string;

namespace ambient_light {class ambient_light_sensor;}


namespace ambient_light::detail
{
    ext::number<int> illuminance_rounding_multiple = 1;
    ext::number<int> illuminance_threshold_value = 1;

    /* [6.1] */ auto construct_ambient_light_sensor_object(ambient_light_sensor* sensor, ext::map<ext::string, ext::any>&& options) -> void;
    /* [6.2] */ auto ambient_light_threshold_check_algorithm(const sensors::detail::sensor_reading_t& new_reading, const sensors::detail::sensor_reading_t& latest_reading) -> ext::boolean;
    /* [6.3] */ auto ambient_light_reading_quantization_algorithm(const sensor::detail::sensor_reading& reading) -> std::unique_ptr<sensor::detail::sensor_reading>;
};
