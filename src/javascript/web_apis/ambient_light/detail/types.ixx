module;
#include "ext/macros.hpp"


export module apis.ambient_light.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE(ambient_light)
{
    class ambient_light_sensor;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(ambient_light)
{
    using ambient_light_reading_values = ext::map<ext::string, ext::any>;
};
