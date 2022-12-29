module;
#include "ext/macros/macros.hpp"


export module apis.accelerometer.detail;

import apis.accelerometer.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(accelerometer)
{
    /* [7.1] */ auto construct_accelerometer_object(accelerometer* sensor, ext::map<ext::string, ext::any>&& options) -> void;
}
