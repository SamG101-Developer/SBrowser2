module;
#include "ext/macros/macros.hpp"


export module apis.geolocation_sensor.detail;
import apis.geolocation_sensor.types;

import ext.core;
import ext.js;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(geolocation_sensor)
{
    auto construct_geolocation_sensor_object(geolocation_sensor* sensor, ext::map<ext::string, ext::any>&& options) -> void;
    auto resolve_geolocation_promise(geolocation_sensor* sensor, ext::promise<ext::map<ext::string, ext::any>>& promise) -> void;
};
