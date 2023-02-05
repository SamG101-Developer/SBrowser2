module;
#include "ext/macros.hpp"


export module apis.geolocation.geolocation_position_error:p;
import apis.base_exception;
import apis.geolocation.types;


DEFINE_PRIVATE_CLASS(geolocation, geolocation_position_error)
        : base_exception<detail::geolocation_position_error_t>
{
public:
    MAKE_QIMPL(geolocation_position_error);
};
