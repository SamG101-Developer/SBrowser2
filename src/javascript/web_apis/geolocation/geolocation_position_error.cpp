#include "geolocation_position_error.hpp"
#include "geolocation_position_error_private.hpp"

#include INCLUDE_INNER_TYPES(geolocation)


geolocation::geolocation_position_error::geolocation_position_error()
{
    INIT_PIMPL(geolocation_position_error);
}


geolocation::geolocation_position_error::geolocation_position_error(
        ext::string&& message,
        exception_t type)
        : base_exception{std::move(message), std::move(type)}
{
    INIT_PIMPL(geolocation_position_error);
}


auto geolocation::geolocation_position_error::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    using enum detail::geolocation_position_error_t;

    decltype(auto) conversion = v8pp::class_<geolocation_position_error>{isolate}
        .inherit<base_exception<exception_t>>()
        .static_("PERMISSION_DENIED", PERMISSION_DENIED)
        .static_("POSITION_UNAVAILABLE", POSITION_UNAVAILABLE)
        .static_("TIMEOUT", TIMEOUT)
        .auto_wrap_objects();

    return std::move(conversion);
}
