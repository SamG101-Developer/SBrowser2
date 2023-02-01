module;
#include "ext/macros.hpp"


export module apis.geolocation.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE(geolocation)
{
    class geolocation;
    class geolocation_coordinates;
    class geolocation_position;
    class geolocation_position_error;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(geolocation)
{
    using position_callback_t = ext::unique_function<auto(geolocation_position* position) -> void>;
    using position_error_callback_t = ext::unique_function<auto(geolocation_position_error* position_error) -> void>;
    using position_options_t = ext::map<ext::string, ext::any>;

    enum class geolocation_position_error_t {PERMISSION_DENIED, POSITION_UNAVAILABLE, TIMEOUT};
}
