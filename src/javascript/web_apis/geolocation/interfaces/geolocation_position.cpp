module;
#include "ext/macros.hpp"


module apis.geolocation.geolocation_position;
import apis.geolocation.geolocation_coordinates;


geolocation::geolocation_position::geolocation_position()
{
    INIT_PIMPL;
}


auto geolocation::geolocation_position::get_coords() const -> geolocation_coordinates*
{
    ACCESS_PIMPL;
    return d->coords.get();
}


auto geolocation::geolocation_position::get_timestamp() const -> hr_time::epoch_time_stamp
{
    ACCESS_PIMPL;
    return d->timestamp;
}
