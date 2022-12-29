module;
#include "ext/macros/macros.hpp"


export module apis.magnetometer.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE(magnetometer)
{
    class magnetometer;
    class uncalibrated_magnetometer;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(magnetometer)
{
    using magnetometer_reading_values_t = ext::map<ext::string, ext::any>;
    using uncalibrated_magnetometer_reading_values_t = ext::map<ext::string, ext::any>;
}
