#include "geolocation_coordinates.hpp"
#include "geolocation_coordinates_private.hpp"

#include "ext/casting.hpp"


geolocation::geolocation_coordinates::geolocation_coordinates()
{
    INIT_PIMPL(geolocation_coordinates);
}


auto geolocation::geolocation_coordinates::get_accuracy() const -> ext::number<double>
{
    ACCESS_PIMPL(const geolocation_coordinates);
    return d->accuracy;
}


auto geolocation::geolocation_coordinates::get_latitude() const -> ext::number<double>
{
    ACCESS_PIMPL(const geolocation_coordinates);
    return d->latitude;
}


auto geolocation::geolocation_coordinates::get_longitude() const -> ext::number<double>
{
    ACCESS_PIMPL(const geolocation_coordinates);
    return d->longitude;
}


auto geolocation::geolocation_coordinates::get_altitude() const -> ext::number<double>
{
    ACCESS_PIMPL(const geolocation_coordinates);
    return d->altitude;
}


auto geolocation::geolocation_coordinates::get_altitude_accuracy() const -> ext::number<double>
{
    ACCESS_PIMPL(const geolocation_coordinates);
    return d->altitude_accuracy;
}


auto geolocation::geolocation_coordinates::get_heading() const -> ext::number<double>
{
    ACCESS_PIMPL(const geolocation_coordinates);
    return d->heading;
}


auto geolocation::geolocation_coordinates::get_speed() const -> ext::number<double>
{
    ACCESS_PIMPL(const geolocation_coordinates);
    return d->speed;
}


auto geolocation::geolocation_coordinates::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) declaration = v8pp::class_<geolocation_coordinates>{isolate}
        .inherit<dom_object>()
        .property("accuracy", &geolocation_coordinates::get_accuracy)
        .property("latitude", &geolocation_coordinates::get_latitude)
        .property("longitude", &geolocation_coordinates::get_longitude)
        .property("altitude", &geolocation_coordinates::get_altitude)
        .property("altitudeAccuracy", &geolocation_coordinates::get_altitude_accuracy)
        .property("heading", &geolocation_coordinates::get_heading)
        .property("speed", &geolocation_coordinates::get_speed)
        .auto_wrap_objects();

    return std::move(declaration);
}
