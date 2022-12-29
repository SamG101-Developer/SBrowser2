module;
#include "ext/macros/macros.hpp"


export module apis.gyroscope.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE(gyroscope)
{
    class gyroscope;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(gyroscope)
{
    enum class gyroscope_local_coordinate_system_t {DEVICE, SCREEN};
    using gyroscope_reading_values_t = ext::map<ext::string, ext::any>;
}
