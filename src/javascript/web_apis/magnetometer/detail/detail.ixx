module;
#include "ext/macros.hpp"


export module apis.magnetometer.detail;
import apis.magnetometer.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(magnetometer)
{
    auto construct_magnetometer_object(magnetometer* sensor, ext::map<ext::string, ext::any>&& options) -> void;
};
