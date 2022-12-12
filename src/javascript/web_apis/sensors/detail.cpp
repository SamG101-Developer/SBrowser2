module;
#include <range/v3/algorithm/fold.hpp>


module apis.sensors.detail;
import apis.sensors.types;
import apis.sensors.sensor;
import apis.sensors.sensor_private;

import ext.boolean;
import ext.functional;
import ext.number;


auto sensors::detail::initialize_sensor_object(sensors::sensor* sensor_instance, sensor_options_t&& options) -> void
{
    sensor_instance->d_func()->frequency = options[u"frequency"].to<ext::number<double>>();
}


auto sensors::detail::check_sensor_policy_controlled_features(const sensor_type_t& sensor_type) -> ext::boolean
{
    auto feature_names = sensor_type.sensor_feature_names;
    return ranges::views::fold_left(feature_names | dom::detail::active_document()->d_func()->allowed_to_use(feature_name), ext::ops::and_);
}


sensors::detail::connect
