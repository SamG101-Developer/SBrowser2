module;
#include "ext/macros.hpp"


export module apis.geolocation.geolocation_position_error;
import apis.base_exception;
import apis.geolocation.types;


DEFINE_PUBLIC_CLASS(geolocation, geolocation_position_error) final
        : public base_exception<detail::geolocation_position_error_t>
{
public constructors:
    geolocation_position_error();
    geolocation_position_error(ext::string&& message, exception_t type);
    MAKE_PIMPL(geolocation_position_error);
    MAKE_V8_AVAILABLE(WINDOW);
};
