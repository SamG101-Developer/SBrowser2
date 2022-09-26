#include "geolocation_position.hpp"

#include "geolocation/geolocation_coordinates.hpp"


geolocation::geolocation_position::geolocation_position()
{
    INIT_PIMPL(geolocation_position);
}


auto geolocation::geolocation_position::get_coords() const -> geolocation_coordinates*
{
    ACCESS_PIMPL(const geolocation_position);
    return d->coords.get();
}


auto geolocation::geolocation_position::get_timestamp() const -> hr_time::epoch_time_stamp
{
    ACCESS_PIMPL(const geolocation_position);
    return d->timestamp;
}


auto geolocation::geolocation_position::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<geolocation_position>{isolate}
        .inherit<dom_object>()
        .property("coords", &geolocation_position::get_coords)
        .property("timestamp", &geolocation_position::get_timestamp)
        .auto_wrap_objects();

    return std::move(conversion);
}
