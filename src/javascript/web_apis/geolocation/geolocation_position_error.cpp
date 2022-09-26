#include "geolocation_position_error.hpp"

#include INCLUDE_INNER_TYPES(geolocation)


geolocation::geolocation_position_error::geolocation_position_error()
{
    INIT_PIMPL(geolocation_position_error);
}


auto geolocation::geolocation_position_error::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<geolocation_position_error>{isolate}
        .inherit<dom::other::dom_exception>()
        .static_("PERMISSION_DENIED", detail::geolocation_position_error_t::PERMISSION_DENIED)
        .static_("POSITION_UNAVAILABLE", detail::geolocation_position_error_t::POSITION_UNAVAILABLE)
        .static_("TIMEOUT", detail::geolocation_position_error_t::TIMEOUT)
        .auto_wrap_objects();

    return std::move(conversion);
}
